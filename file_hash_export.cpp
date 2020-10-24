#include "file_hash_export.h"
#include "ui_file_hash_export.h"

File_Hash_Export::File_Hash_Export(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::File_Hash_Export)
{
    ui->setupUi(this);
    //设置本窗口为模态窗口
    this->setWindowModality(Qt::WindowModal);
}

File_Hash_Export::~File_Hash_Export()
{
    delete ui;
}

