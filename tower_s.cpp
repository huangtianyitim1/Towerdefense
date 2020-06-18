#include"tower_s.h"

void Tower2::set(double x, double y){
    this->x=x;
    this->y=y;
    range=180;  //��Χ
    spd=5; //�ӵ����٣�����������һ�㲻��
    power=5;  //�ӵ������������Ӵ�
    picture=":/images/minilong.png";
    id=2;
}


void Tower2::levelup(){
    if(level<12){
    level++;
    power=power+1;          //����������
    if (level==5) {picture=":/images/hakelong.png"; power=power+5;}
    if(level==12) {picture=":/images/kuailong.png"; power=power+9;}
    }
}

void Tower2::getenemy(vector<Enemy *> &es){
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
        Bullet *bp=new Bullet2();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //��ʼ���ӵ�������
        int tmp_power=power;      //�Լ�����ʱ��������Բ�ͬ���˻᲻ͬ��������powerֻ�͵ȼ��й�
        if (es[ei]->get_id()==3 ||es[ei]->get_id()==4 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==1 ||es[ei]->get_id()==6 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //�ӵ����������ã����Լ�Ŀǰ����������
            }
}
///////////////////////////////////////////////////////////////////////////////////////////
void Tower3::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //��Χ
    spd=3; //�ӵ����٣�����������һ�㲻��
    power=2;  //�ӵ������������Ӵ�
    picture=":/images/jienigui.png";
    id=3;
}


void Tower3::levelup(){
    if(level<9){
    level++;
    power=power+1;          //����������
    if (level==4) {picture=":/images/kamigui.png"; power=power+4;}
    if(level==9) {picture=":/images/shuijiangui.png"; power=power+7;}
    }
}

void Tower3::getenemy(vector<Enemy *> &es){
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
        Bullet *bp=new Bullet3();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //��ʼ���ӵ�������
        int tmp_power=power;      //�Լ�����ʱ��������Բ�ͬ���˻᲻ͬ��������powerֻ�͵ȼ��й�
        if (es[ei]->get_id()==1 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==2 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //�ӵ����������ã����Լ�Ŀǰ����������
            }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
