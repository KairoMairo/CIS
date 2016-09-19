#include "part.h"


CPart::CPart(int id, QString name)
{
    _id = id;
    _name = name;
}

int CPart::get_id()
{
    return _id;
}

int CPart::get_current_process_id()
{
    if (!_processes.isEmpty())
    {
        return _processes.first();
    }

    return 0;
}

int CPart::get_process_id(int index)
{
    if (index >= 0 && index < _processes.size())
    {
        return _processes[index];
    }

    return 0;
}
