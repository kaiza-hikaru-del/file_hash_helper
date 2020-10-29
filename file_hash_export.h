#ifndef FILE_HASH_EXPORT_H
#define FILE_HASH_EXPORT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

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

private slots:
    void on_btn_exit_clicked();//退出按钮按下槽函数

    void on_btn_finddir_clicked();

private:
    Ui::File_Hash_Export *ui;

};

#endif // FILE_HASH_EXPORT_H
