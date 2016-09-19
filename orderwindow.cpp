#include "orderwindow.h"
#include "ui_orderwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>

enum
{
    ID,
    NAME,
    PRODUCTION_TIME,
    PRICE,
    QUANTITY,
    SUM
};

orderwindow::orderwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderwindow)
{
    ui->setupUi(this);

    _controller = NULL;

    connect(this, SIGNAL(rejected()), parent, SLOT(after_close_order_window()));
}

orderwindow::~orderwindow()
{
    if (ui->order_table->model() != NULL)
    {
        delete ui->order_table->model();
    }

    delete ui;
}

//выводим список продукции
void orderwindow::update_list()
{
    _controller->load_items(_document_index);

    if (ui->order_table->model() != NULL)
    {
        delete ui->order_table->model();
    }

    QStringList horizontalHeader;
    horizontalHeader.append("Номер");
    horizontalHeader.append("Название продукции");
    horizontalHeader.append("Время изготовления");
    horizontalHeader.append("Цена");
    horizontalHeader.append("Количество");
    horizontalHeader.append("Сумма");

    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(horizontalHeader);

    QStandardItem *item;

    int size = _controller->get_item_size();

    for (int i = 0; i < size; i++)
    {
        item = new QStandardItem(_controller->get_item_index(i));
        model->setItem(i, ID, item);

        item = new QStandardItem(_controller->get_item_name(i));
        model->setItem(i, NAME, item);

        item = new QStandardItem(_controller->get_item_production_time(i));
        model->setItem(i, PRODUCTION_TIME, item);

        item = new QStandardItem(_controller->get_item_price(i));
        model->setItem(i, PRICE, item);

        item = new QStandardItem(_controller->get_item_quantity(i));
        model->setItem(i, QUANTITY, item);

        item = new QStandardItem(_controller->get_item_sum(i));
        model->setItem(i, SUM, item);
    }

    ui->order_table->setModel(model);
    ui->order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->order_table->resizeColumnsToContents();
    ui->order_table->resizeRowsToContents();

    ui->total->setValue((double)_controller->get_item_total());

}

void orderwindow::get_controller(CController* controller, int document_index)
{
    if (_controller == NULL)
    {
        _controller = controller;
        _document_index = document_index;

        setWindowTitle(_controller->get_document_name(ORDER, document_index));
        ui->id->setText(_controller->get_document_index(ORDER, document_index));
        ui->added_date->setText(_controller->get_document_added_date(ORDER, document_index));
        ui->completion_date->setText(_controller->get_document_completion_date(ORDER, document_index));
        ui->status->setText(_controller->get_document_status(ORDER, document_index));
        ui->comment->setText(_controller->get_document_comment(ORDER, document_index));

        update_list();
    }


}

void orderwindow::on_ok_clicked()
{
    QString comment = ui->comment->toPlainText();

    if (_controller->get_document_comment(ORDER, _document_index) != comment)
    {
        _controller->set_document_comment(ORDER, _document_index, comment);
    }

    this->close();
}
