#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helppage.h"
#include "rabbit.h"
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QLabel>
#include <QMainWindow>

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

private slots:
    void switchToRabbit();
    void switchToMonkey();
    void switchToDog();
    void showHelpPage();

    // rabbit
    void updateRabbitPhysics();
    void handleRabbitClick();


private:
    Ui::MainWindow *ui;

    // Rabbit-specific physics
    Rabbit *rabbit = nullptr;
    b2World *world = nullptr;
    QTimer *rabbitPhysicsTimer = nullptr;
};
#endif // MAINWINDOW_H
