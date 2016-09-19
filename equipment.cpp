#include "equipment.h"


CEquipment::CEquipment(int id,
                       QString name,
                       QString specification,
                       int number,
                       QList<CProcessing*> processes,
                       EquipmentStatus status,
                       float work_time_found,
                       float maintenance_interval,
                       float maintenance_time,
                       float power_consumption,
                       QDate maintenance_day)
{
    _id =                   id;
    _name =                 name;
    _specification =        specification;
    _number =               number;
    _processes =            processes;
    _status =               status;
    _work_time_found =      work_time_found;
    _maintenance_interval = maintenance_interval;
    _maintenance_time =     maintenance_time;
    _power_consumption =    power_consumption;
    _maintenance_day =      maintenance_day;
}

//возвращает индекс оборудования
int CEquipment::get_id()
{
    return _id;
}

//проверяет, существует ли обрабока/процесс с данным номером для данного оборудования
bool CEquipment::search_process(int index)
{
    for (int i = 0; i < _processes.size(); i++)
    {
        if (_processes[i]->get_id() == index)
        {
            return true;
        }
    }

    return false;
}
