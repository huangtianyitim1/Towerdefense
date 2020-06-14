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

class Bullet{
protected:
    double x,y;   //����
    double ex, ey;  //��������
    static int w,h; //�����С
    double steps;  //�ٶ�
    int power;  //�˺�
    double dir; //��λ����:��x����н�,����
    QImage pic_b;
    Enemy* e;                   //��¼�����ĵ���
public:
    Bullet(){}
    void set(double x, double y, Enemy *p);  //λ��  �������ĵ���
    double getdir() const {return dir;}             //���ط���
    void setspd(double s);                      //�����ٶ�
    void setpower(int p);                     //��������
    void show(QPainter&p);
    void loadimage();
    bool shootdown();                      //���кͿ�Ѫ
    double getx() const{ return x;}
    double gety() const{ return y;}
    int getp() const{ return power;}        //��������
    void move();             //�ӵ��ƶ�
};
#endif // BULLET_H
