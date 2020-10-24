#ifndef FILE_HASH_HELPER_H
#define FILE_HASH_HELPER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class File_Hash_Helper; }
QT_END_NAMESPACE

class File_Hash_Helper : public QMainWindow
{
    Q_OBJECT

public:
    File_Hash_Helper(QWidget *parent = nullptr);
    ~File_Hash_Helper();

private:
    Ui::File_Hash_Helper *ui;

    //初始化界面
    void init_ui();
};
#endif // FILE_HASH_HELPER_H
