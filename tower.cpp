#include"tower.h"

const int Tower::w=70;
const int Tower::h=70;

void Tower::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //��Χ
    spd=5; //�ӵ����٣�����������һ�㲻��
    power=10;  //�ӵ������������Ӵ�
    picture=":/images/xiaohuolong.png";
    id=1;
    allhp=10;
    hp=allhp;
    make_score=350;
    level_score=200;
}

void Tower::loadimage(const QString&s){
    pic_t.load(s);
}

void Tower::show(QPainter &p){
    loadimage(picture);
    QRect target(x,y,w,h);
    p.drawImage(target, pic_t);
    for (int i=0; i<bs.size(); i++){
        bs[i]->show(p);
    }
    QFont font("Microsoft YaHei", 9, 75);
    p.setFont(font);
    QString s_level="Level:"+QString::number(level);
    p.drawText(x+10, y-25,200,50,1, s_level);
    p.setPen(QPen(1));
    p.setBrush(QBrush(Qt::blue));
    p.drawRect(x+75, y+10, 5,50*hp/allhp); //��Ѫ��
}

void Tower::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        if (!es[ei]->die()){    //���ε�����Щ������
        //cout<<es.size()<<endl;
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //ƽ������
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //˵��û�з��ֵ���
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//���򣬶�λ����ei������(-1)
        //cout<<ex<<"------"<<ey<<endl;
        Bullet *bp=new Bullet();
        bs.push_back(bp);
        bp=NULL;
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //��ʼ���ӵ�������
        int tmp_power=power;      //�Լ�����ʱ��������Բ�ͬ���˻᲻ͬ��������powerֻ�͵ȼ��й�
        if (es[ei]->get_id()==2 ||es[ei]->get_id()==6 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==3 ||es[ei]->get_id()==4 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //�ӵ����������ã����Լ�Ŀǰ����������
            }
}

void Tower::attack(){
    if (bs.size()>0){
    for(int i=0; i<bs.size(); i++){         //ÿ���ӵ����ƶ�, �Լ��ķ����Ѿ����ú���
        bs[i]->move();
        if (bs[i]->shootdown()){
            delete bs[i];         //ɾ���ӵ�����ռ�е��ڴ�
            bs[i]=NULL;
            bs.erase(bs.begin()+i);                  //���п�Ѫ���ӵ���ʧ
        }
        else if (bs[i]->getx()>960 || bs[i]->gety()>600 || bs[i]->getx()<0 || bs[i]->gety()<0){
            delete bs[i];                      //ɾ���ӵ�����ռ�е��ڴ�
            bs[i]=NULL;
            bs.erase(bs.begin()+i);          //�������ˣ�ɾ��
        }
    }}
}

int Tower::levelup(){
    if(level<3){
    level++;
    if (level==2) {picture=":/images/huokonglong.png"; power=power+6;}
    if(level==3) {picture=":/images/penhuolong.png"; power=power+6;}
    return level_score;
    }
    else return 0;
}

void Tower::hp_minus(int p){           //�۵�ѪΪ�ӵ�����
    hp-=p;
}
