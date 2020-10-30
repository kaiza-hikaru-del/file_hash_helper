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
        //若进度变化吗没有0.1% 直接继续计算 不送信号也不改变值
        if(nowProg == (caledsize * 1000) / filesize)
            continue;
        nowProg = (caledsize * 1000) / filesize;
        emit nowProgress(nowProg);
    }
    QByteArray Hashcode = Hash.result();
    file.close();
    //计算完成 送出结束信号
    emit finishHashCal(QString(Hashcode.toHex()).toUpper());
}

//导出部分 计算文件哈希值
void Hashcode_Calculate::exportCalHashCode(QString filename, QString algos)
{
    qDebug() << filename << "," << algos;
    //声明一些变量
    const qint64 oneMega = 1024*1024;
    qint64 filesize;
    qint64 caledsize = 0;
    int nowProg = 0;
    int algoNum = 0;
    //算法字符串常量 占位[0]用不到
    const QString constAlgoList[7] = {"MD4","MD5","SHA-1","SHA-224","SHA-256","SHA-384","SHA-512"};

    //文件相关
    QFile file(filename);
    QFileInfo fileinfo(filename);
    QString result = fileinfo.fileName() + ": \n";
    filesize = fileinfo.size();

    //解析算法字符串
    QStringList algolist = algos.split('_');
    qDebug() << algolist;
    algoNum = algolist.size();
    QCryptographicHash::Algorithm Algos[algoNum];
    for(int i = 0; i < algoNum; i++){
        if(algolist.at(i) == "MD5")
            Algos[i] = QCryptographicHash::Md5;
        else if(algolist.at(i) == "SHA-1")
            Algos[i] = QCryptographicHash::Sha1;
        else if(algolist.at(i) == "SHA-224")
            Algos[i] = QCryptographicHash::Sha224;
        else if(algolist.at(i) == "SHA-256")
            Algos[i] = QCryptographicHash::Sha256;
        else if(algolist.at(i) == "SHA-384")
            Algos[i] = QCryptographicHash::Sha384;
        else if(algolist.at(i) == "SHA-512")
            Algos[i] = QCryptographicHash::Sha512;
    }

    //核心算法
    for(int i = 0; i < algoNum; i++){
        file.open(QIODevice::ReadOnly);
        QCryptographicHash Hash(Algos[i]);
        while (!file.atEnd()) {
            //最核心
            QByteArray buf = file.read(oneMega);
            Hash.addData(buf);
            //送进度信号
            caledsize += oneMega;
            //若进度变化吗没有0.1% 直接继续计算 不送信号也不改变值
            if(nowProg == (caledsize * 1000) / (filesize * algoNum))
                continue;
            nowProg = (caledsize * 1000) / (filesize * algoNum);
            emit exportProgress(nowProg);
        }
        QByteArray Hashcode = Hash.result();
        QString hashresult = Hashcode.toHex().toUpper();

        if(Algos[i] == QCryptographicHash::Md5 || Algos[i] == QCryptographicHash::Sha1)
            result += constAlgoList[Algos[i]] + ":\t\t" + hashresult + "\n";
        else
            result += constAlgoList[Algos[i]] + ":\t" + hashresult + "\n";

        file.close();
    }
    qDebug() << "export calculate finished";
    emit finishExportCal(result);
}

