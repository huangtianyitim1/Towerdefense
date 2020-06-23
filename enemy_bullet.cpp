#include"enemy_bullet.h"
using namespace std;
int EBullet::h=20;
int EBullet::w=20;

void EBullet::set(double x, double y, Tower *p){
    this->e=p;
    this->x=x;
    this->y=y;
    this->ex=this->e->getx()+20;     //要注意的是子弹定位的地方不一定就是敌人的右上角，要下来一点
    this->ey=this->e->gety()+20;
    double l=sqrt(pow(x-ex,2)+pow(y-ey,2));
    if (ey-y>0 && ex-x>0){   //1
        dir=asin((fabs(static_cast<double>(ey-y)))/l);
    }
    else if(ey-y>0 && ex-x<0){   //2
        dir=-1*asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926;
    }
    else if(ey-y<0 && ex-x<0){  //3
        dir=asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926;
    }
    else if(ey-y<0 && ex-x>0){   //
        dir=-1*asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926*2;
    }
      //注意这里用atan则不能得到360！
    type_id=10;   //种类id为10
}

void EBullet::setspd(double s){
    steps=s;
}

void EBullet::loadimage(){
    pic_b.load(":/images/zuqiu.png");
}

void EBullet::show(QPainter &p){
    loadimage();
    QRect target(x,y,w,h);
    //cout<<x<<"------"<<y<<endl;
    p.drawImage(target, pic_b);
}

void EBullet::setpower(double p){
    power=p;
}

bool EBullet::shootdown(){
    if (abs(x-ex)<5 && abs(y-ey)<5) {
        e->hp_minus(power);    //扣血
        return true; }  //还有音效没有
    else return false;
}

void EBullet::move(){
    if(!shootdown()){
        x+=steps*cos(dir);
        y+=steps*sin(dir);
        //cout<<x<<"--------"<<y<<endl;
        //cout<<cos(dir)<<endl;
    }
}
