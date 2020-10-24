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

QT_BEGIN_NAMESPACE
namespace Ui { class File_Hash_Helper; }
QT_END_NAMESPACE

class File_Hash_Helper : public QMainWindow
{
    Q_OBJECT

public:
    File_Hash_Helper(QWidget *parent = nullptr);
    ~File_Hash_Helper();

private slots:
    void on_btn_cal_clicked();//开始校验按钮按下槽函数

    void on_btn_export_clicked();//导出按钮按下槽函数

    void on_btn_findfile_clicked();//浏览按钮按下槽函数

private:
    Ui::File_Hash_Helper *ui;

    //子界面变量
    QMainWindow* file_hash_export;

    //初始化界面
    void init_ui();


    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;//拖放的东西进入后执行的函数
    void dropEvent(QDropEvent *event) override;//拖放的东西放下后执行的函数
};
#endif // FILE_HASH_HELPER_H
