#include "modelproduction.h"


CModelProduction::CModelProduction(QList<CEquipment *> equipments, QList<CPart *> parts)
{
    _all_equipments = equipments;
    _parts = parts;
}

bool CModelProduction::execution()
{
    for (int i = 0; i < _parts.size(); i++)
    {

       choose_equipment(_parts[i]);
    }

    return true;
}

void CModelProduction::choose_equipment(CPart *part)
{
    for (int i = 0; i < _all_equipments.size(); i++)
    {
       /* if (_model_equipments[i]->search_process(part->))
        {

        }*/
    }
}
