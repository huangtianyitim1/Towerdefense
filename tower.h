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
    double x,y;  //λ��
    double ex, ey; //��׼�ĵ���λ��
    vector <Bullet> bs;    //װ�ӵ�
    const static int w,h;    //ͼƬ��С
    QImage pic_t;
    double range=200;  //��Χ
    int ei;  //�����ڼ�������
    int spd=5; //�ӵ����٣���������
    int level=1;
public:
    Tower(){}
    ~Tower(){}
    void set(double x, double y);   //λ�ú�
    void setspd(int spd) {this->spd=spd;}
    void show(QPainter&p);
    void loadimage();
    double getx() const {return x;}
    double gety() const {return y;}
    void getenemy(vector<Enemy *> &es);                   //Ѱ�Һ��������ˣ����һ���ӵ��������䣬�����ٶ�
    void attack();                     //�����ӵ��ƶ������������ɾ��
    int getn_bs() const {return bs.size();}                    //the size of bullets
    void levelup(){level++;}
};
#endif // TOWER_H
