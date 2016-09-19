#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QDialog>

#include "controller.h"


namespace Ui {
class orderwindow;
}

class orderwindow : public QDialog
{
    Q_OBJECT

public:
    explicit orderwindow(QWidget *parent = 0);
    ~orderwindow();

private:
    void update_list();

private:
    Ui::orderwindow *ui;

    CController* _controller;
    int _document_index;

public slots:
    void get_controller(CController* controller, int document_index);
private slots:
    void on_ok_clicked();
};

#endif // ORDERWINDOW_H
