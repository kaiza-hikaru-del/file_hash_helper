#ifndef HASHCODE_CALCULATE_H
#define HASHCODE_CALCULATE_H

#include <QObject>
#include <QDebug>
#include <QThread>  //延时函数 测试用
#include <QCryptographicHash>   //哈希函数头文件 核心
#include <QFile>
#include <QFileInfo>    //文件相关头文件

class Hashcode_Calculate : public QObject
{
    Q_OBJECT
public:
    explicit Hashcode_Calculate(QObject *parent = nullptr);

public slots:
    void calHashcode(QString filename, QString algo);

signals:
    void nowProgress(int prog);
    void finishHashCal(QString result);

};

#endif // HASHCODE_CALCULATE_H
