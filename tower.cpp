#include"tower.h"

const int Tower::w=80;
const int Tower::h=80;

void Tower::set(double x, double y){
    this->x=x;
    this->y=y;
}

void Tower::loadimage(){
    pic_t.load(":/images/penhuolong.png");
}

void Tower::show(QPainter &p){
    loadimage();
    QRect target(x,y,w,h);
    p.drawImage(target, pic_t);
    for (int i=0; i<bs.size(); i++){
        bs[i].show(p);
    }
    QString s_level="Level:"+QString::number(level);
    p.drawText(x+10, y-10,200,50,1, s_level);
}

void Tower::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //ƽ������
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //˵��û�з��ֵ���
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//���򣬶�λ����ei������(-1)
        //cout<<ex<<"------"<<ey<<endl;
        bs.push_back(Bullet());
        bs.back().set(x+30, y+30, es[ei]);
        bs.back().setspd(spd);     //��ʼ���ӵ�������
        bs.back().setpower(power);
            }
}

void Tower::attack(){
    for(int i=0; i<bs.size(); i++){         //ÿ���ӵ����ƶ�, �Լ��ķ����Ѿ����ú���
        bs[i].move();
        if (bs[i].shootdown()){
            bs.erase(bs.begin()+i);                  //���п�Ѫ���ӵ���ʧ
        }
        else if (bs[i].getx()>960 || bs[i].gety()>540 || bs[i].getx()<0 || bs[i].gety()<0){
            bs.erase(bs.begin()+i);
        }
    }
}

void Tower::levelup(){
    level++;
    power=power+10;          //����������
}
