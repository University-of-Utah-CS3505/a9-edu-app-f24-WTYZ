/**
 * Name: WYNTER KIM, TERESA PARK, YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK, ZHENGXI ZHANG
 */
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize Box2D world
    qDebug() << "Creating Box2D world...";
    b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);

    // Default Ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -2.0f);
    groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    qDebug() << "Ground initialized in Box2D world.";

    // UI connections and setup
    connections();
    settingScreenUI();
    settingSounds();

    // Initialize global world update timer
    worldUpdateTimer = new QTimer(this);
    connect(worldUpdateTimer, &QTimer::timeout, this, &MainWindow::updateWorld);
    worldUpdateTimer->start(16);

    // RopeButtonSetup
    std::vector<QPushButton *> ropeButtons = {ui->ropeButton,
                                              ui->ropeButton_2,
                                              ui->ropeButton_3,
                                              ui->ropeButton_4,
                                              ui->ropeButton_5,
                                              ui->ropeButton_6};
    for (QPushButton *button : ropeButtons) {
        if (!button) {
            qDebug() << "Error: Missing QPushButton for rope.";
            return;
        }
    }
    b2Vec2 anchorPosition(4.0f, 6.0f);
    rope = new Rope(world, anchorPosition, ropeButtons);

    // Initialize animals
    initializeAnimal(reinterpret_cast<Animal *&>(rabbit), ui->rabbitButton, 0);
    initializeAnimal(reinterpret_cast<Animal *&>(dog), ui->dogButton, 1);
    initializeAnimal(reinterpret_cast<Animal *&>(monkey), ui->monkeyButton, 2);
    switchToRabbit();
}

MainWindow::~MainWindow()
{
    delete world; // Clean up Box2D world
    delete ui;
}

void MainWindow::settingSounds()
{
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
    dogSound->setSource(QUrl("qrc:/sounds/dogBarks_gou_zai_jiao.m4a"));

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
        QRect geometry = button->geometry();
        QPointF initialPos = geometry.center();

        // Map button position to Box2D world coordinates
        float initialX = initialPos.x() / 50.0f;
        float initialY = (300 - initialPos.y()) / 50.0f;

        if (layerIndex == 0) { // Rabbit
            rabbit = new Rabbit(button, world, b2Vec2(initialX, initialY));
            rabbit->getButton()->setStyleSheet("background: transparent; border: none;");
        }
        else if (layerIndex == 1) { // Dog
            float initialX = initialPos.x() / 50.0f;
            float initialY = (300 - initialPos.y()) / 50.0f;
            dog = new Dog(button, world, b2Vec2(initialX, initialY));
            dog->getButton()->setStyleSheet("background: transparent; border: none;");
            // Ensure the button starts within visible bounds
            float uiX = std::max(0.0f, std::min(static_cast<float>(geometry.center().x()), 750.0f));
            float uiY = std::max(0.0f, std::min(static_cast<float>(geometry.center().y()), 550.0f));
            button->move(static_cast<int>(uiX), static_cast<int>(uiY));
            button->setParent(ui->stackedWidgetBackground->widget(layerIndex));
        }
        else if (layerIndex == 2) { // Monkey
            monkey = new Monkey(button,
                                world,
                                b2Vec2(initialPos.x() / 50.0f,
                                       (300 - initialPos.y()) / 52.0f),
                                rope);
            button->setMouseTracking(true);
            monkey->getButton()->setStyleSheet("background: transparent; border: none;");
        }
        // Attach button to the correct layer
        if (animal && button) {
            button->setParent(ui->stackedWidgetBackground->widget(layerIndex));
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
        if (rabbitSound)
            rabbitSound->play();
    });
    connect(ui->soundButton_3, &QPushButton::clicked, this, [this]() {
        if (dogSound)
            dogSound->play();
    });
    connect(ui->soundButton_2, &QPushButton::clicked, this, [this]() {
        if (monkeySound)
            monkeySound->play();
    });

    // Connect cleanup Button
    connect(ui->clearButton_rabbit, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_rabbit->clearDrawing();
    });
    connect(ui->clearButton_monkey, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_monkey->clearDrawing();
    });
    connect(ui->clearButton_dog, &QPushButton::clicked, this, [this]() {
        ui->drawingWidget_dog->clearDrawing();
    });
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

void MainWindow::playDrawingBoxGif(QLabel *gifLabel, const QString &gifPath)
{
    QMovie *animalGifMovie = new QMovie(gifPath, QByteArray(), this);
    gifLabel->setMovie(animalGifMovie);
    gifLabel->setScaledContents(true);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(gifLabel);
    opacityEffect->setOpacity(0.5);
    gifLabel->setGraphicsEffect(opacityEffect);

    connect(animalGifMovie, &QMovie::frameChanged, this, [animalGifMovie]() {
        if (animalGifMovie->currentFrameNumber() == animalGifMovie->frameCount() - 1) {
            animalGifMovie->stop();
        }
    });

    animalGifMovie->start();
    gifLabel->setVisible(true);
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
    ui->translateEnglish->setStyleSheet("color: black;"
                                        "font-weight: bold; color: black;"
                                        "font-weight: bold; background-color: transparent;");
    ui->translateChinese->setStyleSheet("color: black;"
                                        "font-size: 16px;"
                                        "background:transparent;");

    QMovie *leftMovie = new QMovie(":/animations/gif_rabbit_tu.gif");
    ui->leftGifLabel->setScaledContents(true);
    ui->leftGifLabel->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_run_tiao.gif");
    ui->rightGifLabel->setScaledContents(true);
    ui->rightGifLabel->setMovie(rightMovie);
    rightMovie->start();
    //Main Containter Gif & User Input Drawing
    playDrawingBoxGif(ui->gifContainerRight_rabbit, ":/animations/gif_run_tiao.gif");
    playDrawingBoxGif(ui->gifContainerLeft_rabbit, ":/animations/gif_rabbit_tu.gif");
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
    updateGroundPosition(-2.0f, 200.0f, 0.5f);

    ui->btnRabbit->setStyleSheet("background-color: white; border-radius: 25px;");
    ui->btnDog->setStyleSheet("background-color: white; border-radius: 25px;");
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
    ui->translateEnglish_3->setStyleSheet("color: black;"
                                          "font-weight: bold; color: black;"
                                          "font-weight: bold; background-color: transparent;");
    ui->translateChinese_3->setStyleSheet("color: black;"
                                          "font-size: 16px;"
                                          "background:transparent;");

    QMovie *leftMovie = new QMovie(":/animations/gif_dog_gou.gif");
    ui->leftGifLabel_3->setScaledContents(true);
    ui->leftGifLabel_3->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_bark_jiao.gif");
    ui->rightGifLabel_3->setScaledContents(true);
    ui->rightGifLabel_3->setMovie(rightMovie);
    rightMovie->start();

    //Main Containter Gif & User Input Drawing
    playDrawingBoxGif(ui->gifContainerRight_dog, ":/animations/gif_bark_jiao.gif");
    playDrawingBoxGif(ui->gifContainerLeft_dog, ":/animations/gif_dog_gou.gif");
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
    std::vector<QPushButton *> ropeButtons = {ui->ropeButton,
                                              ui->ropeButton_2,
                                              ui->ropeButton_3,
                                              ui->ropeButton_4,
                                              ui->ropeButton_5,
                                              ui->ropeButton_6};

    for (QPushButton *button : ropeButtons) {
        if (button) {
            button->show();
            button->raise();
        }
    }

    ui->translateEnglish_2->setText("Monkey Swings");
    ui->translateChinese_2->setText("猴在荡");
    ui->translateEnglish_2->setStyleSheet("color: white; font-weight: bold;");
    ui->translateChinese_2->setStyleSheet("color: white;"
                                          "font-size: 16px;"
                                          "background:transparent;");

    QMovie *leftMovie = new QMovie(":/animations/gif_monkey_hou.gif");
    ui->leftGifLabel_2->setScaledContents(true);
    ui->leftGifLabel_2->setMovie(leftMovie);
    leftMovie->start();

    QMovie *rightMovie = new QMovie(":/animations/gif_swing_dang.gif");
    ui->rightGifLabel_2->setScaledContents(true);
    ui->rightGifLabel_2->setMovie(rightMovie);
    rightMovie->start();
    //Main Containter Gif & User Input Drawing
    playDrawingBoxGif(ui->gifContainerRight_monkey, ":/animations/gif_swing_dang.gif");
    playDrawingBoxGif(ui->gifContainerLeft_monkey, ":/animations/gif_monkey_hou.gif");
    enableAnimalDrawing(ui->drawingWidget_monkey);
}

void MainWindow::showHelpPage()
{
    HelpPage helpPage(this);
    helpPage.exec();
}

void MainWindow::updateGroundPosition(float yPosition, float width, float height)
{
    if (groundBody) {
        world->DestroyBody(groundBody);
    }

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, yPosition); // Update ground position
    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(width, height); // Update ground dimensions
    groundBody->CreateFixture(&groundBox, 0.0f);
    qDebug() << "Ground updated to position:" << yPosition;
}
