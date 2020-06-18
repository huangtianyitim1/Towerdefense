#ifndef BULLET_S_H
#define BULLET_S_H
#include"bullet.h"
class Bullet2: public Bullet{
public:
    Bullet2(){}
    void set(double x, double y, Enemy *p);
    void loadimage();
    ~Bullet2(){cout<<"delete bullet2"<<endl;}
};

class Bullet3: public Bullet{
public:
    Bullet3(){}
    void set(double x, double y, Enemy *p);
    void loadimage();
    ~Bullet3(){cout<<"delete bullet3"<<endl;}
};

#endif // BULLET_S_H
