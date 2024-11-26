#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connections();
    settingScreenUI();
    switchToRabbit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingScreenUI()
{
    // Animal Mode Button Clicked
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

    // Setting to Centralwidget
    ui->setContainerLeft->setParent(ui->centralwidget);
    ui->setContainerRight->setParent(ui->centralwidget);
    ui->translateChinese->setParent(ui->centralwidget);
    ui->translateEnglish->setParent(ui->centralwidget);
    ui->hanziContainerLeft->setParent(ui->centralwidget);
    ui->hanziContainerRight->setParent(ui->centralwidget);
    ui->labelContainerLeft->setParent(ui->centralwidget);
    ui->labelContainerRight->setParent(ui->centralwidget);
}

void MainWindow::connections()
{
    connect(ui->btnRabbit, &QPushButton::clicked, this, &MainWindow::switchToRabbit);
    connect(ui->btnMonkey, &QPushButton::clicked, this, &MainWindow::switchToMonkey);
    connect(ui->btnDog, &QPushButton::clicked, this, &MainWindow::switchToDog);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpPage);

    // Rabbit click
    connect(ui->rabbitButton, &QPushButton::clicked, this, &MainWindow::handleRabbitClick);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpPage);
}

void MainWindow::switchToRabbit()
{   ui->rabbitButton->setStyleSheet("background: none; border: none;");
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
                                 "border: 4px solid #2685E4;"
                                 "border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(0);

    // Initialize Rabbit Physics
    if (!world) {
        b2Vec2 gravity(0.0f, -5.0f);
        world = new b2World(gravity);
        qDebug() << "Box2D world is created";

        // Define the ground body
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -1.5f);
        b2Body *groundBody = world->CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 0.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
        qDebug() << "Ground body created";
    }

    // Create Rabbit object
    if (!rabbit) {
        rabbit = new Rabbit(ui->rabbitButton, world, b2Vec2(12.0f, -1.4f));
        qDebug() << "Rabbit object created";

        rabbitPhysicsTimer = new QTimer(this);
        connect(rabbitPhysicsTimer, &QTimer::timeout, this, &MainWindow::updateRabbitPhysics);
        rabbitPhysicsTimer->start(16); // 60 FPS
    }
}

void MainWindow::updateRabbitPhysics()
{
    if (world) {
        float32 timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        world->Step(timeStep, velocityIterations, positionIterations);

        if (rabbit) {
            rabbit->updatePosition();
        } else {
            qDebug() << "Rabbit is not initialized!";
        }
    } else {
        qDebug() << "Box2D world is not initialized!";
    }
}

void MainWindow::handleRabbitClick()
{
    if (rabbit) {
        rabbit->performAction();
    } else {
        qDebug() << "Rabbit object is not initialized!";
    }
}

void MainWindow::switchToDog()
{
    ui->btnRabbit->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid transparent;"
                                 "border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid transparent;"
                                 "border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;"
                              "width:50px;"
                              "background-color: white;"
                              "border: 4px solid #866839;"
                              "border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(1);
}
void MainWindow::switchToMonkey()
{
    ui->btnRabbit->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid transparent;"
                                 "border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;"
                              "width:50px;"
                              "background-color: white;"
                              "border: 4px solid transparent;"
                              "border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("height:50px;"
                                 "width:50px;"
                                 "background-color: white;"
                                 "border: 4px solid #25CE45;"
                                 "border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(2);
}

void MainWindow::showHelpPage()
{
    HelpPage helpPage(this);
    helpPage.exec();
}
