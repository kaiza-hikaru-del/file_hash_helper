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

//显示进度
void File_Hash_Export::showProgress(int prog)
{

}

//导出结果
void File_Hash_Export::exportFile(QString result)
{

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
