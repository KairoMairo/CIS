#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"
#include "productionwindow.h"

#include <QMessageBox>

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

void CAuthorizationWindow::on_ok_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();

    int i = rand() %100 + 1;

    if(_controller->authorization(login, password))
    {

        CProductionWindow* productionDlg = new CProductionWindow;

        connect(this, SIGNAL(ok(CController*)), productionDlg, SLOT(get_controller(CController*)));
        emit ok(_controller);
        productionDlg->showMaximized();
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Неверный логин или пароль!");
    }


}

void CAuthorizationWindow::on_cancel_clicked()
{
    close();
}

void CAuthorizationWindow::get_controller(CController *controller)
{


    _controller = controller;
}
