/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidgetBackground;
    QWidget *pageRabbit;
    QLabel *bgRabbit;
    QLabel *hanziContainerLeft;
    QLabel *hanziContainerRight;
    QLabel *labelContainerLeft;
    QLabel *setContainerRight;
    QLabel *setContainerLeft;
    QLabel *labelContainerRight;
    QLabel *labelHanziAnimal;
    QLabel *labelHanziVerb;
    QLabel *translateChinese;
    QLabel *translateEnglish;
    QLabel *labelSound;
    QPushButton *rabbitButton;
    QWidget *pageDog;
    QLabel *bgDog;
    QWidget *pageMonkey;
    QLabel *bgMonkey;
    QPushButton *helpButton;
    QPushButton *btnDog;
    QPushButton *btnRabbit;
    QPushButton *btnMonkey;
    QMenuBar *menubar;
    QMenu *menuGame;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(801, 597);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background:black;"));
        stackedWidgetBackground = new QStackedWidget(centralwidget);
        stackedWidgetBackground->setObjectName("stackedWidgetBackground");
        stackedWidgetBackground->setGeometry(QRect(0, 0, 801, 501));
        pageRabbit = new QWidget();
        pageRabbit->setObjectName("pageRabbit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pageRabbit->sizePolicy().hasHeightForWidth());
        pageRabbit->setSizePolicy(sizePolicy);
        pageRabbit->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        pageRabbit->setAutoFillBackground(false);
        bgRabbit = new QLabel(pageRabbit);
        bgRabbit->setObjectName("bgRabbit");
        bgRabbit->setGeometry(QRect(-30, 0, 841, 551));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bgRabbit->sizePolicy().hasHeightForWidth());
        bgRabbit->setSizePolicy(sizePolicy1);
#if QT_CONFIG(accessibility)
        bgRabbit->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_CONFIG(accessibility)
        bgRabbit->setPixmap(QPixmap(QString::fromUtf8(":/background/bg_rabbit.png")));
        bgRabbit->setScaledContents(true);
        hanziContainerLeft = new QLabel(pageRabbit);
        hanziContainerLeft->setObjectName("hanziContainerLeft");
        hanziContainerLeft->setGeometry(QRect(260, 70, 151, 141));
        hanziContainerLeft->setPixmap(QPixmap(QString::fromUtf8(":/images/strokeGuideBox.png")));
        hanziContainerLeft->setScaledContents(true);
        hanziContainerRight = new QLabel(pageRabbit);
        hanziContainerRight->setObjectName("hanziContainerRight");
        hanziContainerRight->setGeometry(QRect(420, 70, 151, 141));
        hanziContainerRight->setPixmap(QPixmap(QString::fromUtf8(":/images/strokeGuideBox.png")));
        hanziContainerRight->setScaledContents(true);
        labelContainerLeft = new QLabel(pageRabbit);
        labelContainerLeft->setObjectName("labelContainerLeft");
        labelContainerLeft->setGeometry(QRect(260, 20, 151, 41));
        labelContainerLeft->setPixmap(QPixmap(QString::fromUtf8(":/images/labelContainer.png")));
        labelContainerLeft->setScaledContents(true);
        setContainerRight = new QLabel(pageRabbit);
        setContainerRight->setObjectName("setContainerRight");
        setContainerRight->setGeometry(QRect(580, 20, 181, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(setContainerRight->sizePolicy().hasHeightForWidth());
        setContainerRight->setSizePolicy(sizePolicy2);
        setContainerRight->setStyleSheet(QString::fromUtf8("border: 4px solid white;\n"
"background-color: rgba(255, 255, 255, 0.3);"));
        setContainerLeft = new QLabel(pageRabbit);
        setContainerLeft->setObjectName("setContainerLeft");
        setContainerLeft->setGeometry(QRect(70, 20, 181, 41));
        sizePolicy2.setHeightForWidth(setContainerLeft->sizePolicy().hasHeightForWidth());
        setContainerLeft->setSizePolicy(sizePolicy2);
        setContainerLeft->setStyleSheet(QString::fromUtf8("border: 4px solid white;\n"
"background-color: rgba(255, 255, 255, 0.3);"));
        labelContainerRight = new QLabel(pageRabbit);
        labelContainerRight->setObjectName("labelContainerRight");
        labelContainerRight->setGeometry(QRect(420, 20, 151, 41));
        labelContainerRight->setPixmap(QPixmap(QString::fromUtf8(":/images/labelContainer.png")));
        labelContainerRight->setScaledContents(true);
        labelHanziAnimal = new QLabel(pageRabbit);
        labelHanziAnimal->setObjectName("labelHanziAnimal");
        labelHanziAnimal->setGeometry(QRect(260, 70, 151, 141));
        labelHanziAnimal->setStyleSheet(QString::fromUtf8("background: transparent;"));
        labelHanziVerb = new QLabel(pageRabbit);
        labelHanziVerb->setObjectName("labelHanziVerb");
        labelHanziVerb->setGeometry(QRect(420, 70, 151, 141));
        labelHanziVerb->setStyleSheet(QString::fromUtf8("background:transparent;"));
        translateChinese = new QLabel(pageRabbit);
        translateChinese->setObjectName("translateChinese");
        translateChinese->setGeometry(QRect(580, 20, 91, 41));
        translateChinese->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(60, 60, 60);"));
        translateChinese->setAlignment(Qt::AlignmentFlag::AlignCenter);
        translateEnglish = new QLabel(pageRabbit);
        translateEnglish->setObjectName("translateEnglish");
        translateEnglish->setGeometry(QRect(70, 20, 91, 41));
        translateEnglish->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(60, 60, 60);"));
        translateEnglish->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelSound = new QLabel(pageRabbit);
        labelSound->setObjectName("labelSound");
        labelSound->setGeometry(QRect(730, 30, 21, 21));
        labelSound->setStyleSheet(QString::fromUtf8("background: transparent;"));
        labelSound->setPixmap(QPixmap(QString::fromUtf8(":/images/btn_sound.png")));
        labelSound->setScaledContents(true);
        rabbitButton = new QPushButton(pageRabbit);
        rabbitButton->setObjectName("rabbitButton");
        rabbitButton->setGeometry(QRect(650, 320, 111, 101));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/animals/obj_rabbit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        rabbitButton->setIcon(icon);
        rabbitButton->setIconSize(QSize(100, 100));
        stackedWidgetBackground->addWidget(pageRabbit);
        pageDog = new QWidget();
        pageDog->setObjectName("pageDog");
        bgDog = new QLabel(pageDog);
        bgDog->setObjectName("bgDog");
        bgDog->setGeometry(QRect(-10, -20, 811, 541));
        bgDog->setPixmap(QPixmap(QString::fromUtf8(":/background/bg_dog.png")));
        bgDog->setScaledContents(true);
        stackedWidgetBackground->addWidget(pageDog);
        pageMonkey = new QWidget();
        pageMonkey->setObjectName("pageMonkey");
        bgMonkey = new QLabel(pageMonkey);
        bgMonkey->setObjectName("bgMonkey");
        bgMonkey->setGeometry(QRect(0, -15, 801, 511));
        bgMonkey->setPixmap(QPixmap(QString::fromUtf8(":/background/bg_monkey.png")));
        bgMonkey->setScaledContents(true);
        stackedWidgetBackground->addWidget(pageMonkey);
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName("helpButton");
        helpButton->setGeometry(QRect(690, 510, 100, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/btn_tutorial.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        helpButton->setIcon(icon1);
        helpButton->setIconSize(QSize(100, 90));
        btnDog = new QPushButton(centralwidget);
        btnDog->setObjectName("btnDog");
        btnDog->setGeometry(QRect(130, 510, 50, 50));
        sizePolicy1.setHeightForWidth(btnDog->sizePolicy().hasHeightForWidth());
        btnDog->setSizePolicy(sizePolicy1);
        btnDog->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/btn_dog.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnDog->setIcon(icon2);
        btnDog->setIconSize(QSize(36, 36));
        btnRabbit = new QPushButton(centralwidget);
        btnRabbit->setObjectName("btnRabbit");
        btnRabbit->setGeometry(QRect(70, 510, 50, 50));
        sizePolicy1.setHeightForWidth(btnRabbit->sizePolicy().hasHeightForWidth());
        btnRabbit->setSizePolicy(sizePolicy1);
        btnRabbit->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/btn_rabbit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnRabbit->setIcon(icon3);
        btnRabbit->setIconSize(QSize(36, 36));
        btnMonkey = new QPushButton(centralwidget);
        btnMonkey->setObjectName("btnMonkey");
        btnMonkey->setGeometry(QRect(10, 510, 50, 50));
        sizePolicy1.setHeightForWidth(btnMonkey->sizePolicy().hasHeightForWidth());
        btnMonkey->setSizePolicy(sizePolicy1);
        btnMonkey->setAutoFillBackground(false);
        btnMonkey->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/btn_monkey.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnMonkey->setIcon(icon4);
        btnMonkey->setIconSize(QSize(36, 36));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 801, 21));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName("menuGame");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuGame->menuAction());

        retranslateUi(MainWindow);

        stackedWidgetBackground->setCurrentIndex(0);
        helpButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        bgRabbit->setText(QString());
        hanziContainerLeft->setText(QString());
        hanziContainerRight->setText(QString());
        labelContainerLeft->setText(QString());
        setContainerRight->setText(QString());
        setContainerLeft->setText(QString());
        labelContainerRight->setText(QString());
        labelHanziAnimal->setText(QString());
        labelHanziVerb->setText(QString());
        translateChinese->setText(QCoreApplication::translate("MainWindow", "CHINESE", nullptr));
        translateEnglish->setText(QCoreApplication::translate("MainWindow", "ENGLISH", nullptr));
        labelSound->setText(QString());
        rabbitButton->setText(QString());
        bgDog->setText(QString());
        bgMonkey->setText(QString());
        helpButton->setText(QString());
        btnDog->setText(QString());
        btnRabbit->setText(QString());
        btnMonkey->setText(QString());
        menuGame->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
