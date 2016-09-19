#ifndef EQUIPMENTWINDOW_H
#define EQUIPMENTWINDOW_H

#include <QDialog>
#include "controller.h"

namespace Ui {
class CEquipmentWindow;
}

class CEquipmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CEquipmentWindow(QWidget *parent = 0);
    ~CEquipmentWindow();

private:
    void updata_equipment_table();
    void updata_parts_table();

private:
    Ui::CEquipmentWindow*   ui;
    CController*            _controller;

    int _part_document_index;
    int _document_index;

public slots:
    void get_controller(CController* controller, int part_document_index, int document_index);
};

#endif // EQUIPMENTWINDOW_H
