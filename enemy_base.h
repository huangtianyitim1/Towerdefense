#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H
#include <QMainWindow>
#include<QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <iostream>
//#include<tower.h>
//#include"bullet.h"
using namespace std;
//Ѫ�Ľ�ѵ����Ҫ�������ã�����holdס�������ܻ���һ���ڸ�ʲô
class Enemy{
protected:
    double x,y;          //λ��
    static int w,h;          //ͼƬ��С
    QImage pic_e;
    int direction=1;  //����Ϊһ��ʼ���ұ�
    double steps;   //speed
    int hp;               //Ѫ��
    int allhp;         //��Ѫ��
    int e_score;   //һ�����˶��ٷ�
    int type_id;   //��������id
    //vector<Bullet *> bs;     //����Ҳ����װ��

public:
    Enemy(){}
    virtual~Enemy();
    virtual void set(double x, double y)=0;                  //�����ٶȺ���һ��λ�á���ʼѪ��!!ע�⣬�ٶȺͳ�ʼѪ�ҷŵ��������ﶨ����
    //��Ϊһ����Ҫ��д����Ĭ�ϲ������麯�����������������ģ�
    void setspd(double s);                //�����ٶ�
    void move();                               //�����ƶ�
    void show(QPainter&p);
    virtual void loadimage()=0;
    double getx() const {return x;}
    double gety() const {return y;}
    void change_dir(int d);                         //���˸ı䷽��
    void hpminus(int p);      //��Ѫ
    bool die();   //�Ƿ�����
    int gethp() const{return hp;}
    int get_score() const {return e_score;}
    int get_id() const {return type_id;}   //����id��ȡ
    //virtual void gettower(vector <Tower *> &ts){}   //��Ѱ��������
    //virtual void attack(){}  //�ӵ��ƶ�
};
#endif // ENEMY_BASE_H
