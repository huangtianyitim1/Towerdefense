#include"map1.h"

void map1::collide_check(Enemy *e){
    //�̻���ͼ�����ӣ�������ת��
    x=e->getx(); y=e->gety();
    if (x<=400 && y>=400) e->change_dir(2);
    if (x<=500 && y<=300) e->change_dir(1);
}

bool map1::outbound(Enemy *e){
    x=e->getx(); y=e->gety();
    if (x<20) return true;
    else return false;
}
