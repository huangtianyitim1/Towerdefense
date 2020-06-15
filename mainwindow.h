#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include<QTime>
#include"map1.h"
#include<vector>
#include"tower.h"
#include<QString>
#include"enemy_s.h"
#include"tower_s.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initgame();
    void draw(QPainter &p);
    Enemy* gen_enemy();    //返回一个指向某一子类敌人的基类指针
    int no_tower(int x, int y);   //判断这里 是否有塔，没有返回-999，有的话返回当前鼠标塔的索引

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);


private slots:
    void recieve_start();

private:
    Ui::MainWindow *ui;
    static const int WINDOW_W=900;  //界面宽
    const static int WINDOW_H=600;
    static const int MARGIN=0;  //游戏边界
    QImage dot, map, remove, up, cancel;
    vector <Enemy *> e1 ;  //一群敌人(不一定类型相同)的指针
    int timerid1; //敌人移动刷新的id
    static int e_spd;  //敌人移动刷新的频率
    int timerid2;
    static int e_spd2; //敌人产生的频率
    int timerid3;  //子弹刷新产生id
    static int e_spd3;  //子弹产生频率
    int timerid4;  //子弹刷新移动id
    static int e_spd4;  //子弹移动刷新频率
    map1 m1;
    QTime time;
    vector <Tower *> tw;
    int score=0;    //分数
    QString s_score;  //分数文字
    int m2p=0;   //鼠标和画图连接的信号
    int tw_i;  //塔的索引记录
    QImage type1_pic, type2_pic, type3_pic;
    int local_x, local_y;  //针对=拖动用的鼠标位置
    int type_id; //塔的种类
};

#endif // MAINWINDOW_H
