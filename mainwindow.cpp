#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPushButton>
#include <QApplication>
#include <QPalette>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->production_BTN->setStyleSheet("QPushButton{color: #fff; "
                                                  "text-decoration: none; "
                                                  "user-select: none; "
                                                  "background: rgb(0, 128, 0); /* фон кнопки */"
                                                  "padding: .7em 1.5em; }"
                                      "QPushButton:hover{background: rgb(34, 139, 34); border:none;}");

    ui->supply_BTN->setStyleSheet("QPushButton{color: #fff; "
                                             "text-decoration: none; "
                                             "user-select: none; "
                                             "background: rgb(0, 128, 0); /* фон кнопки */"
                                             "padding: .7em 1.5em; }"
                                  "QPushButton:hover{background: rgb(34, 139, 34); border:none;}");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_production_BTN_clicked()
{
    authorizationDlg = new CAuthorizationWindow;

    CController* controller = new CController();
    connect(this, SIGNAL(authorization(CController*)), authorizationDlg, SLOT(get_controller(CController*)));
    connect(authorizationDlg, SIGNAL(ok(CController*)), this, SLOT(open_production(CController*)));
    emit authorization(controller);

    authorizationDlg->show();

}

void MainWindow::open_production(CController* controller)
{
    this->close();
}

