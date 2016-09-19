#ifndef CITEM_H
#define CITEM_H

#include <QString>

//класс для продукции
class CItem
{
public:
    CItem(int id, QString name, float price, int quantity, float production_time);
    CItem* operator=(CItem* item);

    int get_id();
    int get_quantity();
    float get_price();
    float get_production_time();
    QString get_name();

    QString get_id_str(); //возвращает индекс в виде строки
    QString get_quantity_str(); //возвращает количество необходимой продукции в виде строки
    QString get_price_str(); //возвращает цену за ед. продукции в виде строки
    QString get_production_time_str(); //возвращает время изготовления в виде строки
    QString get_sum_str(); //возвращает общую сумму в виде строки

    float sum();

private:
    int _id;
    int _quantity;

    QString _name;

    float _price;
    float _production_time;
};

#endif // CITEM_H
