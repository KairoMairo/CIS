#include "equipmentwindow.h"
#include "ui_equipmentwindow.h"

CEquipmentWindow::CEquipmentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CEquipmentWindow)
{
    ui->setupUi(this);
}

CEquipmentWindow::~CEquipmentWindow()
{
    delete ui;
}

void CEquipmentWindow::updata_equipment_table()
{

}

void CEquipmentWindow::updata_parts_table()
{

}

void CEquipmentWindow::get_controller(CController *controller, int part_document_index, int document_index)
{
    if (controller != NULL)
    {
        _controller =           controller;
        _part_document_index =  part_document_index;
        _document_index =       document_index;
    }
}
