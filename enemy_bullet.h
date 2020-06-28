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

class EBullet{                      //���˵��ӵ�-----------------���˵ĵ�������
protected:
    double x,y;   //����
    double ex, ey;  //��������
    static int w,h; //�����С
    double steps;  //�ٶ�
    double power;  //�˺�
    double dir; //��λ����:��x����н�,����
    QImage pic_b;
    Tower* e;                   //��¼��������
    int type_id;     //�ӵ�����id
    QString pic;   //�ӵ�ͼƬ

public:
    EBullet(QString pic);
    virtual~EBullet(){}
    virtual void set(double x, double y, Tower *p);  //λ��  �������ĵ���
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
    void set_id(int id);
    int get_id() const {return type_id;}
};
#endif // ENEMY_BULLET_H
