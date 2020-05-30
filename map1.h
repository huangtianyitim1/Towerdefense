#ifndef MAP1_H
#define MAP1_H
#include"enemy_s.h"
class map1{
private:
    double x,y;
public:
    map1(){}
    void collide_check(Enemy *e);
    bool outbound(Enemy *);
};
#endif // MAP1_H
