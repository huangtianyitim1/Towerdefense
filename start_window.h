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
    void on_pushButton_clicked();                         //����ʼ����ת���棬ͬʱ���ط���

signals:
    void showmain1();


private:
    Ui::start_window *ui;
    QImage background;
};

#endif // START_WINDOW_H
