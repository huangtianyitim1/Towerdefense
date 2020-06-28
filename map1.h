#ifndef MAP1_H
#define MAP1_H
#include"enemy_s.h"
//class Enemy;
class map1{
private:

public:
    map1(){}
    void collide_check(Enemy *e) const;
    bool outbound(Enemy *) const;
    bool can_put(double x, double y) const;    //判断能不能放，必须传入整百
    void collide_check2(Enemy *e)const;
    void collide_check3(Enemy *e) const;
    bool can_put2(double x, double y) const;
    bool can_put3(double x, double y) const;
};
#endif // MAP1_H
