#include "productionwindow.h"
#include "ui_productionwindow.h"
#include "mainwindow.h"
#include "equipmentwindow.h"
#include "authorizationwindow.h"
#include "userwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractItemModel>
#include <QMessageBox>

enum
{
    ORDER_MODEL,
    POWER_MODEL,
    ACCOUNT_MODEL
};

enum
{
    ID,
    NAME,
    ADDED_DATE,
    STATUS,
    COMPLETION_DATE,
    COMMENT
};

enum
{
    EQUIPMENT_MODEL,
    WORKING_HOURS_MODEL,
    INDUSTRIAL_AREA_MODEL,
    NOMENCLATURE_MODEL,
};

CProductionWindow::CProductionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CProductionWindow)
{
    ui->setupUi(this);

    signed_now = false;

    //связывем сигнал "выбрали пункт меню Главное меню" со слотом "перейти в главное меню"
    connect(ui->main_menu, SIGNAL(triggered()), this, SLOT(slot_go_main_menu()));

    //связываем сигнал "выбрали пункт меню Выход" со слотом "закрыть диалог. окно"
    connect(ui->close_program, SIGNAL(triggered()), this, SLOT(close()));


}

CProductionWindow::~CProductionWindow()
{
    delete _controller;

    if (ui->order_table->model() != NULL)
    {
        delete ui->order_table->model();
    }
    if (ui->account_table->model() != NULL)
    {
        delete ui->account_table->model();
    }
    if (ui->power_table->model() != NULL)
    {
        delete ui->power_table->model();
    }

    delete ui;
}

//задаетм модели для таблиц окна производства
void CProductionWindow::make_tables_model()
{
    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Номер");
    horizontalHeader.append("Название документа");
    horizontalHeader.append("Дата добавления");
    horizontalHeader.append("Статус");
    horizontalHeader.append("Дата завершения");
    horizontalHeader.append("Комментарий");

    //Создаем модели
    QStandardItemModel* model[TABLES_QUANTITY];

    for (int i = 0; i < TABLES_QUANTITY; i++)
    {
        model[i] = new QStandardItemModel;
        model[i]->setHorizontalHeaderLabels(horizontalHeader);
    }

    ui->order_table->setModel(model[ORDER_MODEL]);
    ui->power_table->setModel(model[POWER_MODEL]);
    ui->account_table->setModel(model[ACCOUNT_MODEL]);

    //Подгоняем размер колонок в зависимости от текста заголовков
    ui->order_table->resizeColumnsToContents();

    //updata_order_table();


}


//Обновляем таблицу
//Таблица будет содержать документы
void CProductionWindow::updata_table(DocumentType type)
{
    if (ui->order_table->model() != NULL)
    {
        delete ui->order_table->model();
    }

    QStringList horizontalHeader;
    horizontalHeader.append("Номер");
    horizontalHeader.append("Название документа");
    horizontalHeader.append("Дата добавления");
    horizontalHeader.append("Статус");
    horizontalHeader.append("Дата завершения");
    horizontalHeader.append("Комментарий");

    QStandardItemModel *model = new QStandardItemModel;
    model->setHorizontalHeaderLabels(horizontalHeader);

    QStandardItem *item;

    int size =_controller->get_document_size(type);

    for (int i = 0; i < size; i++)
    {
        item = new QStandardItem(_controller->get_document_index(type, i));
        //item->setEditable(false);
        model->setItem(i, ID, item);

        item = new QStandardItem(_controller->get_document_name(type, i));
        model->setItem(i, NAME, item);

        item = new QStandardItem(_controller->get_document_added_date(type, i));
        model->setItem(i, ADDED_DATE, item);

        item = new QStandardItem(_controller->get_document_status(type, i));
        model->setItem(i, STATUS, item);

        item = new QStandardItem(_controller->get_document_completion_date(type, i));
        model->setItem(i, COMPLETION_DATE, item);

        item = new QStandardItem(_controller->get_document_comment(type, i));
        item->setEditable(true);
        model->setItem(i, COMMENT, item);
    }

    ui->order_table->setModel(model);
    ui->order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->order_table->resizeColumnsToContents();
    ui->order_table->resizeRowsToContents();

}

//Обрабатываем событие перед выходом
void CProductionWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    int choose = test_save();

    if (choose == QMessageBox::Ok)
    {
        event->accept();
    }
    else if (choose == QMessageBox::SaveAll)
    {
       _controller->save_all();
        event->accept();
    }
}

//удаляем все *
void CProductionWindow::delete_stars()
{
    delete_stars(ORDER_MODEL);
    delete_stars(POWER_MODEL);
    delete_stars(ACCOUNT_MODEL);
}

//удаляем * из заголовка выбранной страницы
void CProductionWindow::delete_stars(int page)
{
    if (_controller->is_saved())
    {
        setWindowTitle(_controller->delete_star(windowTitle()));
    }

    ui->work_space->setTabText(page,_controller->delete_star(ui->work_space->tabText(page)));
}

void CProductionWindow::open_user_window()
{
    CUserWindow* dlg = new CUserWindow;
    connect(this, SIGNAL(review_user(CController*)), dlg, SLOT(get_controller(CController*)));
    emit review_user(_controller);

    dlg->show();
}

//смотрим, на какой мы странице сейчас
DocumentType CProductionWindow::test_page()
{
    int index = ui->work_space->currentIndex();

    if (index == ORDER_MODEL)
    {
        return ORDER;
    }
    else if (index == POWER_MODEL)
    {
        return POWER;
    }
    else if (index == ACCOUNT_MODEL)
    {

    }

    return ORDER;
}

//спрашиваем, хотим ли сохранить измененные файлы? (если таковые имеются)
int CProductionWindow::test_save()
{
    if (!_controller->is_saved())
    {
        QMessageBox message("Предупреждение",
                            "Имеются несохраненные данные. "
                            "При продолжении информайия будет утеряна.",
                            QMessageBox::Information,
                            QMessageBox::Ok | QMessageBox::Default,
                            QMessageBox::SaveAll,
                            QMessageBox::Cancel | QMessageBox::Escape,
                            this);
        message.setButtonText(QMessageBox::SaveAll, "Сохранить все");
        message.setButtonText(QMessageBox::Cancel, "Отмена");

        int choose = message.exec();

        return choose;
    }

    return QMessageBox::Ok;
}

//перейти в главное меню
void CProductionWindow::go_main_menu()
{
    MainWindow* dlg = new MainWindow;
    dlg->show();
    this->close();
}

//выбран пункт "главное меню"
void CProductionWindow::slot_go_main_menu()
{
    int choose = test_save();

    if (choose == QMessageBox::Ok)
    {
        go_main_menu();
    }
    else if (choose == QMessageBox::SaveAll)
    {
       _controller->save_all();
        go_main_menu();
    }

}

//открываем окно просмотра заказов
void CProductionWindow::on_review_document_3_clicked()
{
    int index = ui->order_table->currentIndex().row();

    if (index < 0)
    {
        QMessageBox::information(this, "Ошибка", "Не выбран документ для просмотра!");
        return;
    }

    order_window = new orderwindow(this);

    connect(this, SIGNAL(review_order(CController*, int)), order_window, SLOT(get_controller(CController*, int)));

    emit review_order(_controller, index);

    order_window->show();
}

//выполняется после закрытия окна просмотра заказов
void CProductionWindow::after_close_order_window()
{
    updata_table(ORDER);

    if (!_controller->is_saved(ORDER))
    {
        setWindowTitle(_controller->add_star(windowTitle()));
        ui->work_space->setTabText(ORDER_MODEL,_controller->add_star(ui->work_space->tabText(ORDER_MODEL)));
    }

    if (signed_now)
    {
        signed_now = false;
    }
}

//выбрали пункт меню "сохранить"
void CProductionWindow::on_save_triggered()
{
   _controller->save_document(test_page());
    delete_stars(test_page());
}

//выбрали пункт меню "сохранить все"
void CProductionWindow::on_save_all_triggered()
{
   _controller->save_all();
    delete_stars();
}

//сменили лист в главном окне производства
void CProductionWindow::on_work_space_currentChanged(int index)
{
    updata_table(test_page());
}

//создать документ плана производства
void CProductionWindow::on_create_document_clicked()
{
    CEquipmentWindow* dlg = new CEquipmentWindow(this);

    dlg->show();
}

//открываем окно "производство"
void CProductionWindow::on_review_document_clicked()
{
    CEquipmentWindow* dlg = new CEquipmentWindow(this);

    dlg->show();
}

//открываем окно "производство" для редактирования
void CProductionWindow::on_reduct_document_clicked()
{
    CEquipmentWindow* dlg = new CEquipmentWindow(this);

    dlg->show();

}

void CProductionWindow::get_controller(CController *controller)
{
    _controller = controller;

    //обновляем текущую таблицу
    updata_table(test_page());
    ui->user_name->setText(_controller->get_user_FIO());
}

void CProductionWindow::on_change_user_triggered()
{
    CAuthorizationWindow* dlg = new CAuthorizationWindow;
    connect(this, SIGNAL(authorization(CController*)), dlg, SLOT(get_controller(CController*)));
    emit authorization(_controller);

    dlg->show();
    this->close();
}

void CProductionWindow::on_show_user_data_triggered()
{

    int choose = test_save();

    if (choose == QMessageBox::Ok)
    {
        open_user_window();
    }
    else if (choose == QMessageBox::SaveAll)
    {
       _controller->save_all();
        open_user_window();
    }

}

void CProductionWindow::on_close_program_triggered()
{
    int choose = test_save();

    if (choose == QMessageBox::Ok)
    {
        close();
    }
    else if (choose == QMessageBox::SaveAll)
    {
       _controller->save_all();
       close();
    }
}
