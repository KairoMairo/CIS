#ifndef CDOCUMENT_H
#define CDOCUMENT_H

#include <QString>
#include <QVector>
#include <QDate>

enum DocumentType
{
    ORDER,
    POWER,
    COSTS
};

enum DocumentStatus
{
    REDUCT,
    WAIT,
    COMPLET
};

class CDocument
{
public:
    CDocument(int id,
              QString name,
              DocumentType type,
              QDate added_date,
              DocumentStatus status,
              QString comment = "");
    CDocument(int id,
              QString name,
              DocumentType type,
              QDate added_date,
              QDate completion_date,
              DocumentStatus status,
              QString comment = "");
    CDocument* operator=(CDocument* document);

    void set_name(QString name);
    void set_comment(QString comment);
    void sign();

    int get_id();
    QDate get_added_date();
    QDate get_completion_date();
    DocumentStatus get_status();
    QString get_name();
    QString get_comment();

    QString get_id_str(); //возвращает id документа в виде строки
    QString get_added_date_str(); //возвращает дату добавления документа в виде строки
    QString get_completion_date_str(); //возвращает дату подписи в виде строки
    QString get_status_str(); //возвращает статус в виде строки


private:
    int _id; //id документа

    QDate _added_date; //дата добавления документа
    QDate _completion_date; //дата выполнения документа

    DocumentStatus _status; //статус документа

    DocumentType _type; //тип документа

    QString _name; //название документа
    QString _comment; //комментарий к документу

};

#endif // CDOCUMENT_H
