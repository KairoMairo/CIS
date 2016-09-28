#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

CAuthorizationWindow::CAuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAuthorizationWindow)
{
    ui->setupUi(this);
}

CAuthorizationWindow::~CAuthorizationWindow()
{
    delete ui;
}
