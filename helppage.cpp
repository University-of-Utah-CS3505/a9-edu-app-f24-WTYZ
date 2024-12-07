/**
 * Name: WYNTER KIM, TERESA PARK
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: ZHENGXI ZHANG, YINHAO CHEN
 */
#include "helppage.h"
#include "ui_helppage.h"

HelpPage::HelpPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpPage)
{
    ui->setupUi(this);
}

HelpPage::~HelpPage()
{
    delete ui;
}
