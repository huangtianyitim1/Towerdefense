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
#include <string>
#include"bullet_s.h"
using namespace std;
//class Enemy;
//class Bullet;
class Tower{
protected:
    double x,y;  //位置
    double ex, ey; //瞄准的敌人位置
    vector <Bullet *> bs;    //装子弹
    QImage pic_t;
    double range;  //范围
    int ei;  //攻击第几个敌人
    int spd; //子弹射速，可以升级，一般不用
    int level=1;
    double power;  //子弹威力，升级加大
    QString picture;
    int id;    //种类
    int e_in;  //范围内是否有敌人，光圈塔专用
    int hp;  //自己的即时血量
    int allhp; //初始血量
    int make_score;   //建造消耗的积分
    int level_score;    //升级消耗的积分
    bool have_boomed=false;   //还没爆炸


signals:

public:
    Tower(){}
    Tower(int range, int spd, int power, int allhp, int make_score, int level_score): range(range),spd(spd),power(power),
    allhp(allhp),make_score(make_score), level_score(level_score){
        picture=":/images/minilong.png";
        id=1;
        hp=this->allhp;
    }
    virtual ~Tower(){}
    const static int w,h;    //图片大小
    virtual void set(double x, double y);
    void setspd(int spd) {this->spd=spd;}  //设置自己的所有的子弹速度，感觉没什么用
    virtual void show(QPainter&p);
    void loadimage(const QString &s);
    double getx() const {return x;}
    double gety() const {return y;}
    virtual void getenemy(vector<Enemy *> &es);                   //寻找和锁定敌人，添加一颗子弹朝他发射，传递速度
    virtual void attack();                     //所有子弹移动，如果打中了删除
    int getn_bs() const {return bs.size();}                    //the size of bullets
    virtual int levelup();    //升级，返回消耗的积分
    int getid() const {return id;}
    double get_range() const {return range;}
    void hp_minus(int p);
    int get_hp() const{return hp;}   //小于等于0判定为死亡
    int get_make_score() const {return make_score;}
    int get_level_score() const {return level_score;}
    double get_power() const {return power;}
    double set_power(double p) {this->power=p;}
};
#endif // TOWER_H
