#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class CAuthorizationWindow;
}

class CAuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CAuthorizationWindow(QWidget *parent = 0);
    ~CAuthorizationWindow();

private:
    Ui::CAuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
