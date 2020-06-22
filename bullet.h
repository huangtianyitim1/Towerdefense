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
    double x,y;   //����
    double ex, ey;  //��������
    static int w,h; //�����С
    double steps;  //�ٶ�
    double power;  //�˺�
    double dir; //��λ����:��x����н�,����
    QImage pic_b;
    Enemy* e;                   //��¼�����ĵ���
    int type_id;     //�ӵ�����id
public:
    Bullet(){}
    virtual~Bullet(){}
    virtual void set(double x, double y, Enemy *p);  //λ��  �������ĵ���
    double getdir() const {return dir;}             //���ط���
    void setspd(double s);                      //�����ٶ�
    void setpower(double p);                     //��������
    void show(QPainter&p);
    virtual void loadimage();
    bool shootdown();                      //���кͿ�Ѫ
    double getx() const{ return x;}
    double gety() const{ return y;}
    int getp() const{ return power;}        //��������
    void move();             //�ӵ��ƶ�
};
#endif // BULLET_H
