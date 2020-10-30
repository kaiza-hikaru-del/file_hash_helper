#include "file_hash_helper.h"
#include "ui_file_hash_helper.h"


File_Hash_Helper::File_Hash_Helper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::File_Hash_Helper)
{
    ui->setupUi(this);
    //初始化界面
    this->init_ui();
    //打开即开启子线程
    Hashcode_Calculate* calculator = new Hashcode_Calculate;
    calculator->moveToThread(&this->childThread);
    //关联线程结束处理
    connect(&this->childThread,&QThread::finished,calculator,&Hashcode_Calculate::deleteLater);
    //关联开始信号与计算函数
    connect(this,&File_Hash_Helper::startHashCal,calculator,&Hashcode_Calculate::calHashcode);
    //关联进度信号与处理函数
    connect(calculator,&Hashcode_Calculate::nowProgress,this,&File_Hash_Helper::showProgress);
    //关联结果型号与处理函数
    connect(calculator,&Hashcode_Calculate::finishHashCal,this,&File_Hash_Helper::showResult);
    //开启子线程
    this->childThread.start();
}

File_Hash_Helper::~File_Hash_Helper()
{
    //使线程结束
    this->childThread.quit();
    this->childThread.wait();
    qDebug() << "Threads closed!";
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
    //设置列宽与不可调
    this->ui->tableWidget->setColumnWidth(0,60);
//    this->ui->tableWidget->setColumnWidth(1,325);
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);//固定列宽
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//活动列宽 但不能被用户更改
    //设置表格为只读
    this->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidget->item(0,0)->setFlags(Qt::NoItemFlags);
    this->ui->tableWidget->item(0,1)->setFlags(Qt::NoItemFlags);
    //设置结果栏为空
    this->ui->l_result->setText("");
    //设置icon
    this->setWindowIcon(QIcon(":/icon/Logo.svg"));
    //设置结果显示栏为一张其他图片
    this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/Logo.svg").scaled(100,100,Qt::KeepAspectRatio)));
}

//清空一些值
void File_Hash_Helper::setEmpty()
{
    //进度条置0
    this->ui->progressBar->setValue(0);
    //表格元素置空
    this->ui->tableWidget->setItem(0,0,new QTableWidgetItem(""));
    this->ui->tableWidget->setItem(0,1,new QTableWidgetItem(""));
    //结果置空
    this->ui->l_result->setText("");
    //设置结果显示栏为一张其他图片
    this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/Logo.svg").scaled(100,100,Qt::KeepAspectRatio)));
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
            QMessageBox::critical(this,"错误","请拖入<b>一个</b>文件！");
            return;
        }
        QString filename = fileUrls.first().toLocalFile();
        qDebug() << filename;
        QFileInfo fileinfo(filename);
        //拖入的不是文件
        if(!fileinfo.isFile()){
            QMessageBox::critical(this,"错误","请拖入一个<b>文件</b>！");
            return;
        }
         //如果写入值与原先值一样则直接返回
        if(filename == this->ui->le_file->text())
            return;

        //剩下的是合法情况 写入lineEdit
        this->ui->le_file->setText(filename);


        //清空一些值
        this->setEmpty();
    }
}

//开始校验按钮按下槽函数
void File_Hash_Helper::on_btn_cal_clicked()
{
    //若打不开文件
    QFile file(this->ui->le_file->text());
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Cannot open file!";
        QMessageBox::critical(this,"错误","请<b>打开</b>一个文件！");
        return;
    }

    //清空一些值
    this->setEmpty();
    //冻结窗口 待计算完成释放 释放在处理结果函数
    this->setEnabled(false);
    //发出计算信号 交由子线程处理
    emit startHashCal(this->ui->le_file->text(),this->ui->cb_algo->currentText());
}

//导出按钮按下槽函数
void File_Hash_Helper::on_btn_export_clicked()
{
    //若打不开文件
    QFile file(this->ui->le_file->text());
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Cannot open file!";
        QMessageBox::critical(this,"错误","请<b>打开</b>一个文件！");
        return;
    }

    //新建窗口对象
    this->file_hash_export = new File_Hash_Export(this);
    //传入参数 并设置默认路径
    this->file_hash_export->setFilename(this->ui->le_file->text());
    this->file_hash_export->setDefault(this->ui->le_file->text());
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
   this->setEmpty();
}

//显示进度
void File_Hash_Helper::showProgress(int prog)
{
    this->ui->progressBar->setValue(prog);
}

//显示结果
void File_Hash_Helper::showResult(QString result)
{
    this->ui->tableWidget->setItem(0,0,new QTableWidgetItem(this->ui->cb_algo->currentText()));
    this->ui->tableWidget->setItem(0,1,new QTableWidgetItem(result));
    //将进度条置最大值
    this->ui->progressBar->setValue(1000);
    //解冻窗口
    this->setEnabled(true);
    //若不存在参考值则直接退出
    if(this->ui->le_ref->text().isEmpty()){
        qDebug() << "Finish calculating but no reference!";
        return;
    }

    //存在参考值则显示结果
    if(result == this->ui->le_ref->text().toUpper())
        this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/newCorrect.svg").scaled(100,100,Qt::KeepAspectRatio)));
    else
        this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/newWrong.svg").scaled(100,100,Qt::KeepAspectRatio)));

}

//参考值改变时
void File_Hash_Helper::on_le_ref_textChanged(const QString &arg1)
{
    //测试用
    qDebug() << arg1;
    //若表格内无结果
    if(this->ui->tableWidget->item(0,1)->text().trimmed().isEmpty()){
        qDebug() << "No result!";
        return;
    }
    //若参考值本身也没有
    if(arg1.trimmed().isEmpty()){
        qDebug() << "No reference!";
        //清空结果
        //设置结果显示栏为一张其他图片
        this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/Logo.svg").scaled(100,100,Qt::KeepAspectRatio)));
        return;
    }
    //若有结果改变比对结果
    if(arg1.trimmed().toUpper() == this->ui->tableWidget->item(0,1)->text().trimmed())
        this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/newCorrect.svg").scaled(100,100,Qt::KeepAspectRatio)));
    else
        this->ui->l_result->setPixmap(QPixmap::fromImage(QImage(":/icon/newWrong.svg").scaled(100,100,Qt::KeepAspectRatio)));
}

//算法改变时
void File_Hash_Helper::on_cb_algo_currentIndexChanged(const QString &arg1)
{
    qDebug() << arg1;
    //直接清空一些值
    this->setEmpty();
}

//复制结果
void File_Hash_Helper::on_btn_copyresult_clicked()
{
    //若没有结果
    if(this->ui->tableWidget->item(0,1)->text().isEmpty()){
        qDebug() << "no result";
        QMessageBox::warning(this,"警告","没有结果！");
        return;
    }

    QClipboard* clipboard = QApplication::clipboard();
    QString result = this->ui->tableWidget->item(0,1)->text();
    clipboard->setText(result);
    QMessageBox::about(this,"复制成功","已将结果复制到剪贴板！");
}
