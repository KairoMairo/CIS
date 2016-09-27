#include "choosedocument.h"
#include "ui_choosedocument.h"

CChooseDocument::CChooseDocument(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CChooseDocument)
{
    ui->setupUi(this);
}

CChooseDocument::~CChooseDocument()
{
    delete ui;
}
