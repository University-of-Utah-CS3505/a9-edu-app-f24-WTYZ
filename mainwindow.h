/**
 * Name: WYNTER KIM, TERESA PARK, YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK, ZHENGXI ZHANG
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioOutput>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMovie>
#include <QTimer>
#include <Box2D/Box2D.h>
#include "dog.h"
#include "drawingwidget.h"
#include "helppage.h"
#include "monkey.h"
#include "rabbit.h"
#include "rope.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connections();
    void settingScreenUI();
    void settingSounds();
    /**
     * @brief initializeAnimal
     * Set up the Animal (Which are QPushButton)
     * @param animal
     * @param button
     * @param layerIndex
     */
    void initializeAnimal(Animal *&animal, QPushButton *button, int layerIndex);
    /**
     * @brief playDrawingBoxGif
     * Play the stroke gif
     * @param gifLabel
     * @param gifPath
     */
    void playDrawingBoxGif(QLabel *gifLabel, const QString &gifPath);
    /**
     * @brief enableAnimalDrawing
     * Allow user draw the Hanzi
     * @param drawingWidget
     */
    void enableAnimalDrawing(DrawingWidget *drawingWidget);

private slots:
    /**
     * @brief updateWorld
     * Just update the Box2d world with animation
     */
    void updateWorld();
    // Three methods for switching scene
    void switchToRabbit();
    void switchToMonkey();
    void switchToDog();

    void showHelpPage();
    void handleRabbitClick();
    void handleDogClick();

private:
    Ui::MainWindow *ui;

    b2World *world = nullptr;
    QTimer *worldUpdateTimer = nullptr; // Global physics timer
    b2Body *groundBody = nullptr;
    Animal *currentAnimal = nullptr;
    Rabbit *rabbit = nullptr;
    Dog *dog = nullptr;
    Monkey *monkey = nullptr;
    Rope *rope;
    QPushButton *ropeButton;

    QMediaPlayer *rabbitSound = nullptr; // Rabbit sound
    QMediaPlayer *dogSound = nullptr;    // Dog sound
    QMediaPlayer *monkeySound = nullptr; // Monkey sound
    /**
     * @brief updateGroundPosition
     * Private method to help update the ground position for different scene
     * @param yPosition
     * @param width
     * @param height
     */
    void updateGroundPosition(float yPosition, float width, float height);
};

#endif // MAINWINDOW_H
