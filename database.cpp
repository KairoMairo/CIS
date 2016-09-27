#include "database.h"

#include <QSqlError>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QFileInfo>
#include <QDir>

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
                        /*"SELECT * FROM equipment, equipment_list
                         * WHERE equipment.id_equipment = equipment_list.id"
                        "(SELECT id FROM equipment_list WHERE id IN "
                        "(SELECT id_equipment FROM pricessing_list, processing WHERE "
                        "processing_list.id = processing.id_processing AND "
                        "id_output = %1));";*/
    string =            string.arg(type);
    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            //return NULL;
    }

    QList<CDocument*>   documents;
    CDocument*          document;

    while (query.next())
    {
        document = new CDocument(query.value("id").toInt(),
                                  query.value("name").toString(),
                                  type,
                                  query.value("added_date").toDate(),
                                  query.value("completion_date").toDate(),
                                  (DocumentStatus)query.value("status").toInt(),
                                  query.value("comment").toString());

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
    QString string = QString("SELECT * FROM processing_list WHERE id_equipment = %1;").arg(id_equipment);

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
        /*CEquipment* equipment = new CEquipment(query.value("id").toInt(),
                                               query.value("name").toString(),
                                               query.value("specification").toString(),
                                               query.value("number").toInt(),
                                               (EquipmentStatus)query.value("status").toInt(),
                                               query.value("workload").toFloat(),
                                               query.value("maintenance_interval").toFloat(),
                                               query.value("maintenance_time").toFloat(),
                                               query.value("power_consumption").toFloat(),
                                               query.value("maintenance_day").toDate(),);

        equipments.push_back(equipment);*/
    }

    return equipments;
}

CUser *CDataBase::authorization(QString login, QString password)
{
    QString string = "SELECT * FROM users, positions "
                     "WHERE login = \"" +
                     login +
                     "\" AND password = \"" +
                     password + "\";";

    QSqlQuery query(data_base);

    if (!query.exec(string))
    {
            return NULL;
    }
    query.next();

    QString name = query.value("name").toString();

    if (name.isEmpty())
    {
        return NULL;
    }

    CUser* user = new CUser(query.value("id").toInt(),
                            name,
                            query.value("surname").toString(),
                            query.value("patronymic").toString(),
                            query.value("position").toString(),
                            query.value("salary").toFloat(),
                            query.value("working_hours").toFloat());

    return user;
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
