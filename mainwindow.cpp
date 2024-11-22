#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connections();
    settingScreenUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingScreenUI(){
    // Animal Mode Button Clicked
    ui->btnMonkey->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnRabbit->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");

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

void MainWindow::connections(){
    connect(ui->btnRabbit, &QPushButton::clicked, this, &MainWindow::switchToRabbit);
    connect(ui->btnMonkey, &QPushButton::clicked, this, &MainWindow::switchToMonkey);
    connect(ui->btnDog, &QPushButton::clicked, this, &MainWindow::switchToDog);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::showHelpPage);
}

void MainWindow::switchToRabbit(){
    ui->btnMonkey->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnRabbit->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid #2685E4;""border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(0);
}
void MainWindow::switchToDog(){
    ui->btnRabbit->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid #866839;""border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(1);
}
void MainWindow::switchToMonkey(){
    ui->btnRabbit->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnDog->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid transparent;""border-radius: 25px;");
    ui->btnMonkey->setStyleSheet("height:50px;""width:50px;""background-color: white;""border: 4px solid #25CE45;""border-radius: 25px;");
    ui->stackedWidgetBackground->setCurrentIndex(2);
}

void MainWindow::showHelpPage() {
    HelpPage helpPage(this);
    helpPage.exec();
}
