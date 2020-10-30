#include "file_hash_export.h"
#include "ui_file_hash_export.h"

File_Hash_Export::File_Hash_Export(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::File_Hash_Export)
{
    ui->setupUi(this);
    //设置本窗口为模态窗口
    this->setWindowModality(Qt::WindowModal);
    //子线程设置
    Hashcode_Calculate* calculator = new Hashcode_Calculate;
    calculator->moveToThread(&this->childHashThread);
    //关联相关信号与槽
    connect(&this->childHashThread,&QThread::finished,calculator,&Hashcode_Calculate::deleteLater);
    connect(this,&File_Hash_Export::startExport,calculator,&Hashcode_Calculate::exportCalHashCode);
    connect(calculator,&Hashcode_Calculate::exportProgress,this,&File_Hash_Export::showProgress);
    connect(calculator,&Hashcode_Calculate::finishExportCal,this,&File_Hash_Export::exportFile);
    //开启子线程
    this->childHashThread.start();
}

File_Hash_Export::~File_Hash_Export()
{
    //结束线程
    this->childHashThread.quit();
    this->childHashThread.wait();
    qDebug() << "Threads closed in export";
    delete ui;
}

//显示进度
void File_Hash_Export::showProgress(int prog)
{
    this->ui->progressBar->setValue(prog);
}

//导出结果
void File_Hash_Export::exportFile(QString result)
{
    QFile exportFile(this->exportFilename);
    exportFile.open(QIODevice::WriteOnly);
    QByteArray content = result.toUtf8();
    exportFile.write(content);
    exportFile.close();
    //解冻窗口 设置进度条 并弹出导出成功消息框
    this->ui->progressBar->setValue(1000);
    this->setEnabled(true);
    QMessageBox::about(this,"导出成功！","文件导出成功！");
}

//退出按钮按下槽函数
void File_Hash_Export::on_btn_exit_clicked()
{
    close();
}

//浏览按钮按下槽函数
void File_Hash_Export::on_btn_finddir_clicked()
{
    QString filedir = QFileDialog::getExistingDirectory(this,"请选择文件夹",nullptr);
    qDebug() << filedir;
    //若没有打开文件夹 直接返回
    if(filedir.isEmpty())
        return;
    //若打开文件夹与原先一样 直接返回
    if(filedir == this->ui->le_dir->text())
        return;

    this->ui->le_dir->setText(filedir);
    //将一些值清零
    this->ui->progressBar->setValue(0);
}

//设置文件名
void File_Hash_Export::setFilename(QString filename)
{
    this->filename = filename;
}

//设置默认路径
void File_Hash_Export::setDefault(QString filename)
{
    QFileInfo fileinfo(filename);
    this->ui->le_dir->setText(fileinfo.absolutePath()+"/");
}

//导出按钮按下
void File_Hash_Export::on_btn_export_clicked()
{
    //解析复选框
    QString algos;
    if(this->ui->cb_md5->isChecked())
        algos.append("MD5_");
    if(this->ui->cb_sha1->isChecked())
        algos.append("SHA-1_");
    if(this->ui->cb_sha224->isChecked())
        algos.append("SHA-224_");
    if(this->ui->cb_sha256->isChecked())
        algos.append("SHA-256_");
    if(this->ui->cb_sha384->isChecked())
        algos.append("SHA-384_");
    if(this->ui->cb_sha512->isChecked())
        algos.append("SHA-512_");
    //去掉最后一个"_"
    algos = algos.left(algos.length()-1);
    qDebug() << algos;

    //导出文件名 xxx.yyy_algo1_algo2.txt
    QFileInfo fileinfo(this->filename);
    this->exportFilename = this->ui->le_dir->text()+fileinfo.fileName()+"_"+algos+".txt";
    //若有重名文件
    qDebug() << this->exportFilename;
    QFile exportFile(this->exportFilename);
    if(exportFile.exists()){
        qDebug() << "File exist!";
        QString message = "文件已存在！<br/>" + this->exportFilename + "<br/>请尝试<b>删除同名文件</b>后重试";
        qDebug() << message;
        QMessageBox::critical(this,"错误",message);
        return;
    }
    //冻结窗口
    this->setEnabled(false);
    //清除一些值
    this->ui->progressBar->setValue(0);
    emit startExport(this->filename, algos);
}
