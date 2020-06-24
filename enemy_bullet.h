#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H
#include<QPainter>
#include<cmath>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include<iostream>
#include"tower_s.h"
using namespace std;

class EBullet{                      //敌人的子弹-----------------敌人的敌人是塔
protected:
    double x,y;   //坐标
    double ex, ey;  //敌人坐标
    static int w,h; //画面大小
    double steps;  //速度
    double power;  //伤害
    double dir; //定位放向:和x正轴夹角,弧度
    QImage pic_b;
    Tower* e;                   //记录锁定的塔
    int type_id;     //子弹种类id

public:
    EBullet(){}
    virtual~EBullet(){cout<<"delete ebullet"<<endl;}
    virtual void set(double x, double y, Tower *p);  //位置  和锁定的敌人
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
#endif // ENEMY_BULLET_H
