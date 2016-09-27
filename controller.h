#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#define QUANTITY_TYPES 3

#include "database.h"

class CController
{
public:
    CController();
    ~CController();
    CController* operator=(CController* controller);

    bool load_documents(DocumentType type); // загружаем документ
    bool load_items(int index); //загружает список продукции (принимает id документа)
    bool load_components(int index);
    bool save_document(DocumentType type); //сохраняем изменения
    bool save_all();

    QList<CDocument*> get_documents(DocumentType type); //возвращаем список документов

    void set_document_name(DocumentType type, int index, QString name);
    void set_document_comment(DocumentType type, int index, QString comment);

    QString get_document_index(DocumentType type, int index);
    QString get_document_added_date(DocumentType type, int index);
    QString get_document_completion_date(DocumentType type, int index);
    QString get_document_status(DocumentType type, int index);
    QString get_document_name(DocumentType type, int index);
    QString get_document_comment(DocumentType type, int index);
    int get_document_size(DocumentType type);

    QString get_item_index(int index);
    QString get_item_name(int index);
    QString get_item_price(int index);
    QString get_item_quantity(int index);
    QString get_item_sum(int index);
    QString get_item_production_time(int index);

    QString get_components_id(int index);
    QString get_components_name(int index);
    QString get_components_id_component(int index);
    QString get_components_count(int index);
    QString get_components_id_item(int index);

    void get_index_window_item(int index);
    int set_index_window_item();

    float get_item_total();
    int get_item_size();

    bool is_saved();
    bool is_saved(DocumentType type);
    bool document_signed(DocumentType type, int index);

    QString delete_star(QString string);
    QString add_star(QString string);

private:
    void clear_items();
    void clear_documents();
    void clear_components();


private:
    QList<CDocument*> documents[QUANTITY_TYPES]; // список всех документов
    QList<CItem*> items; //список продукции
    QList<CPart*> parts; //список необходимых материалов
    QList<CEquipment*> equipments; //список оборудования
    QList<CComponents *> components; //список компонентов
    CDataBase data_base; //для работы с базой данных

    bool saved[QUANTITY_TYPES];
    int _index;
};

#endif // CCONTROLLER_H
