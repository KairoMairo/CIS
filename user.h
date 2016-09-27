#ifndef CUSER_H
#define CUSER_H

#include <QString>

class CUser
{
public:
    CUser(int id,
          QString name,
          QString surname,
          QString patronymic,
          QString position,
          float salary,
          float working_hours);

    QString get_surname();
    QString get_name();
    QString get_patronymic();
    QString get_position();

private:
    int _id;

    float _salary;
    float _working_hours;

    QString _surname;
    QString _name;
    QString _patronymic;
    QString _position;

};

#endif // CUSER_H
