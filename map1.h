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
    bool can_put(double x, double y) const;    //�ж��ܲ��ܷţ����봫������
};
#endif // MAP1_H
