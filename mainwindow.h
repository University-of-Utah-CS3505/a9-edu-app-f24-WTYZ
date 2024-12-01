#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helppage.h"
#include "rabbit.h"
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QMainWindow>
#include "dog.h"
#include "monkey.h"
#include "rope.h"

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

    b2World *world = nullptr;          // Box2D world
    QTimer *worldUpdateTimer = nullptr; // Global physics timer

    b2Body *groundBody = nullptr;
    Animal* currentAnimal = nullptr;

    Rabbit *rabbit = nullptr;          // Rabbit object
    Dog *dog = nullptr;                // Dog object
    Monkey *monkey = nullptr;          // Monkey object
    Rope *rope;
    QPushButton *ropeButton;

};

#endif // MAINWINDOW_H
