#ifndef CDATABASE_H
#define CDATABASE_H

//#include <QtSql/QSql>
#include <QtSql>
#include <QSqlDatabase>

#include "document.h"
#include "item.h"
#include "equipment.h"
#include "components.h"


class CDataBase
{
public:
    CDataBase();
    QList<CDocument*> load_document(DocumentType type);
    QList<CItem*> load_items(int id);
    QList<int> load_part_processing(int id_part, int id_item);
    QList<CProcessing*> load_processing(int id_equipment);
    QList<CEquipment *> load_equipment();
    QList<CComponents *> load_components(int id_item);

    bool updata_document(DocumentType type, CDocument* document);

private:
    bool creat_connection();

private:
    QSqlDatabase data_base;

};

#endif // CDATABASE_H
