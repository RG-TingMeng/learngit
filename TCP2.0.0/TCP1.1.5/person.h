/**
 * @brief 写的“人”类
 * @details 描述学生基本信息
 * @author ctm
 * @version 1.0.7
 * @date 2019.4.3
 * @warning
 * @copyright
 * @note
 */

#ifndef PERSON_H
#define PERSON_H

#include <QString>
class Person
{
public:
    Person();
    Person &operator  = (const Person & t_person);

    void setDateLength(int t_dateLength);
    int getDateLength();

    void setComboBoxIndex(int t_comboBoxIndex);
    int getComboBoxIndex();

    void setNameLength(int t_nameLength);
    int getNameLength();

    void setName(QString t_name);
    QString getName()const;

    void setAge(int t_age);
    int getAge()const;
private:
    int m_dateLength;
    int m_comboBoxIndex;
    int m_nameLength;
    int m_age;
    QString m_name;


};

#endif // PERSON_H
