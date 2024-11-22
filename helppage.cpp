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
