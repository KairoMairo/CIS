#include "processing.h"


//возвращает номер обработки
CProcessing::CProcessing(int id, QString name, QString specification)
{
    _id = id;
    _name = name;
    _specification = specification;
}

int CProcessing::get_id()
{
    return _id;
}
