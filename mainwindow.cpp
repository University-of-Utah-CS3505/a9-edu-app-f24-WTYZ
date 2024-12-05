#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rabbit.h"  // Ensure Rabbit header is included for type safety
#include "rope.h"

#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize Box2D world
    qDebug() << "Creating Box2D world...";
    b2Vec2 gravity(0.0f, -9.8f); // Standard gravity
    world = new b2World(gravity);

    // Create ground to prevent animals from falling
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -2.0f); // Ground positioned slightly below the screen
    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.5f); // Ground dimensions (wide and thin)
    groundBody->CreateFixture(&groundBox, 0.0f);

    qDebug() << "Ground initialized in Box2D world.";

    // UI connections and setup
    connections();
    settingScreenUI();

    // Initialize global world update timer
    worldUpdateTimer = new QTimer(this);
    connect(worldUpdateTimer, &QTimer::timeout, this, &MainWindow::updateWorld);
    worldUpdateTimer->start(16); // 60 FPS

    // Initialize animals
    initializeAnimal(reinterpret_cast<Animal*&>(rabbit), ui->rabbitButton, 0);
    initializeAnimal(reinterpret_cast<Animal*&>(dog), ui->dogButton, 1);
    initializeAnimal(reinterpret_cast<Animal*&>(monkey), ui->monkeyButton, 2);

    // Default setup
    hideAllAnimals();
    switchToRabbit();

    // Ensure the parent widget (current stacked page) is visible
    QWidget* parentWidget = ui->stackedWidgetBackground->currentWidget();
    if (!parentWidget->isVisible()) {
        parentWidget->show(); // Make sure the parent widget is visible
        qDebug() << "Forcing parent widget to be visible.";
    }

    // Initialize the rope button and add it to the stacked widget
    ropeButton = new QPushButton(parentWidget);
    int parentHeight = ui->stackedWidgetBackground->currentWidget()->height();
    int buttonHeight = std::min(600, parentHeight); // Ensure button height fits within parent widget
    ropeButton->setGeometry(400, 0, 300, buttonHeight); // Adjust button geometry to 300 width
    ropeButton->setStyleSheet("background: transparent; border: none;");
    ropeButton->setEnabled(true);
    ropeButton->setFocusPolicy(Qt::StrongFocus);
    ropeButton->show();

    // Scale and set the icon for ropeButton to 300x300
    QPixmap pixmap(":/images/obj_rope.png");
    if (!pixmap.isNull()) {
        QSize targetSize(300, 300); // Explicitly set icon size to 300x300
        QPixmap scaledPixmap = pixmap.scaled(
            targetSize,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation // Smooth scaling
            );
        ropeButton->setIcon(QIcon(scaledPixmap));
        ropeButton->setIconSize(targetSize); // Apply the fixed 300x300 size
        qDebug() << "Icon scaled to size 300x300 and applied to ropeButton.";
    } else {
        qDebug() << "Error: Failed to load obj_rope.png.";
    }

    qDebug() << "Parent widget geometry:" << parentWidget->geometry()
             << "Visible:" << parentWidget->isVisible();
    qDebug() << "Rope button initialized with geometry:" << ropeButton->geometry()
             << "Visible:" << ropeButton->isVisible();

    // Pass the ropeButton to the Rope constructor
    rope = new Rope(world, b2Vec2(8.0f, 10.0f), ropeButton);

}

MainWindow::~MainWindow()
{
    delete world; // Clean up Box2D world
    delete ui;
}

void MainWindow::initializeAnimal(Animal *&animal, QPushButton *button, int layerIndex)
{
    if (!animal && button) {
        // Get the button's geometry to calculate its center
        QRect geometry = button->geometry();
        QPointF initialPos = geometry.center();

        // Map button position to Box2D world coordinates
        float initialX = initialPos.x() / 50.0f;  // Scale down for Box2D
        float initialY = (300 - initialPos.y()) / 50.0f;

        if (layerIndex == 0) { // Rabbit
            rabbit = new Rabbit(button, world, b2Vec2(initialX, initialY));
            rabbit->getButton()->setStyleSheet("background: transparent; border: none;");
        } else if (layerIndex == 1) { // Dog
            float initialX = initialPos.x() / 50.0f;  // Scale down for Box2D
            float initialY = (300 - initialPos.y()) / 50.0f; // Map UI Y to Box2D Y

            // Log for debugging
            qDebug() << "Dog Initial Box2D position:" << initialX << initialY;

            dog = new Dog(button, world, b2Vec2(initialX, initialY));
            dog->getButton()->setStyleSheet("background: transparent; border: none;");

            // Ensure the button starts within visible bounds
            float uiX = std::max(0.0f, std::min(static_cast<float>(geometry.center().x()), 750.0f));
            float uiY = std::max(0.0f, std::min(static_cast<float>(geometry.center().y()), 550.0f));
            button->move(static_cast<int>(uiX), static_cast<int>(uiY));
            qDebug() << "Dog Button Initial UI position:" << uiX << uiY;

            button->setParent(ui->stackedWidgetBackground->widget(layerIndex));
            button->hide(); // Initially hidden
        } else if (layerIndex == 2) { // Monkey
            monkey = new Monkey(button, world, b2Vec2(initialPos.x() / 50.0f, (300 - initialPos.y()) / 50.0f + 2.0f)); // Offset to avoid ground collision
            button->setMouseTracking(true);
            monkey->getButton()->setStyleSheet("background: transparent; border: none;");
            qDebug() << "Monkey initialized at position:" << initialX << initialY + 2.0f;
        }

        // Attach button to the correct layer
        if (animal && button) {
            button->setParent(ui->stackedWidgetBackground->widget(layerIndex));
            button->hide(); // Hide initially
        }
    }
}

void MainWindow::settingScreenUI()
{
    ui->btnMonkey->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid transparent;"
                                 "border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;"
                              "width:50px;"
                              "background-color: white;"
                              "border: 4px solid transparent;"
                              "border-radius: 25px;");
    ui->btnRabbit->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid transparent;"
                                 "border-radius: 25px;");
}

void MainWindow::connections()
{
    connect(ui->btnRabbit, &QPushButton::clicked, this, &MainWindow::switchToRabbit);
    connect(ui->btnMonkey, &QPushButton::clicked, this, &MainWindow::switchToMonkey);
    connect(ui->btnDog, &QPushButton::clicked, this, &MainWindow::switchToDog);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpPage);

    connect(ui->rabbitButton, &QPushButton::clicked, this, &MainWindow::handleRabbitClick);

    connect(ui->dogButton, &QPushButton::clicked, this, &MainWindow::handleDogClick);
}

void MainWindow::updateWorld() {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    if (world) {
        world->Step(timeStep, velocityIterations, positionIterations);

        if (monkey && rope && monkey->overlapsWithRope(rope)) {
            rope->attachMonkey(monkey->getBody());
        }
        if (currentAnimal) {
            currentAnimal->updatePhysics();
            currentAnimal->updatePosition();
        }
    }
}

void MainWindow::switchToRabbit()
{
    currentAnimal = rabbit;
    hideAllAnimals();

    ui->btnRabbit->setStyleSheet("background-color: #2685E4; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(0);

    if (rabbit && rabbit->getButton()) {
        rabbit->getButton()->show();
    }

    ui->labelHanziAnimal->setText("兔");
    ui->labelHanziAnimal->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziAnimal->setAlignment(Qt::AlignCenter);

    ui->labelHanziVerb->setText("跳");
    ui->labelHanziVerb->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziVerb->setAlignment(Qt::AlignCenter);
}

void MainWindow::handleRabbitClick()
{
    if (currentAnimal == rabbit && rabbit) {
        rabbit->performAction();
    } else {
        qDebug() << "Rabbit is not active or initialized!";
    }
}

void MainWindow::switchToDog()
{
    currentAnimal = dog;
    hideAllAnimals();

    ui->btnRabbit->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: #866839; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(1);

    if (dog && dog->getButton()) {
        dog->getButton()->show();
        qDebug() << "Dog button shown at:" << dog->getButton()->geometry();
    } else {
        qDebug() << "Dog object or button not initialized!";
    }

    ui->labelHanziAnimal_3->setText("狗");
    ui->labelHanziAnimal_3->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziAnimal_3->setAlignment(Qt::AlignCenter);

    ui->labelHanziVerb_3->setText("叫");
    ui->labelHanziVerb_3->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziVerb_3->setAlignment(Qt::AlignCenter);
}

void MainWindow::handleDogClick()
{
    if (currentAnimal == dog && dog) {
        dog->performAction();
    } else {
        qDebug() << "Dog is not active or initialized!";
    }
}


void MainWindow::switchToMonkey() {
    currentAnimal = monkey;
    hideAllAnimals();

    ui->btnRabbit->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: #25CE45; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(2);

    QWidget* monkeyPage = ui->stackedWidgetBackground->currentWidget();
    if (!monkeyPage->isVisible()) {
        monkeyPage->show();
        qDebug() << "Monkey page forced to visible.";
    }

    if (ropeButton) {
        ropeButton->setParent(monkeyPage);
        ropeButton->show();
        qDebug() << "Rope button shown on monkey page. Geometry:" << ropeButton->geometry();
    }

    if (monkey && monkey->getButton()) {
        monkey->getButton()->show();
        qDebug() << "Monkey button shown at:" << monkey->getButton()->geometry();
    }

    ui->labelHanziAnimal_2->setText("猴");
    ui->labelHanziAnimal_2->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziAnimal_2->setAlignment(Qt::AlignCenter);

    ui->labelHanziVerb_2->setText("荡");
    ui->labelHanziVerb_2->setStyleSheet(
        "font-size: 90px;"
        "font-family: SimKai;"
        "font-weight: bold;"
        "color: rgba(0, 0, 0, 40%);"
        "background: transparent;"
        );
    ui->labelHanziVerb_2->setAlignment(Qt::AlignCenter);
}

void MainWindow::hideAllAnimals()
{
    if (rabbit && rabbit->getButton()) {
        rabbit->getButton()->hide();
    }
    if (dog && dog->getButton()) {
        dog->getButton()->hide();
    }
    if (monkey && monkey->getButton()) {
        monkey->getButton()->hide();
    }
}

void MainWindow::showHelpPage()
{
    HelpPage helpPage(this);
    helpPage.exec();
}
