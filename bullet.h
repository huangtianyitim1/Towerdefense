#ifndef BULLET_H
#define BULLET_H
#include<QPainter>
#include<cmath>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include<iostream>
#include"enemy_s.h"

class Bullet{
protected:
    double x,y;   //坐标
    double ex, ey;  //敌人坐标
    static int w,h; //画面大小
    double steps=5;  //速度
    int power=5;  //伤害
    double dir; //定位放向:和x正轴夹角,弧度
    QImage pic_b;
    Enemy* e;                   //记录锁定的敌人
public:
    Bullet(){}
    void set(double x, double y, Enemy *p);  //位置  和锁定的敌人
    double getdir() const {return dir;}             //返回方向
    void setspd(double s);                      //设置速度
    void show(QPainter&p);
    void loadimage();
    bool shootdown();                      //打中和扣血
    double getx() const{ return x;}
    double gety() const{ return y;}
    int getp() const{ return power;}        //返回威力
    void setp(int p);          //设置速度
    void move();             //子弹移动
};
#endif // BULLET_H
