#ifndef ENEMY_S_H
#define ENEMY_S_H
#include"enemy_base.h"
class Enemy1: public Enemy{
protected:
public:
    Enemy1(){}
    ~Enemy1();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy2: public Enemy{
protected:
public:
    Enemy2(){}
    ~Enemy2();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy3: public Enemy{
protected:
public:
    Enemy3(){}
    ~Enemy3();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy4: public Enemy{           //�������ࣺ�ᷢ���ڵ�
protected:
public:
    Enemy4(){}
    ~Enemy4();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ�����ڵ������ٶ�
    void loadimage();
};

class Enemy5: public Enemy{
protected:
public:
    Enemy5(){}
    ~Enemy5();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy6: public Enemy{
protected:
public:
    Enemy6(){}
    ~Enemy6();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy7: public Enemy{
protected:
public:
    Enemy7(){}
    ~Enemy7();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};

class Enemy8: public Enemy{
protected:
public:
    Enemy8(){}
    ~Enemy8();
    void set(double x, double y, int dir);                  //�����ٶȺ���һ��λ�á���ʼѪ��
    void loadimage();
};
#endif // ENEMY_S_H
