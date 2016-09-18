#ifndef CPART_H
#define CPART_H

#include"processing.h"

#include<QList>

class CPart
{
public:
    CPart(int id, QString name);

    int get_id();
    int get_current_process_id();
    int get_process_id(int index);

private:
    int _id;
    int _quantity;

    QString _name;

    QList<int> _processes;
};

#endif // CPART_H
