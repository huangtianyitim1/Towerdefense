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
using namespace std;

class Bullet{
protected:
    double x,y;   //坐标
    double ex, ey;  //敌人坐标
    static int w,h; //画面大小
    double steps;  //速度
    double power;  //伤害
    double dir; //定位放向:和x正轴夹角,弧度
    QImage pic_b;
    Enemy* e;                   //记录锁定的敌人
    int type_id;     //子弹种类id
public:
    Bullet(){}
    virtual~Bullet(){}
    virtual void set(double x, double y, Enemy *p);  //位置  和锁定的敌人
    double getdir() const {return dir;}             //返回方向
    void setspd(double s);                      //设置速度
    void setpower(double p);                     //设置威力
    void show(QPainter&p);
    virtual void loadimage();
    bool shootdown();                      //打中和扣血
    double getx() const{ return x;}
    double gety() const{ return y;}
    int getp() const{ return power;}        //返回威力
    void move();             //子弹移动
};
#endif // BULLET_H
