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
    double x,y;  //λ��
    double ex, ey; //��׼�ĵ���λ��
    vector <Bullet *> bs;    //װ�ӵ�
    QImage pic_t;
    double range;  //��Χ
    int ei;  //�����ڼ�������
    int spd; //�ӵ����٣�����������һ�㲻��
    int level=1;
    double power;  //�ӵ������������Ӵ�
    QString picture;
    int id;    //����
    int e_in;  //��Χ���Ƿ��е��ˣ���Ȧ��ר��
    int hp;  //�Լ��ļ�ʱѪ��
    int allhp; //��ʼѪ��
public:
    Tower(){}
    virtual ~Tower(){}
    const static int w,h;    //ͼƬ��С
    virtual void set(double x, double y);   //λ�ú�
    void setspd(int spd) {this->spd=spd;}             //�����Լ������е��ӵ��ٶȣ��о�ûʲô��
    virtual void show(QPainter&p);
    void loadimage(const QString &s);
    double getx() const {return x;}
    double gety() const {return y;}
    virtual void getenemy(vector<Enemy *> &es);                   //Ѱ�Һ��������ˣ����һ���ӵ��������䣬�����ٶ�
    virtual void attack();                     //�����ӵ��ƶ������������ɾ��
    int getn_bs() const {return bs.size();}                    //the size of bullets
    virtual void levelup();    //����
    int getid() const {return id;}
    double get_range() const {return range;}
    void hp_minus(int p);
    int get_hp() const{return hp;}   //С�ڵ���0�ж�Ϊ����
};
#endif // TOWER_H
