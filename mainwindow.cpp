#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rabbit.h"  // Ensure Rabbit header is included for type safety

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

        if (currentAnimal) {
            currentAnimal->updatePhysics(); // Call custom physics updates
            currentAnimal->updatePosition(); // Update visual position
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
}

void MainWindow::handleDogClick()
{
    if (currentAnimal == dog && dog) {
        dog->performAction();
    } else {
        qDebug() << "Dog is not active or initialized!";
    }
}


void MainWindow::switchToMonkey()
{
    currentAnimal = monkey;
    hideAllAnimals();

    qDebug() << "Switching to monkey. CurrentAnimal set to:" << currentAnimal;



    ui->btnRabbit->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: #25CE45; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(2);

    if (monkey && monkey->getButton()) {
        monkey->getButton()->show();
        qDebug() << "Monkey button shown at:" << monkey->getButton()->geometry();
    }
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
