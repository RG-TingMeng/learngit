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
 * @brief ������person���ݳ�Ա����(����4����)�ܳ���
 */
void Person::setDateLength(int t_dateLength)
{
    m_dateLength = t_dateLength;
}

/**
 * @brief ��ȡ��person���ݳ�Ա�����ܳ���
 */
int Person::getDateLength()
{
    return m_dateLength;
}

/**
 * @brief ������person���ݳ�Ա����ѡ��������ֵ
 */
void Person::setComboBoxIndex(int t_comboBoxIndex)
{
    m_comboBoxIndex = t_comboBoxIndex;
}

/**
 * @brief ��ȡ��person���ݳ�Ա����ѡ�������ֵ
 */
int Person::getComboBoxIndex()
{
    return m_comboBoxIndex;
}

/**
 * @brief ������person���ݳ�Աname�ĳ���
 */
void Person::setNameLength(int t_nameLength)
{
        m_nameLength = t_nameLength;
}

/**
 * @brief ��ȡ��person���ݳ�Աname�ĳ���
 */
int Person::getNameLength()
{
    return m_nameLength;
}

/**
 * @brief ������person���ݳ�Աname
 */
void Person::setName(QString t_name)
{
    m_name = t_name;
}

/**
 * @brief ��ȡ��person���ݳ�Աname
 */
QString Person::getName() const
{
    return m_name;
}

/**
 * @brief ������person���ݳ�Աage
 */
void Person::setAge(int t_age)
{
    m_age = t_age;
}

/**
  * @brief ��ȡ��person���ݳ�Աage
  */
 int Person::getAge()const
{
    return m_age;
}
