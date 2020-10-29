#ifndef FILE_HASH_HELPER_H
#define FILE_HASH_HELPER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMimeData>
#include <QList>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QThread>

#include "hashcode_calculate.h"//计算文件哈希值类

QT_BEGIN_NAMESPACE
namespace Ui { class File_Hash_Helper; }
QT_END_NAMESPACE

class File_Hash_Helper : public QMainWindow
{
    Q_OBJECT

public:
    File_Hash_Helper(QWidget *parent = nullptr);
    ~File_Hash_Helper();

    //子线程变量
    QThread childThread;

private slots:
    void on_btn_cal_clicked();//开始校验按钮按下槽函数

    void on_btn_export_clicked();//导出按钮按下槽函数

    void on_btn_findfile_clicked();//浏览按钮按下槽函数

    void on_le_ref_textChanged(const QString &arg1);

public slots:
    void showProgress(int prog);//显示进度槽函数

    void showResult(QString result);//显示结果槽函数 并进行一些后续工作

private:
    Ui::File_Hash_Helper *ui;

    //子界面变量
    QMainWindow* file_hash_export;

    //初始化界面
    void init_ui();

    //清空一些值
    void setEmpty();


    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;//拖放的东西进入后执行的函数
    void dropEvent(QDropEvent *event) override;//拖放的东西放下后执行的函数

signals:
    //开始计算信号
    void startHashCal(QString filename, QString algo);

};
#endif // FILE_HASH_HELPER_H
