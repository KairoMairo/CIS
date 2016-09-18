#ifndef CEQUIPMENT_H
#define CEQUIPMENT_H

#include "part.h"

#include<QDate>


enum EquipmentStatus
{
    BUSY,
    FREE,
    BROKEN,
    SERVICED
};

class CEquipment
{
public:
    CEquipment(int id,
               QString name,
               QString specification,
               int number,
               QList<CProcessing*> processes,
               EquipmentStatus status,
               float work_time_found,
               float maintenance_interval,
               float maintenance_time,
               float power_consumption,
               QDate maintenance_day);

    int get_id();

    bool search_process(int index);

private:
    int _id;
    int _number;

    float _maintenance_interval;
    float _maintenance_time;
    float _power_consumption;
    float _work_time_found;
    float _effective_work_time_found;
    float _custodial_work_time_found;
    float _calendar_work_time_found;

    QString _name;
    QString _specification;

    EquipmentStatus _status;

    QDate _maintenance_day;

    QList<CProcessing*> _processes;

    QList<CPart*> _parts;
};

#endif // CEQUIPMENT_H
