#ifndef TOWER_H
#define TOWER_H
#include <QMainWindow>
#include<QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include<QTime>
#include"map1.h"
#include<vector>
#include"bullet.h"
#include"enemy_s.h"
using namespace std;

class Tower{
protected:
    double x,y;  //位置
    double ex, ey; //瞄准的敌人位置
    vector <Bullet> bs;    //装子弹
    const static int w,h;    //图片大小
    QImage pic_t;
    double range=200;  //范围
    int ei;  //攻击第几个敌人
    int spd=5; //子弹射速，可以升级
    int level=1;
public:
    Tower(){}
    ~Tower(){}
    void set(double x, double y);   //位置和
    void setspd(int spd) {this->spd=spd;}
    void show(QPainter&p);
    void loadimage();
    double getx() const {return x;}
    double gety() const {return y;}
    void getenemy(vector<Enemy *> &es);                   //寻找和锁定敌人，添加一颗子弹朝他发射，传递速度
    void attack();                     //所有子弹移动，如果打中了删除
    int getn_bs() const {return bs.size();}                    //the size of bullets
    void levelup(){level++;}
};
#endif // TOWER_H
