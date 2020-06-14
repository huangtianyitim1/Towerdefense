#include "mainwindow.h"
#include <QApplication>
#include"start_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start_window  s;
    s.show();

    return a.exec();
}
