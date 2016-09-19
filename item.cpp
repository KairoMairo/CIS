#include "item.h"

CItem::CItem(int id,
             QString name,
             float price,
             int quantity,
             float production_time)
{
    _id =               id;
    _name =             name;
    _price =            price;
    _quantity =         quantity;
    _production_time =  production_time;
}

CItem *CItem::operator=(CItem *item)
{
    _id =               item->_id;
    _name =             item->_name;
    _price =            item->_price;
    _quantity =         item->_quantity;
    _production_time =  item->_production_time;

    return this;
}

int CItem::get_id()
{
    return _id;
}

int CItem::get_quantity()
{
    return _quantity;
}

float CItem::get_price()
{
    return _price;
}

float CItem::get_production_time()
{
    return _production_time;
}

QString CItem::get_name()
{
    return _name;
}

QString CItem::get_id_str()
{
    QString result = QString("%1").arg(_id);

    return result;
}

QString CItem::get_quantity_str()
{
    QString result = QString("%1").arg(_quantity);

    return result;
}

QString CItem::get_price_str()
{
    QString result = QString("%1").arg(_price);

    return result;
}

QString CItem::get_production_time_str()
{
    QString result = QString("%1").arg(_production_time);

    return result;
}

QString CItem::get_sum_str()
{
    QString result = QString("%1").arg(sum());

    return result;
}

float CItem::sum()
{
    float result = (float)_quantity;
    result *= _price;

    return result;
}
