#include "controller.h"


CController::CController()
{
    load_documents(ORDER);

    user = NULL;

    for (int type = ORDER; type < QUANTITY_TYPES; type++)
    {
        saved[type] = true;
    }
}

CController::~CController()
{
    clear_documents();
    clear_items();

}

//перегрузка оператора =
CController* CController::operator=(CController* controller)
{
    data_base = controller->data_base;

    for (int type = ORDER; type < QUANTITY_TYPES; type++)
    {
        documents[type] =   controller->documents[type];
        saved[type] =       controller->saved[type];
    }

    return this;
}

// вызывает функцию загрузки из базы данных документов выбранного типа
bool CController::load_documents(DocumentType type)
{
    if (type < QUANTITY_TYPES)
    {
        documents[type] = data_base.load_document(type);
    }
    else
    {
        return false;
    }

    if (documents[type].isEmpty())
    {
        return false;
    }

    return true;
}

//вызывает функцию загрузки из БД списка продукции для документа
bool CController::load_items(int index)
{
    clear_items();

    if (index < documents[ORDER].size())
    {
        items = data_base.load_items(documents[ORDER][index]->get_id());
    }
    else
    {
        return false;
    }

    if (items.isEmpty())
    {
        return false;
    }

    return true;
}

//сохраняем определенные документы
bool CController::save_document(DocumentType type)
{
    bool result = false;

    if (type < QUANTITY_TYPES)
    {
        if (!saved[type])
        {
            for (int i = 0; i < documents[type].size(); i++)
            {
                result =        data_base.updata_document(type, documents[type][i]);
                saved[type] =   true;
            }
        }
        else
        {
            return true;
        }
    }

    return result;

}

//сохраняем все документы
bool CController::save_all()
{
    bool result = false;

    for (int type = ORDER; type < QUANTITY_TYPES; type++)
    {
        result = save_document((DocumentType)type);
    }

    return result;
}

//возврвщаем список документов выбранного типа
QList<CDocument*> CController::get_documents(DocumentType type)
{
    if (type < QUANTITY_TYPES)
    {
        if (documents[type].isEmpty())//если документы не загружены, то загружаем их
        {
            load_documents(type);
        }

        return documents[type];
    }

    QList<CDocument*> empty_list;
    return empty_list;
}

void CController::set_document_name(DocumentType type, int index, QString name)
{
    if (type < QUANTITY_TYPES && type != ORDER)
    {
        if (index < documents[type].size())
        {
            documents[type][index]->set_name(name);

            saved[type] = false;
        }
    }
}

void CController::set_document_comment(DocumentType type, int index, QString comment)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            documents[type][index]->set_comment(comment);

            saved[type] = false;
        }
    }
}

//возвращает индекс выбранного документа в виде строки
QString CController::get_document_index(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_id_str();
        }
    }

    return "";
}

//возвращает дату добавления выбранного документа в виде строки
QString CController::get_document_added_date(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_added_date_str();
        }
    }

    return "";
}

//возвращает дату подписи выбранного документа в виде строки
QString CController::get_document_completion_date(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_completion_date_str();
        }
    }

    return "";
}

//возвращает статус выбранного документа в виде строки
QString CController::get_document_status(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_status_str();
        }
    }

    return "";
}

//возвращает название выбранного документа в виде строки
QString CController::get_document_name(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_name();
        }
    }

    return "";
}

//возвращает комментарий выбранного документа в виде строки
QString CController::get_document_comment(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            return documents[type][index]->get_comment();
        }
    }

    return "";
}

//возвращает количество документов выбранного типа
int CController::get_document_size(DocumentType type)
{
    if (type < QUANTITY_TYPES)
    {
        return documents[type].size();
    }

    return 0;
}

//возвращает индекс выбранной продукции в виде строки
QString CController::get_item_index(int index)
{
    if (index < items.size())
    {
        return items[index]->get_id_str();
    }

    return "";
}

//возвращает название выбранной продукции в виде строки
QString CController::get_item_name(int index)
{
    if (index < items.size())
    {
        return items[index]->get_name();
    }

    return "";
}

//возвращает цену выбранной продукции в виде строки
QString CController::get_item_price(int index)
{
    if (index < items.size())
    {
        return items[index]->get_price_str();
    }

    return "";
}

//возвращает количество выбранной продукции в виде строки
QString CController::get_item_quantity(int index)
{
    if (index < items.size())
    {
        return items[index]->get_quantity_str();
    }

    return "";
}

//возвращает сумму для выбраннй продукции в виде строки
QString CController::get_item_sum(int index)
{
    if (index < items.size())
    {
        return items[index]->get_sum_str();
    }

    return "";
}

//возвращает время, необходимое на изготовление выбранной продукции, в виде строки
QString CController::get_item_production_time(int index)
{
    if (index < items.size())
    {
        return items[index]->get_production_time_str();
    }

    return "";
}

//возвращает общую сумму списка продукции в виде строки
float CController::get_item_total()
{
    float sum = 0.0;

    for (int i = 0; i < items.size(); i++)
    {
        sum += items[i]->sum();
    }

    return sum;
}

int CController::get_item_size()
{
    return items.size();
}

// проверяет, все ли документы сохранены
bool CController::is_saved()
{
    for (int type = ORDER; type < QUANTITY_TYPES; type++)
    {
        if (!is_saved((DocumentType)type))
        {
            return false;
        }
    }

    return true;
}

//проверяет, сохранен ли определенный тип документов
bool CController::is_saved(DocumentType type)
{
    if (type < QUANTITY_TYPES)
    {
        return saved[type];
    }

    return true;
}

//проверяет, подписан ли документ
bool CController::document_signed(DocumentType type, int index)
{
    if (type < QUANTITY_TYPES)
    {
        if (index < documents[type].size())
        {
            if (documents[type][index]->get_status())
            {
                return true;
            }
        }
    }

    return false;
}

bool CController::authorization(QString login, QString password)
{
    if (user != NULL)
    {
        delete user;
    }

    user = data_base.authorization(login, password);

    if (user != NULL)
    {
        return true;
    }

    return false;
}

//удаляем звездочку в конце строки
QString CController::delete_star(QString string)
{
    int index = string.length();
    --index;

    if (string.at(index) == '*')
    {
        string.chop(1);
    }

    return string;
}

//добавляем звездочку в конец строки, если ее там нет
QString CController::add_star(QString string)
{
    int index = string.length();
    --index;

    if (string.at(index) != '*')
    {
        string += "*";
    }

    return string;
}

QString CController::get_user_FIO()
{
    return user->get_surname() + " " + user->get_name() + " " + user->get_patronymic();
}

QString CController::get_user_surname()
{
    return user->get_surname();
}

QString CController::get_user_name()
{
    return user->get_name();
}

QString CController::get_user_patronymic()
{
    return user->get_patronymic();
}

QString CController::get_user_position()
{
    return user->get_position();
}

//отчищаем список заказов
void CController::clear_items()
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i] != NULL)
        {
            delete items[i];
            items[i] = NULL;
        }
    }

    items.clear();
}

//отчищаем список документов
void CController::clear_documents()
{
    for (int i = ORDER; i < QUANTITY_TYPES; i++)
    {
        for (int j = 0; j < documents[i].size(); j++)
        {
            if (documents[i][j] != NULL)
            {
                delete documents[i][j];
                documents[i][j] = NULL;
            }
        }

        documents[i].clear();
    }
}
