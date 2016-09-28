#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <controller.h>

namespace Ui {
class CAuthorizationWindow;
}

class CAuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CAuthorizationWindow(QWidget *parent = 0);
    ~CAuthorizationWindow();

signals:
    void ok(CController* controller);

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();
    void get_controller(CController* controller);

private:
    Ui::CAuthorizationWindow *ui;
    CController* _controller;
};

#endif // AUTHORIZATIONWINDOW_H
