#include"enemy_s.h"

void Enemy1::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1.5;
    this->allhp=100;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=150;
    type_id=1;
    damage=100;
}

void Enemy1::loadimage(){
    pic_e.load(":/images/daiouqixisi.png");
}

Enemy1::~Enemy1(){cout<<11<<endl;}

//----------------------------------------------------------------------------------------

void Enemy2::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1;
    this->allhp=90;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=100;
    type_id=2;
    damage=80;
}

void Enemy2::loadimage(){
    pic_e.load(":/images/tiejiayong.png");
}

Enemy2::~Enemy2(){cout<<11<<endl;}

//----------------------------------------------------------------------------------------

void Enemy3::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1;
    this->allhp=200;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=200;
    type_id=3;
    damage=120;
}

void Enemy3::loadimage(){
    pic_e.load(":/images/banjila.png");
}

Enemy3::~Enemy3(){cout<<11<<endl;}

//----------------------------------------------------------------------------------------

void Enemy4::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=2;
    this->allhp=150;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=500;
    type_id=4;
    range=200;
    bullet_spd=1;
    power=1;
    damage=150;
}

void Enemy4::loadimage(){
    pic_e.load(":/images/jiekeluomu.png");
}

Enemy4::~Enemy4(){cout<<11<<endl;}

//----------------------------------------------------------------------------------------

void Enemy5::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1.5;
    this->allhp=90;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=150;
    type_id=5;
    damage=100;
}

void Enemy5::loadimage(){
    pic_e.load(":/images/dailong.png");
}

Enemy5::~Enemy5(){cout<<11<<endl;}

//----------------------------------------------------------------------------------------

void Enemy6::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=2.5;
    this->allhp=100;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=400;
    type_id=6;
    damage=120;
}

void Enemy6::loadimage(){
    pic_e.load(":/images/wujitaina.png");
}

Enemy6::~Enemy6(){cout<<11<<endl;}
