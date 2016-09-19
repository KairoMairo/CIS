#include "administrationwindow.h"
#include "ui_administrationwindow.h"

CAdministrationWindow::CAdministrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CAdministrationWindow)
{
    ui->setupUi(this);
}

CAdministrationWindow::~CAdministrationWindow()
{
    delete ui;
}
