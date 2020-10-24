#ifndef FILE_HASH_EXPORT_H
#define FILE_HASH_EXPORT_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class File_Hash_Export;
}

class File_Hash_Export : public QMainWindow
{
    Q_OBJECT

public:
    explicit File_Hash_Export(QWidget *parent = nullptr);
    ~File_Hash_Export();

private:
    Ui::File_Hash_Export *ui;

};

#endif // FILE_HASH_EXPORT_H
