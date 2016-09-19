#ifndef CMODELPRODUCTION_H
#define CMODELPRODUCTION_H

#include "equipment.h"

class CModelProduction
{
public:
    CModelProduction(QList<CEquipment*> equipments,
                     QList<CPart*> parts);
    bool execution();

private:
    void choose_equipment(CPart* part);

private:
    QList<CEquipment*> _all_equipments;
    QList<CEquipment*> _need_equipments;
    QList<CEquipment*> _model_equipments;

    QList<CPart*> _parts;


};

#endif // CMODELPRODUCTION_H
