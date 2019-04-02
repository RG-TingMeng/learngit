//#include "xml.h"
//#include <QFile>
//#include <iostream>
//#include <QDebug>


//XmlStreamReader::XmlStreamReader()
//{

//}

///**
// * @brief 打开xml文件成功返回true,否则false
// */
//bool XmlStreamReader::readFile(const QString &fileName)
//{
//      QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        std::cerr << "Error:Cannot  read  file " <<qPrintable(fileName)
//                  << ": "<<qPrintable(file.errorString())
//                  <<std::endl;
//        return false;
//    }
//    reader.setDevice(&file);

//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isStartElement())
//        {
//            if(reader.name() == "text")
//            {
//                readTextMembers();
//            }
//            else
//            {
//                reader.raiseError(QObject::tr("Not a text file"));
//            }
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }

//    file.close();
//    if(reader.hasError())
//    {
//        std::cerr<<"Failed to parse file"
//                <<qPrintable(fileName)<<": "
//               <<qPrintable(reader.errorString()) <<std::endl;
//        return false;
//    }
//    else if(file.error() !=QFile::NoError)
//    {
//        std::cerr<<"Error: Cannot read file "<< qPrintable(fileName)
//                <<": "<<qPrintable(file.errorString())
//               <<std::endl;
//        return false;
//    }
//    return true;
//}

///**
// * @brief 读取文件的主体部分,跳过当前标签，遍历整个文件
// */
//void XmlStreamReader::readTextMembers()
//{
//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isEndElement())
//        {
//            reader.readNext();
//            break;
//        }

//        if(reader.isStartElement())
//        {
//            if(reader.name()=="entry")
//            {
//                readEntryMembers();
//            }
//            else
//            {
//                skipUnknownElement();
//            }
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }
//}

///**
// * @brief 读取entry标签
// */
//void XmlStreamReader::readEntryMembers()
//{
//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isEndElement())
//        {
//            reader.readNext();
//            break;
//        }

//        if(reader.isStartElement())
//        {
//            if(reader.name()=="entry")
//            {
//                readIp();
//            }
//            else
//            {
//                skipUnknownElement();
//            }
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }
//}

///**
// * @brief 读取ip标签的内容
// */
//void XmlStreamReader::readIp()
//{
//    std::string ip;
//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isEndElement())
//        {
//            reader.readNext();
//            break;
//        }

//        if(reader.isStartElement())
//        {
//            if(reader.name()=="ip")
//            {
//                ip = reader.readElementText().toStdString();
//            }
//            else
//            {
//                skipUnknownElement();
//            }
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }
//}

///**
// * @brief 读取port标签的内容
// */
//void XmlStreamReader::readPort()
//{
//    int port = 0;
//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isEndElement())
//        {
//            reader.readNext();
//            break;
//        }

//        if(reader.isStartElement())
//        {
//            if(reader.name()=="port")
//            {
//                port = reader.readElementText().toInt();
//            }
//            else
//            {
//                skipUnknownElement();
//            }
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }
//}

///**
// * @brief 跳过未知元素
// */
//void XmlStreamReader::skipUnknownElement()
//{
//    reader.readNext();
//    while(!reader.atEnd())
//    {
//        if(reader.isStartElement())
//        {
//            reader.readNext();
//            break;
//        }

//        if(reader.isStartElement())
//        {
//            skipUnknownElement();
//        }
//        else
//        {
//            reader.readNext();
//        }
//    }
//}
