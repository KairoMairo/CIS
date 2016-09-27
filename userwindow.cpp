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

void CUserWindow::get_controller(CController *controller)
{
    ui->surname->setText(controller->get_user_surname());
    ui->name->setText(controller->get_user_name());
    ui->patronymic->setText(controller->get_user_patronymic());
    ui->position->setText(controller->get_user_position());

}

void CUserWindow::on_ok_clicked()
{
    close();
}
