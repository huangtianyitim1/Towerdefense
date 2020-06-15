#include "mainwindow.h"
#include <QApplication>
#include"start_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start_window  s;
    //MainWindow w;
    s.show();
    //QObject::connect(&s, SIGNAL(showmain1()), &w, SLOT(recieve_start()));

    return a.exec();
}
