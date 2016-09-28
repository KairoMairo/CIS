#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include "controller.h"

namespace Ui {
class CUserWindow;
}

class CUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CUserWindow(QWidget *parent = 0);
    ~CUserWindow();

private:
    Ui::CUserWindow *ui;

public slots:
    void get_controller(CController* controller);
private slots:
    void on_ok_clicked();
};

#endif // USERWINDOW_H
