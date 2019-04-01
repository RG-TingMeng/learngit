#ifndef STUDENT_H
#define STUDENT_H

#include<QString>

class Student
{
private:
    QString m_name;
    int m_age;
public:
    Student();
    QString setName(QString);
    int setAge(int);
    QString getName();
    int getAge();
    Student & operator =(Student &stu);
};
#endif // STUDENT_H
