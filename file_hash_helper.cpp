#include "file_hash_helper.h"
#include "ui_file_hash_helper.h"
#include "file_hash_export.h"

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
//    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->item(0,0)->setFlags(Qt::NoItemFlags);
    this->ui->tableWidget->item(0,1)->setFlags(Qt::NoItemFlags);
    //设置结果栏为空
    this->ui->l_result->setText("");
    //设置icon
    this->setWindowIcon(QIcon(":/icon/Logo.svg"));
}

//拖放的东西进入后执行函数
void File_Hash_Helper::dragEnterEvent(QDragEnterEvent *event)
{
    //若拖入的东西有url 则接受拖拽
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

//拖放的东西放下后执行函数
void File_Hash_Helper::dropEvent(QDropEvent *event)
{
    //当拖入的东西有url 进行处理只保留一个文件
    if(event->mimeData()->hasUrls())
    {
        QList<QUrl> fileUrls = event->mimeData()->urls();
        //拖入多文件
        if(fileUrls.size()>1){
            QMessageBox::critical(this,"错误！","请拖入<b>一个</b>文件！");
            return;
        }
        QString filename = fileUrls.first().toLocalFile();
        qDebug() << filename;
        QFileInfo fileinfo(filename);
        //拖入的不是文件
        if(!fileinfo.isFile()){
            QMessageBox::critical(this,"错误！","请拖入一个<b>文件</b>！");
            return;
        }
         //如果写入值与原先值一样则直接返回
        if(filename == this->ui->le_file->text())
            return;

        //剩下的是合法情况 写入lineEdit
        this->ui->le_file->setText(filename);


        //清空一些值
        this->ui->progressBar->setValue(0);
        this->ui->tableWidget->setItem(0,0,new QTableWidgetItem(""));
        this->ui->tableWidget->setItem(0,1,new QTableWidgetItem(""));
        this->ui->l_result->setText("");
    }
}

//开始校验按钮按下槽函数
void File_Hash_Helper::on_btn_cal_clicked()
{
//    this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/newWrong.svg").scaled(100,100,Qt::KeepAspectRatio)));
}

//导出按钮按下槽函数
void File_Hash_Helper::on_btn_export_clicked()
{
    //新建窗口对象
    this->file_hash_export = new File_Hash_Export(this);
    //显示该模态窗口
    this->file_hash_export->show();
}

//浏览按钮按下槽函数
void File_Hash_Helper::on_btn_findfile_clicked()
{
    //文件选择器
    QString filename = QFileDialog::getOpenFileName(this,"请选择文件",nullptr,nullptr);
    qDebug() << filename;
    //若未打开任何文件 直接返回
    if(filename.isEmpty())
        return;

    //如果写入值与原先值一样则直接返回
   if(filename == this->ui->le_file->text())
       return;

    //成功则写入lineEdit
    this->ui->le_file->setText(filename);
    //清空一些值
    this->ui->progressBar->setValue(0);
    this->ui->tableWidget->setItem(0,0,new QTableWidgetItem(""));
    this->ui->tableWidget->setItem(0,1,new QTableWidgetItem(""));
    this->ui->l_result->setText("");
}

