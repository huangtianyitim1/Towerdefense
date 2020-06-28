#include"tower.h"

const int Tower::w=70;
const int Tower::h=70;

void Tower::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //范围
    spd=5; //子弹射速，可以升级，一般不用
    power=10;  //子弹威力，升级加大
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
    p.drawRect(x+75, y+10, 5,50*hp/allhp); //画血条
}

void Tower::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        if (!es[ei]->die()){    //屏蔽掉了那些死掉的
        //cout<<es.size()<<endl;
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        Bullet *bp=new Bullet();
        bs.push_back(bp);
        bp=NULL;
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //初始化子弹的射速
        int tmp_power=power;      //自己的临时威力，面对不同敌人会不同，但本来power只和等级有关
        if (es[ei]->get_id()==2 ||es[ei]->get_id()==6 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==3 ||es[ei]->get_id()==4 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //子弹的威力设置，由自己目前的威力决定
            }
}

void Tower::attack(){
    if (bs.size()>0){
    for(int i=0; i<bs.size(); i++){         //每颗子弹都移动, 自己的方向已经设置好了
        bs[i]->move();
        if (bs[i]->shootdown()){
            delete bs[i];         //删除子弹对象占有的内存
            bs[i]=NULL;
            bs.erase(bs.begin()+i);                  //打中扣血，子弹消失
        }
        else if (bs[i]->getx()>960 || bs[i]->gety()>600 || bs[i]->getx()<0 || bs[i]->gety()<0){
            delete bs[i];                      //删除子弹对象占有的内存
            bs[i]=NULL;
            bs.erase(bs.begin()+i);          //到界外了，删除
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

void Tower::hp_minus(int p){           //扣的血为子弹威力
    hp-=p;
}
