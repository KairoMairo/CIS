#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>

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
};

#endif // USERWINDOW_H
