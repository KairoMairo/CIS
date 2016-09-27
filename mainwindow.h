#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "productionwindow.h"
#include "authorizationwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void authorization(CController* controller);
    void controller_to_prodaction(CController* controller);

private slots:
    void on_production_BTN_clicked();
    void open_production(CController* controller);

private:
    Ui::MainWindow *ui;
    CAuthorizationWindow* authorizationDlg;
    CProductionWindow* productionDlg;
};

#endif // MAINWINDOW_H
