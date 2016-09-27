#ifndef CHOOSEDOCUMENT_H
#define CHOOSEDOCUMENT_H

#include <QDialog>

namespace Ui {
class CChooseDocument;
}

class CChooseDocument : public QDialog
{
    Q_OBJECT

public:
    explicit CChooseDocument(QWidget *parent = 0);
    ~CChooseDocument();

private:
    Ui::CChooseDocument *ui;
};

#endif // CHOOSEDOCUMENT_H
