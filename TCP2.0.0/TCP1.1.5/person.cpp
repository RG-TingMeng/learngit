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

/**
 * @brief 设置类person数据成员数据(包括4部分)总长度
 */
void Person::setDateLength(int t_dateLength)
{
    m_dateLength = t_dateLength;
}

/**
 * @brief 获取类person数据成员数据总长度
 */
int Person::getDateLength()
{
    return m_dateLength;
}

/**
 * @brief 设置类person数据成员下拉选项框的索引值
 */
void Person::setComboBoxIndex(int t_comboBoxIndex)
{
    m_comboBoxIndex = t_comboBoxIndex;
}

/**
 * @brief 获取类person数据成员下拉选项框索引值
 */
int Person::getComboBoxIndex()
{
    return m_comboBoxIndex;
}

/**
 * @brief 设置类person数据成员name的长度
 */
void Person::setNameLength(int t_nameLength)
{
        m_nameLength = t_nameLength;
}

/**
 * @brief 获取类person数据成员name的长度
 */
int Person::getNameLength()
{
    return m_nameLength;
}

/**
 * @brief 设置类person数据成员name
 */
void Person::setName(QString t_name)
{
    m_name = t_name;
}

/**
 * @brief 获取类person数据成员name
 */
QString Person::getName() const
{
    return m_name;
}

/**
 * @brief 设置类person数据成员age
 */
void Person::setAge(int t_age)
{
    m_age = t_age;
}

/**
  * @brief 获取类person数据成员age
  */
 int Person::getAge()const
{
    return m_age;
}
