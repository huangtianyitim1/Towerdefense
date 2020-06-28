#include"map1.h"

bool map1::outbound(Enemy *e) const{
    double x=e->getx(); double y=e->gety();
    if (x<20) return true;
    else return false;
}

void map1::collide_check(Enemy *e) const{
    //刻画地图的样子，到点了转弯
    double x=e->getx(); double y=e->gety();
    if (x<=410 && y>=400) e->change_dir(2);
    if (x<=500 && y<=120) e->change_dir(1);
}

void map1::collide_check2(Enemy *e) const{
    //刻画地图的样子，到点了转弯
    double x=e->getx(); double y=e->gety();
    if (x<=410 && y>=400 &&e->get_dir()==1) e->change_dir(2);
    if (x<=480 && y<=120 &&e->get_dir()==2 ) e->change_dir(1);
    if (x<=410 &&y>=200 &&y<=280 &&e->get_dir()==1) e->change_dir(2);
}

void map1::collide_check3(Enemy *e) const{
    //刻画地图的样子，到点了转弯
    double x=e->getx(); double y=e->gety();
    if (x<=410 && y>=400 &&e->get_dir()==1) e->change_dir(2);
    if (x<=480 && y<=120 &&e->get_dir()==2 ) e->change_dir(1);
    if (x<=410 &&y>=200 &&y<=280 &&e->get_dir()==1) e->change_dir(2);
    if (x>=410 &&e->get_dir()==3) e->change_dir(2);
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

bool map1::can_put2(double x, double y) const{
    if(!can_put(x,y) || (x>=500 && y==200)) return false;
    else return true;
}

bool map1::can_put3(double x, double y) const{
    if(!can_put2(x,y) ||(y==400 &&x<=350)) return false;
    else return true;
}
