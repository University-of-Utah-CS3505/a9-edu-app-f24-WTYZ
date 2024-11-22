#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helppage.h"

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
