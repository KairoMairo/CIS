#include "user.h"


CUser::CUser(int id,
             QString name,
             QString surname,
             QString patronymic,
             QString position,
             float salary,
             float working_hours)
{
    _id =               id;
    _name =             name;
    _surname =          surname;
    _patronymic =       patronymic;
    _position =         position;
    _salary =           salary;
    _working_hours =    working_hours;
}

QString CUser::get_surname()
{
    return _surname;
}

QString CUser::get_name()
{
    return _name;
}

QString CUser::get_patronymic()
{
    return _patronymic;
}

QString CUser::get_position()
{
    return _position;
}
