#include "document.h"


CDocument::CDocument(int id,
                     QString name,
                     DocumentType type,
                     QDate added_date,
                     DocumentStatus status,
                     QString comment)
{
    _id =           id;
    _name =         name;
    _type =         type;
    _added_date =   added_date;
    _status =       status;
    _comment =      comment;
}

CDocument::CDocument(int id,
                     QString name,
                     DocumentType type,
                     QDate added_date,
                     QDate completion_date,
                     DocumentStatus status,
                     QString comment)
{
    _id =               id;
    _name =             name;
    _type =             type;
    _added_date =       added_date;
    _status =           status;
    _comment =          comment;
    _completion_date =  completion_date;
}

CDocument *CDocument::operator=(CDocument *document)
{
    _id =               document->_id;
    _name =             document->_name;
    _type =             document->_type;
    _added_date =       document->_added_date;
    _completion_date =  document->_completion_date;
    _status =           document->_status;
    _comment =          document->_comment;

    return this;
}

void CDocument::set_name(QString name)
{
    if (_type != ORDER)
    {
        _name = name;
    }
}

void CDocument::set_comment(QString comment)
{
    _comment = comment;
}

void CDocument::sign()
{
    _status = COMPLET;
}

int CDocument::get_id()
{
    return _id;
}

QDate CDocument::get_added_date()
{
    return _added_date;
}

QDate CDocument::get_completion_date()
{
    return _completion_date;
}

DocumentStatus CDocument::get_status()
{
    return _status;
}

QString CDocument::get_name()
{
    return _name;
}

QString CDocument::get_comment()
{
    return _comment;
}

QString CDocument::get_id_str()
{
    QString result = QString("%1").arg(_id);

    return result;
}

QString CDocument::get_added_date_str()
{
    QString result = "%1.%2.%3";
    result = result.arg(_added_date.day())
            .arg(_added_date.month())
            .arg(_added_date.year());

    return result;
}

QString CDocument::get_completion_date_str()
{
    if (_status)
    {
        QString result = "%1.%2.%3";
        result = result.arg(_completion_date.day())
            .arg(_completion_date.month())
            .arg(_completion_date.year());

        return result;
    }

    return "";
}

QString CDocument::get_status_str()
{
    if (_status)
    {
        return "Подписан";
    }
    else if (_status == REDUCT)
    {
        return "Редактируется";
    }

    return "Подписан и выполнен";
}
