#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QTimer>
#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <Box2D/Box2D.h>

#include "dog.h"
#include "monkey.h"
#include "rope.h"
#include "drawingwidget.h"
#include "helppage.h"
#include "rabbit.h"


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
    void initializeAnimal(Animal *&animal, QPushButton *button, int layerIndex);

private slots:
    void updateWorld();
    void switchToRabbit();
    void switchToMonkey();
    void switchToDog();
    void showHelpPage();
    void hideAllAnimals();
    void handleRabbitClick();
    void handleDogClick();


private:
    Ui::MainWindow *ui;

    b2World *world = nullptr;           // Box2D world
    QTimer *worldUpdateTimer = nullptr; // Global physics timer

    b2Body *groundBody = nullptr;
    Animal* currentAnimal = nullptr;

    Rabbit *rabbit = nullptr;          // Rabbit object
    Dog *dog = nullptr;                // Dog object
    Monkey *monkey = nullptr;          // Monkey object
    Rope *rope;
    QPushButton *ropeButton;

    QMediaPlayer *rabbitSound = nullptr;    // Rabbit sound
    QMediaPlayer *dogSound = nullptr;       // Dog sound
    QMediaPlayer *monkeySound = nullptr;    // Monkey sound
};

#endif // MAINWINDOW_H
