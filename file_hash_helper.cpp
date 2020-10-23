#include "file_hash_helper.h"
#include "ui_file_hash_helper.h"

File_Hash_Helper::File_Hash_Helper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::File_Hash_Helper)
{
    ui->setupUi(this);
}

File_Hash_Helper::~File_Hash_Helper()
{
    delete ui;
}

