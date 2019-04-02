#include "student.h"
#include <QDebug>


Student::Student()
{
    qDebug()<<"init";
}

QString Student::setName(QString name)
{
    m_name = name;
    return m_name;
}

int Student::setAge(int age)
{
    m_age = age;
    return m_age;
}

QString Student::getName()
{
    return m_name;
}

int Student::getAge()
{
    return m_age;
}

Student &Student::operator =(Student &stu)
{
 this->m_name = stu.m_name;
 this->m_age = stu.m_age;
 return *this;
}
