#include"bullet_s.h"

void Bullet2::set(double x, double y, Enemy *p){
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
    type_id=2;   //种类id为2
}

void Bullet2::loadimage(){
    pic_b.load(":/images/shuiqiu.png");
}


void Bullet3::set(double x, double y, Enemy *p){
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
    type_id=3;   //种类id为3
}

void Bullet3::loadimage(){
    pic_b.load(":/images/leiqiu.png");
}

void Bullet4::set(double x, double y, Enemy *p){
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
    type_id=4;   //种类id为3
}

void Bullet4::loadimage(){
    pic_b.load(":/images/dianqiu.png");
}

void Bullet5::set(double x, double y, Enemy *p){
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
    type_id=5;   //种类id为3
}

void Bullet5::loadimage(){
    pic_b.load(":/images/guangqiu.png");
}

void Bullet6::set(double x, double y, Enemy *p){
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
    type_id=6;   //种类id为3
}

void Bullet6::loadimage(){
    pic_b.load(":/images/caiqiu.png");
}
