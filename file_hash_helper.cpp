#include "file_hash_helper.h"
#include "ui_file_hash_helper.h"

File_Hash_Helper::File_Hash_Helper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::File_Hash_Helper)
{
    ui->setupUi(this);
    //初始化界面
    this->init_ui();
}

File_Hash_Helper::~File_Hash_Helper()
{
    delete ui;
}

//初始化界面
void File_Hash_Helper::init_ui()
{
    //设置行列数 1*2
    this->ui->tableWidget->setColumnCount(2);
    this->ui->tableWidget->setRowCount(1);
    //设置不显示行号
    this->ui->tableWidget->verticalHeader()->setVisible(false);
    //设置列表头内容
    this->ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("算法"));
    this->ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("哈希值"));
    //设置表内容与对齐方式
    this->ui->tableWidget->setItem(0,0,new QTableWidgetItem(""));
    this->ui->tableWidget->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->ui->tableWidget->setItem(0,1,new QTableWidgetItem(""));
    //设置列宽
    this->ui->tableWidget->setColumnWidth(0,60);
    this->ui->tableWidget->setColumnWidth(1,325);
    //设置表格为只读
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

