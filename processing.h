#ifndef CPROCESSING_H
#define CPROCESSING_H

#include<QString>

class CProcessing
{
public:
    CProcessing(int id, QString name, QString specification);

    int get_id();

private:
    int _id;
    int _time;

    QString _name;
    QString _specification;
};

#endif // CPROCESSING_H
