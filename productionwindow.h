#ifndef PRODUCTIONWINDOW_H
#define PRODUCTIONWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "controller.h"
#include "orderwindow.h"

#define TABLES_QUANTITY 3




namespace Ui {
class CProductionWindow;
}

class CProductionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CProductionWindow(QWidget *parent = 0);
    ~CProductionWindow();

private:
    Ui::CProductionWindow *ui;
    CController* _controller;
    orderwindow* order_window;
    bool signed_now;


private:
    void go_main_menu();
    void make_tables_model();
    void updata_table(DocumentType type);
    void closeEvent(QCloseEvent *event);
    void delete_stars();
    void delete_stars(int page);
    void open_user_window();

    DocumentType test_page();

    int test_save();


signals:
    void review_order(CController* controller, int document_index);
    void authorization(CController* controller);
    void review_user(CController* controller);

private slots:
    void slot_go_main_menu();
    void on_review_document_3_clicked();
    void after_close_order_window();
    void on_save_triggered();
    void on_save_all_triggered();
    void on_work_space_currentChanged(int index);
    void on_create_document_clicked();
    void on_review_document_clicked();
    void on_reduct_document_clicked();
    void get_controller(CController* controller);
    void on_change_user_triggered();
    void on_show_user_data_triggered();
};

#endif // PRODUCTIONWINDOW_H
