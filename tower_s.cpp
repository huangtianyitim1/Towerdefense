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
