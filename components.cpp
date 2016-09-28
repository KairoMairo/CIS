#include "components.h"

CComponents::CComponents(int id,
                         QString name,
                         int id_component,
                         int id_item,
                         int count_component)
{
    _id =               id;
    _name =             name;
    _id_component =     rand()%5;
    _id_item =          rand()%5;
    _count_component =  rand()%100+1;
}



QString CComponents::get_id()
{
     QString result = QString("%1").arg(_id);
    return result;
}

QString CComponents::get_id_component()
{
     QString result = QString("%1").arg(_id_component);
    return result;
}

QString CComponents::get_name()
{
    return _name;
}

QString CComponents::get_id_item()
{
     QString result = QString("%1").arg(_id_item);
    return result;
}

QString CComponents::get_count_component()
{
     QString result = QString("%1").arg(_count_component);
    return result;
}
