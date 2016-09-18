#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class CAdministrationWindow;
}

class CAdministrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CAdministrationWindow(QWidget *parent = 0);
    ~CAdministrationWindow();

private:
    Ui::CAdministrationWindow *ui;
};

#endif // ADMINISTRATIONWINDOW_H
