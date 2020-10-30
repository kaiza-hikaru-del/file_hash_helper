#ifndef FILE_HASH_EXPORT_H
#define FILE_HASH_EXPORT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QThread>
#include <QMessageBox>

#include "hashcode_calculate.h" //计算哈希值头文件

namespace Ui {
class File_Hash_Export;
}

class File_Hash_Export : public QMainWindow
{
    Q_OBJECT

public:
    explicit File_Hash_Export(QWidget *parent = nullptr);
    ~File_Hash_Export();

    void setFilename(QString filename);

    void setDefault(QString filename);

    QThread childHashThread;//子线程变量

public slots:
    void showProgress(int prog);
    void exportFile(QString result);

private slots:
    void on_btn_exit_clicked();//退出按钮按下槽函数

    void on_btn_finddir_clicked();

    void on_btn_export_clicked();

private:
    Ui::File_Hash_Export *ui;

    QString filename;//原文件名
    QString exportFilename;//导出文件名


signals:
    void startExport(QString filename, QString algolist);

};

#endif // FILE_HASH_EXPORT_H
