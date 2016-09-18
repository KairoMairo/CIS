#include "userwindow.h"
#include "ui_userwindow.h"

CUserWindow::CUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUserWindow)
{
    ui->setupUi(this);
}

CUserWindow::~CUserWindow()
{
    delete ui;
}
