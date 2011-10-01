#include <QtGui/QApplication>
#include "include/qdrawmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDrawMainWindow w;
    w.show();

    return a.exec();
}
