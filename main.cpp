#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleTCPChat w;
    w.show();
    return QApplication::exec();
}
