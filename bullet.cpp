#include"bullet.h"
using namespace std;
int Bullet::h=20;
int Bullet::w=20;

void Bullet::set(double x, double y, Enemy *p){
    this->e=p;
    this->x=x;
    this->y=y;
    this->ex=this->e->getx()+20;     //要注意的是子弹定位的地方不一定就是敌人的右上角，要下来一点
    this->ey=this->e->gety()+20;
    double l=sqrt(pow(x-ex,2)+pow(y-ey,2));
    if (ey-y>=0 && ex-x>=0){   //1
        dir=asin((fabs(static_cast<double>(ey-y)))/l);
    }
    else if(ey-y>=0 && ex-x<=0){   //2
        dir=-1*asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926;
    }
    else if(ey-y<=0 && ex-x<=0){  //3
        dir=asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926;
    }
    else if(ey-y<=0 && ex-x>=0){   //
        dir=-1*asin((fabs(static_cast<double>(ey-y)))/l)+3.1415926*2;
    }
      //注意这里用atan则不能得到360！
    type_id=1;   //种类id为0
}

void Bullet::setspd(double s){
    steps=s;
}

void Bullet::loadimage(){
    pic_b.load(":/images/huoqiu.png");
}

void Bullet::show(QPainter &p){
    loadimage();
    QRect target(x,y,w,h);
    //cout<<x<<"------"<<y<<endl;
    p.drawImage(target, pic_b);
}

void Bullet::setpower(double p){
    power=p;
}

bool Bullet::shootdown(){
    if (abs(x-ex)<5 && abs(y-ey)<5) {
        e->hpminus(power);    //扣血
        return true; }  //还有音效没有
    else return false;
}

void Bullet::move(){
    if(!shootdown()){
        x+=steps*cos(dir);
        y+=steps*sin(dir);
        //cout<<x<<"--------"<<y<<endl;
        //cout<<cos(dir)<<endl;
    }
}

