#include "hashcode_calculate.h"

Hashcode_Calculate::Hashcode_Calculate(QObject *parent) : QObject(parent)
{

}

//计算哈希值函数
void Hashcode_Calculate::calHashcode(QString filename, QString algo)
{
    qDebug() << filename << "," << algo;
    //声明一些变量
    const qint64 oneMega = 1024*1024;
    qint64 filesize;
    qint64 caledsize = 0;
    int nowProg = 0;
    QCryptographicHash::Algorithm Algo;

    //选择算法
    if(algo == "MD5")
        Algo = QCryptographicHash::Md5;
    else if(algo == "SHA-1")
        Algo = QCryptographicHash::Sha1;
    else if(algo == "SHA-224")
        Algo = QCryptographicHash::Sha224;
    else if(algo == "SHA-256")
        Algo = QCryptographicHash::Sha256;
    else if(algo == "SHA-384")
        Algo = QCryptographicHash::Sha384;
    else if(algo == "SHA-512")
        Algo = QCryptographicHash::Sha512;
    else{
        qDebug() << "Something wrong!";
        return;
    }

    //文件相关
    QFile file(filename);
    QFileInfo fileinfo(filename);
    filesize = fileinfo.size();

    //核心计算
    file.open(QIODevice::ReadOnly);
    QCryptographicHash Hash(Algo);
    while (!file.atEnd()) {
        //最核心
        QByteArray buf = file.read(oneMega);
        Hash.addData(buf);
        //送进度信号
        caledsize += oneMega;
        //若进度变化吗没有1% 直接继续计算 不送信号也不改变值
        if(nowProg == (caledsize * 100) / filesize)
            continue;
        nowProg = (caledsize * 100) / filesize;
        emit nowProgress(nowProg);
    }
    QByteArray Hashcode = Hash.result();
    //计算完成 送出结束信号
    emit finishHashCal(QString(Hashcode.toHex()).toUpper());
}
