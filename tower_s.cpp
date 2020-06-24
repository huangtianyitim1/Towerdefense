#include"tower_s.h"

void Tower2::set(double x, double y){
    this->x=x;
    this->y=y;
    range=180;  //��Χ
    spd=5; //�ӵ����٣�����������һ�㲻��
    power=5;  //�ӵ������������Ӵ�
    picture=":/images/minilong.png";
    id=2;
    allhp=10;
    hp=allhp;
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
    allhp=10;
    hp=allhp;
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
void Tower4::set(double x, double y){
    this->x=x;
    this->y=y;
    range=5;  //��Χ
    spd=1; //��Ȧ���٣�����������һ�㲻��
    power=5;  //�ӵ������������Ӵ�
    picture=":/images/leixilamu.png";
    id=4;
    allhp=10;
    hp=allhp;
}

void Tower4::levelup(){
    if(level<7){
    level++;
    power=power+2;          //����������
    }
}

void Tower4::getenemy(vector<Enemy *> &es){
    e_in=0; //�жϷ�Χ���Ƿ��е��˵��ź�

    for(int ei=0; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //ƽ������
        if(d<250*250) {/*cout<<ei<<endl;*/e_in=1;  break;}  //��ʱ�е��˽��뷶Χ��250���źŷ�Χ
    }

    for(int ei=0; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(e_in ==1){         //���źŲſ�ʼ����
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //ƽ������
        if(d<range*range) {
            es[ei]->hpminus(power);
        }  //�ڹ�Ȧ�ڣ��ܵ��˺�
    }
    }
    if (e_in==0) range=5;  //û�е���ʱ����ʱ���¹�Ȧ����С���ӽ���0
    //cout<<ei<<endl;
}

void Tower4::attack(){
    if (e_in==1){
        if (range<150) range=range+spd;
        if (range>=150) range=20;
    }
}

void Tower4::show(QPainter &p){
    loadimage(picture);
    QRect target(x,y,w,h);
    p.drawImage(target, pic_t);
    QImage circle;
    circle.load(":/images/guangquan.png");
    QRect size(x+40-range, y+40-range, 2*range, 2*range);
    p.drawImage(size, circle);   //����Ȧ
    QFont font("Microsoft YaHei", 9, 75);
    p.setFont(font);
    QString s_level="Level:"+QString::number(level);
    p.drawText(x+10, y-15,200,50,1, s_level);
    p.setPen(QPen(1));
    p.setBrush(QBrush(Qt::blue));
    p.drawRect(x+75, y+10, 5,50*hp/allhp); //��Ѫ��
}
