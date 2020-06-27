#include"map1.h"

void map1::collide_check(Enemy *e) const{
    //刻画地图的样子，到点了转弯
    double x=e->getx(); double y=e->gety();
    if (x<=410 && y>=400) e->change_dir(2);
    if (x<=500 && y<=120) e->change_dir(1);
}

bool map1::outbound(Enemy *e) const{
    double x=e->getx(); double y=e->gety();
    if (x<20) return true;
    else return false;
}

bool map1::can_put(double x, double y) const{
    if (y==0) return false;
    else if (y==100){
        if( x<500) return false;
        else return true;
    }
    else if (y>100 && y<500){
        if (x==400) return false;
        else return true;
    }
    else {
        if (x>=400) return false;
        else return true;
    }
}
