#include "person.h"

Person::Person()
{

}

Person &Person::operator =(const Person & t_person)
{
    this->m_name = t_person.m_name;
    this->m_age = t_person.m_age;
    return *this;
}

void Person::setDateLength(int t_dateLength)
{
    m_dateLength = t_dateLength;
}

int Person::getDateLength()
{
    return m_dateLength;
}

void Person::setComboBoxIndex(int t_comboBoxIndex)
{
    m_comboBoxIndex = t_comboBoxIndex;
}

int Person::getComboBoxIndex()
{
    return m_comboBoxIndex;
}

void Person::setNameLength(int t_nameLength)
{
        m_nameLength = t_nameLength;
}

int Person::getNameLength()
{
    return m_nameLength;
}

void Person::setName(QString t_name)
{
    m_name = t_name;
}

QString Person::getName()
{
    return m_name;
}

void Person::setAge(int t_age)
{
    m_age = t_age;
}

int Person::getAge()
{
    return m_age;
}

//QDebug &Person::operator << (QDebug os,Person t_person)
//{
//    os << "t_person.DateLength:" <<t_person.m_dateLength
//       <<"t_person.ComboBoxIndex:" <<t_person.m_comboBoxIndex
//      <<"t_person.NameLength:" <<t_person.m_nameLength
//     <<"t_person.name:" <<t_person.m_name
//    <<"t_person.age:" <<t_person.m_age;
//    return os;
//}
