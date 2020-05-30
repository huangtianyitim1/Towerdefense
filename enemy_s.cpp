#include"enemy_s.h"

void Enemy1::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1.5;
    this->allhp=200;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=150;
}

void Enemy1::loadimage(){
    pic_e.load(":/images/daiouqixisi.png");
}

Enemy1::~Enemy1(){}

//----------------------------------------------------------------------------------------

void Enemy2::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1;
    this->allhp=150;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=100;
}

void Enemy2::loadimage(){
    pic_e.load(":/images/tiejiayong.png");
}

Enemy2::~Enemy2(){}

//----------------------------------------------------------------------------------------

void Enemy3::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=0.5;
    this->allhp=300;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=200;
}

void Enemy3::loadimage(){
    pic_e.load(":/images/banjila.png");
}

Enemy3::~Enemy3(){}

//----------------------------------------------------------------------------------------

void Enemy4::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=2;
    this->allhp=350;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=500;
}

void Enemy4::loadimage(){
    pic_e.load(":/images/jiekeluomu.png");
}

Enemy4::~Enemy4(){}

//----------------------------------------------------------------------------------------

void Enemy5::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=1;
    this->allhp=150;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=150;
}

void Enemy5::loadimage(){
    pic_e.load(":/images/dailong.png");
}

Enemy5::~Enemy5(){}

//----------------------------------------------------------------------------------------

void Enemy6::set(double x, double y) {
    this->x=x;
    this->y=y;
    this->steps=2.5;
    this->allhp=250;
    this->hp=allhp;             //初始hp，会扣
    this->e_score=400;
}

void Enemy6::loadimage(){
    pic_e.load(":/images/wujitaina.png");
}

Enemy6::~Enemy6(){}
