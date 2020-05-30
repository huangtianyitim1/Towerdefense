#include"enemy_base.h"

int Enemy::h=80;
int Enemy::w=80;


void Enemy::show(QPainter&p){
    loadimage();
    QRect target(x,y,w,h);
    p.drawImage(target, pic_e);
    p.setPen(QPen(1));
    p.setBrush(QBrush(Qt::red));
    p.drawRect(x+10, y-10, 60*hp/allhp, 5);             //»­ÑªÌõ
}

void Enemy::setspd(double s){
    steps=s;
}
void Enemy::move(){
    switch (direction) {
    case 1:   //A
        this->x-=steps;
        break;
    case 2:  //W
        this->y-=steps;
        break;
    case 3:  //D
        this->x+=steps;
        break;
    case 4:  //S
        this->y+=steps;
        break;
    }
}

Enemy::~Enemy(){/*
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();*/
}

void Enemy::change_dir(int d){
    this->direction=d;
}

void Enemy::hpminus(int p){
    hp-=p;
}

bool Enemy::die(){
    if (hp<=0){
        return true;
    }
    else return false;
}
