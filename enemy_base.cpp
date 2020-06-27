#include"enemy_base.h"

int Enemy::h=70;
int Enemy::w=70;


void Enemy::show(QPainter&p){
    loadimage();
    QRect target(x,y,w,h);
    p.drawImage(target, pic_e);
    p.setPen(QPen(1));
    p.setBrush(QBrush(Qt::red));
    p.drawRect(x+5, y-10, 50*hp/allhp, 5);             //画血条
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

void Enemy::hpminus(int p){  //扣得血量为子弹力量
    hp-=p;
}

bool Enemy::die(){
    if (hp<=0){
        return true;
    }
    else return false;
}

void Enemy::wave_enhance(int wave){                 //注意这里的wave是当前的wave，不用-1
    if (wave<Waveinfo::wave1) {allhp+=0.05*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave1 && wave <Waveinfo::wave2) {allhp+=0.06*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave2 && wave<Waveinfo::wave3) {allhp+=0.07*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave3 && wave<Waveinfo::wave4) {allhp+=0.08*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave4 && wave<Waveinfo::wave5) {allhp+=0.09*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave5 && wave<Waveinfo::wave7) {allhp+=0.1*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave7 && wave<Waveinfo::wave9) {allhp+=0.1*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave9 && wave<Waveinfo::wave11) {allhp+=0.1*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::wave11 && wave<Waveinfo::waveend) {allhp+=0.1*allhp*wave; hp=allhp;}
    if (wave>=Waveinfo::waveend) {allhp+=6*allhp+0.01*(wave-60)*allhp; hp=allhp;}
}
