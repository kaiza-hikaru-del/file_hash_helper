#include "file_hash_helper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    File_Hash_Helper w;
    w.show();
    return a.exec();
}
