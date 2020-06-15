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
using namespace std;

class Tower{
protected:
    double x,y;  //λ��
    double ex, ey; //��׼�ĵ���λ��
    vector <Bullet> bs;    //װ�ӵ�
    QImage pic_t;
    double range;  //��Χ
    int ei;  //�����ڼ�������
    int spd; //�ӵ����٣�����������һ�㲻��
    int level=1;
    int power;  //�ӵ������������Ӵ�
    QString picture;
    int id;    //����
public:
    Tower(){}
    virtual ~Tower(){}
    const static int w,h;    //ͼƬ��С
    virtual void set(double x, double y);   //λ�ú�
    void setspd(int spd) {this->spd=spd;}             //�����Լ������е��ӵ��ٶȣ��о�ûʲô��
    void show(QPainter&p);
    void loadimage(const QString &s);
    double getx() const {return x;}
    double gety() const {return y;}
    void getenemy(vector<Enemy *> &es);                   //Ѱ�Һ��������ˣ����һ���ӵ��������䣬�����ٶ�
    void attack();                     //�����ӵ��ƶ������������ɾ��
    int getn_bs() const {return bs.size();}                    //the size of bullets
    virtual void levelup();    //����
    int getid() const {return id;}
};
#endif // TOWER_H
