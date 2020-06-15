#include"tower.h"

const int Tower::w=85;
const int Tower::h=85;

void Tower::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //范围
    spd=5; //子弹射速，可以升级，一般不用
    power=2;  //子弹威力，升级加大
    picture=":/images/xiaohuolong.png";
    id=0;
}

void Tower::loadimage(const QString&s){
    pic_t.load(s);
}

void Tower::show(QPainter &p){
    loadimage(picture);
    QRect target(x,y,w,h);
    p.drawImage(target, pic_t);
    for (int i=0; i<bs.size(); i++){
        bs[i].show(p);
    }
    QString s_level="Level:"+QString::number(level);
    p.drawText(x+10, y-15,200,50,1, s_level);
}

void Tower::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        bs.push_back(Bullet());
        bs.back().set(x+30, y+30, es[ei]);
        bs.back().setspd(spd);     //初始化子弹的射速
        bs.back().setpower(power);
            }
}

void Tower::attack(){
    for(int i=0; i<bs.size(); i++){         //每颗子弹都移动, 自己的方向已经设置好了
        bs[i].move();
        if (bs[i].shootdown()){
            bs.erase(bs.begin()+i);                  //打中扣血，子弹消失
        }
        else if (bs[i].getx()>960 || bs[i].gety()>540 || bs[i].getx()<0 || bs[i].gety()<0){
            bs.erase(bs.begin()+i);
        }
    }
}

void Tower::levelup(){
    if(level<9){
    level++;
    power=power+1;          //升级加威力
    if (level==4) {picture=":/images/huokonglong.png"; power=power+4;}
    if(level==9) {picture=":/images/penhuolong.png"; power=power+7;}
    }
}
