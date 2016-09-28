#include "database.h"

#include <QSqlError>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QFileInfo>
#include <QDir>
#include<QMessageBox>
#include <QStringList>


CDataBase::CDataBase()
{
    //соединяемся с базой данных
    if (creat_connection())
    {
    }
}

//загружаем документ из базы данных
QList<CDocument*> CDataBase::load_document(DocumentType type)
{
    //формируем запрос
    QString string =    "SELECT * FROM documents WHERE type = %1;";
    string =            string.arg(type);
    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            //return NULL;
    }

    QSqlRecord rec =    query.record();
    QList<CDocument*>   documents;
    CDocument*          document;

    while (query.next())
    {
        document = new CDocument(query.value(rec.indexOf("id")).toInt(),
                                  query.value(rec.indexOf("name")).toString(),
                                  type,
                                  query.value(rec.indexOf("added_date")).toDate(),
                                  query.value(rec.indexOf("completion_date")).toDate(),
                                  (DocumentStatus)query.value(rec.indexOf("status")).toInt(),
                                  query.value(rec.indexOf("comment")).toString());

        documents.push_back(document);
    }

    return documents;
}

//загружаем список заказов из базы данных по id документа
QList<CItem *> CDataBase::load_items(int id)
{
    QString string =    "SELECT * FROM items, orders WHERE "
                        "orders.document_id = %1 AND orders.item_id = items.id;";
    string =            string.arg(id);

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            //return NULL;
    }

    QSqlRecord rec =    query.record();
    QList<CItem*>       items;
    CItem*              item;

    while (query.next())
    {
        item = new CItem(query.value(rec.indexOf("id")).toInt(),
                         query.value(rec.indexOf("name")).toString(),
                         query.value(rec.indexOf("price")).toFloat(),
                         query.value(rec.indexOf("quantity")).toInt(),
                         query.value(rec.indexOf("production_time")).toFloat());

        items.push_back(item);
    }

    return items;
}

QList<CComponents *> CDataBase::load_components(int id_item)
{
    QString string =    "SELECT * FROM componentsofmaterials;";

    string =            string.arg(id_item);

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
        QMessageBox::warning(0,
                                     "Warning",
                                     "БД не подключилась,"
                                     "",
                                     QString(),
                                     0
                                    );
    }

    QSqlRecord rec =    query.record();
    QList<CComponents*>       components;
    CComponents*              component;

    while (query.next())
    {

        component = new CComponents(query.value(rec.indexOf("id")).toInt(),
                         query.value(rec.indexOf("name")).toString(),
                         query.value(rec.indexOf("id_component")).toInt(),
                         query.value(rec.indexOf("id_item")).toInt(),
                         query.value(rec.indexOf("count_component")).toInt());

        components.push_back(component);
    }
    return components;
}

//возвращает индексы обработок для изготовления продукции с id_item из материалов с индексом id_part
QList<int> CDataBase::load_part_processing(int id_part, int id_item)
{
    QString string =    "SELECT id_processing FROM processing WHERE id_part = %1 "
                        "AND id_item = %2 ORDER BY number;";
    string =            string.arg(id_part)
                              .arg(id_item);

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            //return NULL;
    }

    QList<int> processes;

    while (query.next())
    {
        processes.push_back(query.value("id_processing").toInt());
    }

    return processes;
}

QList<CProcessing *> CDataBase::load_processing(int id_equipment)
{
    QString string = "SELECT * FROM processing_list WHERE id_equipment = %1;";

    QList<CProcessing*> processes;
    return processes;
}

//загружает список оборудования из БД
QList<CEquipment *> CDataBase::load_equipment()
{
    QString string =    "SELECT * FROM equipment_list, equipment "
                        "WHERE equipment_list.id = equipment.id_equipment;";

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            //return NULL;
    }

    QList<CEquipment*> equipments;

    while (query.next())
    {
        /*CEquipment* equipment = new CEquipment(query.value(rec.indexOf("id")).toInt(),
                                               query.value(rec.indexOf("name")).toString(),
                                               query.value(rec.indexOf("specification")).toString(),
                                               query.value(rec.indexOf("number")).toInt(),
                                               (EquipmentStatus)query.value(rec.indexOf("status")).toInt(),
                                               query.value(rec.indexOf("workload")).toFloat(),
                                               query.value(rec.indexOf("maintenance_interval")).toFloat(),
                                               query.value(rec.indexOf("maintenance_time")).toFloat(),
                                               query.value(rec.indexOf("power_consumption")).toFloat(),
                                               query.value(rec.indexOf("maintenance_day")).toDate());

        equipments.push_back(equipment);*/
    }

    return equipments;
}

//обновляем информацию о документе в базе данных
bool CDataBase::updata_document(DocumentType type, CDocument *document)
{
    QString string = "";

    if (type == ORDER)
    {
        string = "UPDATE documents SET comment = '"
                + document->get_comment()
                + "' WHERE id = '"
                + document->get_id_str()
                + "';";

    }
    else
    {
        string = "UPDATE documents SET name = '"
                + document->get_name()
                + "', comment = '"
                + document->get_comment()
                + "' WHERE id = '"
                + document->get_id_str()
                + "';";
    }

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
        return false;
    }

    return true;
}


//открываем базу данных "производство"
//при успешном открытии возвращает true
//иначе - false
bool CDataBase::creat_connection()
{
    data_base = QSqlDatabase::addDatabase("QSQLITE");

    QString path_to_data_base = "production.sqlite";
    data_base.setDatabaseName(path_to_data_base);
    data_base.setUserName("Kate");
    data_base.setHostName("localhost");
    data_base.setPassword("password");

    QFileInfo checkFile(path_to_data_base);

    if (checkFile.isFile())
    {
        if (data_base.open())
        {
            return true;
        }
    }

    return false;
}
