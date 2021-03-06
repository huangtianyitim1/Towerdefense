#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QDialog>
#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include<QTime>
#include"mainwindow.h"
#include"prepare.h"
#include"gameover.h"
#include"help.h"
namespace Ui {
class start_window;
}

class start_window : public QDialog
{
    Q_OBJECT

public:
    explicit start_window(QWidget *parent = 0);
    ~start_window();

protected:
    void paintEvent(QPaintEvent *);


private slots:
    void on_pushButton_clicked();                         //按开始，跳转界面，同时隐藏封面
    void show_prepare();       //回到中场休息界面
    void showmain1();


    void on_pushButton_2_clicked();

private:
    Ui::start_window *ui;
    QImage background;
    Prepare *pre;
    MainWindow *w;
    gameover *g;
    help *h;
    int * is_checked;
    QMediaPlayer * warning;
};

#endif // START_WINDOW_H
