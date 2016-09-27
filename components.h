#ifndef CComponents_H
#define CComponents_H
#include <QString>

class CComponents
{
public:
    CComponents(int id,
                QString name,
                int id_component,
                int id_item,
                int count_component);

    QString get_id();
    QString get_id_component();
    QString get_id_item();
    QString get_count_component();
    QString get_name();

private:
    int _id;
    int _id_component;
    int _id_item;
    int _count_component;
    QString _name;
};

#endif // CComponents_H
