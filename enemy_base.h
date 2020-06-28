#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H
#include <QMainWindow>
#include<QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <iostream>
#include"wave_info.h"
//#include<tower.h>
//#include"enemy_bullet.h"
//class Tower;
using namespace std;
//血的教训：不要互相引用，不好hold住，最后可能混在一起遮盖什么
class Enemy{
protected:
    double x,y;          //位置
    static int w,h;          //图片大小
    QImage pic_e;
    int direction;  //都认为一开始从右边
    double steps;   //speed
    int hp;               //血量
    int allhp;         //总血量
    int e_score;   //一个敌人多少分
    int type_id;   //敌人种类id
    int range;   //敌人攻击范围
    double bullet_spd;   //子弹速度
    int power;     //子弹威力
    int damage;    //对家的损失
    //vector<EBullet *> bs;     //敌人也可以装弹

public:
    Enemy(){}
    virtual~Enemy();
    virtual void set(double x, double y, int dir)=0;                  //设置速度和这一刻位置、初始血量!!注意，速度和初始血我放到函数体里定义了
    //因为一定不要改写含有默认参数的虚函数！！！会出大问题的！
    void setspd(double s);                //设置速度
    double getspd() const {return steps;}
    void move();                               //敌人移动
    void show(QPainter&p);
    virtual void loadimage()=0;
    double getx() const {return x;}
    double gety() const {return y;}
    void change_dir(int d);                         //敌人改变方向
    void hpminus(int p);      //扣血
    bool die();   //是否被消灭
    int gethp() const{return hp;}
    int get_score() const {return e_score;}
    int get_id() const {return type_id;}   //敌人id获取
    int get_range() const{return range;}
    double get_bullet_spd() const{return bullet_spd;} //子弹速度
    int get_power() const{return power;}      //子弹威力
    int get_damage() const{return damage;}
    void wave_enhance(int wave);   //每一波后的强化
    bool has_scored=false;    //死了有没有算积分
    bool has_hurt_hp=false;   //有没有已经扣了我的血
    int get_dir() const{return direction;}
    //virtual void gettower(vector <Tower *> &ts){}   //搜寻塔，攻击
    //virtual void attack(){}  //子弹移动
};
#endif // ENEMY_BASE_H
