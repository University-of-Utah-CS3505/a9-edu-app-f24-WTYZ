#include "mainwindow.h"
#include "rabbit.h" // Ensure Rabbit header is included for type safety
#include "rope.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <QMovie>

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
    settingSounds();

    // Initialize global world update timer
    worldUpdateTimer = new QTimer(this);
    connect(worldUpdateTimer, &QTimer::timeout, this, &MainWindow::updateWorld);
    worldUpdateTimer->start(16); // 60 FPS

    // Ensure the parent widget (current stacked page) is visible
    QWidget *parentWidget = ui->stackedWidgetBackground->currentWidget();
    if (!parentWidget->isVisible()) {
        parentWidget->show(); // Make sure the parent widget is visible
        qDebug() << "Forcing parent widget to be visible.";
    }
    // Pass the ropeButton to the Rope constructor
    std::vector<QPushButton *> ropeButtons = {
        ui->ropeButton,
        ui->ropeButton_2,
        ui->ropeButton_3,
        ui->ropeButton_4,
        ui->ropeButton_5,
    };

    // Validate that all buttons exist
    for (QPushButton *button : ropeButtons) {
        if (!button) {
            qDebug() << "Error: Missing QPushButton for rope.";
            return;
        }
    }

    // Initialize the rope
    b2Vec2 anchorPosition(4.0f, 6.0f); // Adjust as needed for your setup
    rope = new Rope(world, anchorPosition, ropeButtons);

    // Initialize animals
    initializeAnimal(reinterpret_cast<Animal *&>(rabbit), ui->rabbitButton, 0);
    initializeAnimal(reinterpret_cast<Animal *&>(dog), ui->dogButton, 1);
    initializeAnimal(reinterpret_cast<Animal *&>(monkey), ui->monkeyButton, 2);
    hideAllAnimals();
    switchToRabbit();
}

MainWindow::~MainWindow()
{
    delete world; // Clean up Box2D world
    delete ui;
}

void MainWindow::settingSounds()
{
    // Initialize Sound Button and Style

    // Rabbit Sound Button
    ui->soundButton->setStyleSheet("border: none; background-color: transparent;");
    QPixmap pixmapSound(":/images/btn_sound.png");
    QIcon iconSound(pixmapSound);
    ui->soundButton->setIcon(iconSound);

    rabbitSound = new QMediaPlayer(this);
    QAudioOutput *rabbitAudioOutput = new QAudioOutput(this);
    rabbitSound->setAudioOutput(rabbitAudioOutput);
    rabbitSound->setSource(QUrl("qrc:/sounds/rabbitJumps_tu_zai_tiao.m4a"));



    // Dog Sound Button
    ui->soundButton_3->setStyleSheet("border: none; background-color: transparent;");
    ui->soundButton_3->setIcon(iconSound);

    dogSound = new QMediaPlayer(this);
    QAudioOutput *dogAudioOutput = new QAudioOutput(this);
    dogSound->setAudioOutput(dogAudioOutput);
    dogSound->setSource(QUrl("qrc:/sounds/dogRuns_gou_zai_pao.m4a"));

    // Monkey Sound Button
    ui->soundButton_2->setStyleSheet("border: none; background-color: transparent;");
    ui->soundButton_2->setIcon(iconSound);

    monkeySound = new QMediaPlayer(this);
    QAudioOutput *monkeyAudioOutput = new QAudioOutput(this);
    monkeySound->setAudioOutput(monkeyAudioOutput);
    monkeySound->setSource(QUrl("qrc:/sounds/monkeySwings_hou_zai_dang.m4a"));
}

void MainWindow::initializeAnimal(Animal *&animal, QPushButton *button, int layerIndex)
{
    if (!animal && button) {
        // Get the button's geometry to calculate its center
        QRect geometry = button->geometry();
        QPointF initialPos = geometry.center();

        // Map button position to Box2D world coordinates
        float initialX = initialPos.x() / 50.0f; // Scale down for Box2D
        float initialY = (300 - initialPos.y()) / 50.0f;

        if (layerIndex == 0) { // Rabbit
            rabbit = new Rabbit(button, world, b2Vec2(initialX, initialY));
            rabbit->getButton()->setStyleSheet("background: transparent; border: none;");
        } else if (layerIndex == 1) {                        // Dog
            float initialX = initialPos.x() / 50.0f;         // Scale down for Box2D
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
            button->hide();           // Initially hidden
        } else if (layerIndex == 2) { // Monkey
            monkey = new Monkey(button,
                                world,
                                b2Vec2(initialPos.x() / 50.0f,
                                       (300 - initialPos.y()) / 50.0f
                                           + 2.0f),
                                rope); // Offset to avoid ground collision
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
    // Connect to Help Page
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpPage);
    // Connect Menu Button on the buttom page
    connect(ui->btnRabbit, &QPushButton::clicked, this, &MainWindow::switchToRabbit);
    connect(ui->btnMonkey, &QPushButton::clicked, this, &MainWindow::switchToMonkey);
    connect(ui->btnDog, &QPushButton::clicked, this, &MainWindow::switchToDog);

    // Connect Animations
    connect(ui->rabbitButton, &QPushButton::clicked, this, &MainWindow::handleRabbitClick);
    connect(ui->dogButton, &QPushButton::clicked, this, &MainWindow::handleDogClick);

    // Connect Sounds
    connect(ui->soundButton, &QPushButton::clicked, this, [this]() {
        if (rabbitSound) rabbitSound->play();});
    connect(ui->soundButton_3, &QPushButton::clicked, this, [this]() {
        if (dogSound) dogSound->play();});
    connect(ui->soundButton_2, &QPushButton::clicked, this, [this]() {
        if (monkeySound) monkeySound->play();});
    // Connect Erase Button
    connect(ui->clearButton_rabbit, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_rabbit->clearDrawing();});
    connect(ui->clearButton_monkey, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_monkey->clearDrawing();});
    connect(ui->clearButton_dog, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_dog->clearDrawing();});


}

void MainWindow::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    if (world) {
        world->Step(timeStep, velocityIterations, positionIterations);

        if (rope) {
            rope->updatePosition();
        }
        if (currentAnimal) {
            currentAnimal->updatePhysics();
            currentAnimal->updatePosition();
        }
    }
}

void MainWindow::playAnimalGifOnce(QLabel *gifLabel, const QString &gifPath, int durationMs)
{
    QMovie *animalGifMovie = new QMovie(gifPath, QByteArray(), this);
    gifLabel->setMovie(animalGifMovie);
    gifLabel->setScaledContents(true);

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(gifLabel);
    opacityEffect->setOpacity(0.5);
    gifLabel->setGraphicsEffect(opacityEffect);

    connect(timer, &QTimer::timeout, this, [animalGifMovie, timer]() {
        animalGifMovie->stop();
        timer->deleteLater();
    });

    animalGifMovie->start();
    gifLabel->setVisible(true);
    timer->start(durationMs);
}

void MainWindow::enableAnimalDrawing(DrawingWidget *drawingWidget)
{
    ui->drawingWidget_rabbit->raise();
    ui->drawingWidget_dog->raise();
    ui->drawingWidget_monkey->raise();
    drawingWidget->show();
    drawingWidget->clearDrawing();
}


void MainWindow::switchToRabbit()
{
    currentAnimal = rabbit;
    hideAllAnimals();
    updateGroundPosition(-2.0f, 200.0f, 0.5f);

    ui->btnRabbit->setStyleSheet("background-color: #2685E4; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(0);

    if (rabbit && rabbit->getButton()) {
        rabbit->getButton()->show();
    }

    ui->translateEnglish->setText("Rabbit Jumps");
    ui->translateChinese->setText("兔在跳");
    ui->translateChinese->setStyleSheet("color: black;" "font-size: 16px;" "background:transparent;");

    QMovie *leftMovie = new QMovie(":/animations/gif_rabbit_tu.gif");
    ui->leftGifLabel->setScaledContents(true);
    ui->leftGifLabel->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_run_tiao.gif");
    ui->rightGifLabel->setScaledContents(true);
    ui->rightGifLabel->setMovie(rightMovie);
    rightMovie->start();
    //Main Containter Gif & User Input Drawing
    playAnimalGifOnce(ui->gifContainerRight_rabbit, ":/animations/gif_run_tiao.gif", 5800);
    playAnimalGifOnce(ui->gifContainerLeft_rabbit, ":/animations/gif_rabbit_tu.gif", 4600);
    enableAnimalDrawing(ui->drawingWidget_rabbit);
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
    updateGroundPosition(-2.0f, 200.0f, 0.5f);

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

    ui->translateEnglish_3->setText("Dog Barks");
    ui->translateChinese_3->setText("狗在叫");
    ui->translateChinese_3->setStyleSheet("color: black;" "font-size: 16px;" "background:transparent;");

    QMovie *leftMovie = new QMovie(":/animations/gif_dog_gou.gif");
    ui->leftGifLabel_3->setScaledContents(true);
    ui->leftGifLabel_3->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_run_pao.gif");
    ui->rightGifLabel_3->setScaledContents(true);
    ui->rightGifLabel_3->setMovie(rightMovie);
    rightMovie->start();

    //Main Containter Gif & User Input Drawing
    playAnimalGifOnce(ui->gifContainerRight_dog, ":/animations/gif_run_pao.gif", 5200);
    playAnimalGifOnce(ui->gifContainerLeft_dog, ":/animations/gif_dog_gou.gif", 4800);
    enableAnimalDrawing(ui->drawingWidget_dog);
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
    monkey->getButton()->show();

    updateGroundPosition(-3.0f, 200.0f, 0.5f);

    // Update button styles to highlight the monkey selection
    ui->btnRabbit->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("background-color: #25CE45; border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(2);

    // Show the monkey's page
    QWidget *monkeyPage = ui->stackedWidgetBackground->currentWidget();
    if (!monkeyPage->isVisible()) {
        monkeyPage->show();
        qDebug() << "Monkey page forced to visible.";
    }

    if (monkey && monkey->getButton()) {
        monkey->getButton()->show();
        qDebug() << "Monkey button shown at:" << monkey->getButton()->geometry();
    }

    // Ensure the rope buttons are visible
    std::vector<QPushButton *> ropeButtons = {
        ui->ropeButton,
        ui->ropeButton_2,
        ui->ropeButton_3,
        ui->ropeButton_4,
        ui->ropeButton_5,
    };

    for (QPushButton *button : ropeButtons) {
        if (button) {
            button->show();
            button->raise();
        }
    }

    ui->translateEnglish_2->setText("Monkey Swings");
    ui->translateChinese_2->setText("猴在荡");
    ui->translateEnglish_2->setStyleSheet("color: white;");
    ui->translateChinese_2->setStyleSheet("color: white;" "font-size: 16px;" "background:transparent;");


    QMovie *leftMovie = new QMovie(":/animations/gif_monkey_hou.gif");
    ui->leftGifLabel_2->setScaledContents(true);
    ui->leftGifLabel_2->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_swing_dang.gif");
    ui->rightGifLabel_2->setScaledContents(true);
    ui->rightGifLabel_2->setMovie(rightMovie);
    rightMovie->start();
    //Main Containter Gif & User Input Drawing
    playAnimalGifOnce(ui->gifContainerRight_monkey, ":/animations/gif_swing_dang.gif", 5200);
    playAnimalGifOnce(ui->gifContainerLeft_monkey, ":/animations/gif_monkey_hou.gif", 5500);
    enableAnimalDrawing(ui->drawingWidget_monkey);
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

void MainWindow::updateGroundPosition(float yPosition, float width, float height) {
    // Destroy the existing ground body
    if (groundBody) {
        world->DestroyBody(groundBody);
    }

    // Create a new ground body with the specified position and dimensions
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, yPosition); // Update ground position
    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(width, height); // Update ground dimensions
    groundBody->CreateFixture(&groundBox, 0.0f);

    qDebug() << "Ground updated to position:" << yPosition;
}

