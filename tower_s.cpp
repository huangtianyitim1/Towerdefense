#include"tower_s.h"

void Tower2::set(double x, double y){
    this->x=x;
    this->y=y;
    range=180;  //范围
    spd=5; //子弹射速，可以升级，一般不用
    power=15;  //子弹威力，升级加大
    picture=":/images/minilong.png";
    id=2;
    allhp=10;
    hp=allhp;
    make_score=500;
    level_score=300;
}


int Tower2::levelup(){
    if(level<3){
    level++;
    if (level==2) {picture=":/images/hakelong.png"; power=power+9;}
    if(level==3) {picture=":/images/kuailong.png"; power=power+9;}
    return level_score;
    }
    else return 0;
}

void Tower2::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        Bullet *bp=new Bullet2();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //初始化子弹的射速
        int tmp_power=power;      //自己的临时威力，面对不同敌人会不同，但本来power只和等级有关
        if (es[ei]->get_id()==3 ||es[ei]->get_id()==4 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==1 ||es[ei]->get_id()==6 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //子弹的威力设置，由自己目前的威力决定
            }
}
///////////////////////////////////////////////////////////////////////////////////////////
void Tower3::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //范围
    spd=3; //子弹射速，可以升级，一般不用
    power=10;  //子弹威力，升级加大
    picture=":/images/jienigui.png";
    id=3;
    allhp=10;
    hp=allhp;
    make_score=350;
    level_score=200;
}


int Tower3::levelup(){
    if(level<3){
    level++;
    if (level==2) {picture=":/images/kamigui.png"; power=power+6;}
    if(level==3) {picture=":/images/shuijiangui.png"; power=power+6;}
    return level_score;
    }
    else return 0;
}

void Tower3::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        Bullet *bp=new Bullet3();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //初始化子弹的射速
        int tmp_power=power;      //自己的临时威力，面对不同敌人会不同，但本来power只和等级有关
        if (es[ei]->get_id()==1 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==2 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //子弹的威力设置，由自己目前的威力决定
            }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower4::set(double x, double y){
    this->x=x;
    this->y=y;
    range=5;  //范围
    spd=1; //光圈射速，可以升级，一般不用
    power=12;  //子弹威力，升级加大
    picture=":/images/leixilamu.png";
    id=4;
    allhp=10;
    hp=allhp;
    make_score=500;
    level_score=500;
}

int Tower4::levelup(){
    if(level<3){
    level++;
    power=power+10;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower4::getenemy(vector<Enemy *> &es){
    e_in=0; //判断范围内是否有敌人的信号

    for(int ei=0; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<250*250) {/*cout<<ei<<endl;*/e_in=1;  break;}}  //此时有敌人进入范围，250的信号范围
    }

    for(int ei=0; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(e_in ==1){         //有信号才开始攻击
            if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {
            es[ei]->hpminus(power);
        } } //在光圈内，受到伤害
    }
    }
    if (e_in==0) range=5;  //没有敌人时，及时更新光圈，缩小到接近于0
    //cout<<ei<<endl;
}

void Tower4::attack(){
    if (e_in==1){
        if (range<180) range=range+spd;
        if (range>=180) range=20;
    }
}

void Tower4::show(QPainter &p){
    loadimage(picture);
    QRect target(x,y,w,h);
    p.drawImage(target, pic_t);
    QImage circle;
    circle.load(":/images/guangquan.png");
    QRect size(x+40-range, y+40-range, 2*range, 2*range);
    p.drawImage(size, circle);   //画光圈
    QFont font("Microsoft YaHei", 9, 75);
    p.setFont(font);
    QString s_level="Level:"+QString::number(level);
    p.drawText(x+10, y-15,200,50,1, s_level);
    p.setPen(QPen(1));
    p.setBrush(QBrush(Qt::blue));
    p.drawRect(x+75, y+10, 5,50*hp/allhp); //画血条
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower5::set(double x, double y){
    this->x=x;
    this->y=y;
    range=250;  //范围
    spd=1; //光圈射速，可以升级，一般不用
    power=12;  //子弹威力，升级加大
    picture=":/images/wanpidan.png";
    id=5;
    allhp=10;
    hp=allhp;
    make_score=3500;
    level_score=500;
}

int Tower5::levelup(){
    if(level<3){
    level++;
    power=power+10;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower5::getenemy(vector<Enemy *> &es){
    if (!have_boomed){
    for(int ei=0; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if (!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<250*250) {/*cout<<ei<<endl;*/ es[ei]->hpminus(10000);}}  //此时有敌人进入范围，炸掉
        have_boomed=true;
    }}
    else {}
}

void Tower5::attack(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower6::set(double x, double y){
    this->x=x;
    this->y=y;
    range=200;  //范围
    spd=1; //射速，可以升级，一般不用
    power=5;  //子弹威力，升级加大
    picture=":/images/pikaqiu.png";
    id=6;
    allhp=10;
    hp=allhp;
    make_score=1200;
    level_score=300;
}

int Tower6::levelup(){
    if(level<3){
    level++;
    power=power+5;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower6::getenemy(vector<Enemy *> &es){
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        Bullet *bp=new Bullet4();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);     //初始化子弹的射速
        int tmp_power=power;      //自己的临时威力，面对不同敌人会不同，但本来power只和等级有关
        if (es[ei]->get_id()==6 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==5 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //子弹的威力设置，由自己目前的威力决定
        es[ei]->setspd(1);    //把敌人速度重置为1
            }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower7::set(double x, double y){
    this->x=x;
    this->y=y;
    range=250;  //范围
    spd=1; //光圈射速，可以升级，一般不用
    power=12;  //子弹威力，升级加大
    picture=":/images/jidongniao.png";
    id=7;
    allhp=10;
    hp=allhp;
    make_score=1500;
    level_score=500;
}

int Tower7::levelup(){
    if(level<3){
    level++;
    power=power+10;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower7::getenemy(vector<Enemy *> &es){         //停止敌人行动由mainwindow实现
    if (!have_boomed){
    for(int ei=0; ei<es.size(); ei++){
        have_boomed=true;
    }}
    else {}
}

void Tower7::attack(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower8::set(double x, double y){
    this->x=x;
    this->y=y;
    range=250;  //范围
    spd=1; //光圈射速，可以升级，一般不用
    power=12;  //子弹威力，升级加大
    picture=":/images/menghuan.png";
    id=8;
    allhp=10;
    hp=allhp;
    make_score=3000;
    level_score=500;
}

int Tower8::levelup(){
    if(level<3){
    level++;
    power=power+10;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower8::getenemy(vector<Enemy *> &es){         //停止敌人行动由mainwindow实现
    if (!have_boomed){
    for(int ei=0; ei<es.size(); ei++){
        have_boomed=true;
    }}
    else {}
}

void Tower8::attack(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tower9::set(double x, double y){
    this->x=x;
    this->y=y;
    range=300;  //范围
    spd=1; //光圈射速，可以升级，一般不用
    power=20;  //子弹威力，升级加大
    picture=":/images/ladiyasi.png";
    id=9;
    allhp=10;
    hp=allhp;
    make_score=900;
    level_score=1400;
}

int Tower9::levelup(){
    if(level<2){
    level++;
    picture=":/images/ladiousi.png";
    power=power+20;          //升级加威力

    return level_score;
    }
    else return 0;
}

void Tower9::getenemy(vector<Enemy *> &es){         //停止敌人行动由mainwindow实现
    ei=0;
    for(; ei<es.size(); ei++){
        //cout<<es.size()<<endl;
        if(!es[ei]->die()){
        double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
        if(d<range*range) {/*cout<<ei<<endl;*/  break;}}
    }
    //cout<<ei<<endl;
    if (ei==es.size()) ei=9999;   //说明没有发现敌人
    else {
        this->ex=es[ei]->getx();
        this->ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
        //cout<<ex<<"------"<<ey<<endl;
        if(level==1){
        Bullet *bp=new Bullet5();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);    } //初始化子弹的射速
        else {
        Bullet *bp=new Bullet6();
        bs.push_back(bp);
        bs.back()->set(x+30, y+30, es[ei]);
        bs.back()->setspd(spd);    } //初始化子弹的射速
        int tmp_power=power;      //自己的临时威力，面对不同敌人会不同，但本来power只和等级有关
        if (es[ei]->get_id()==4 ||es[ei]->get_id()==6 ) tmp_power=power*1.5;
        if (es[ei]->get_id()==5 ) tmp_power=power*0.5;
        bs.back()->setpower(tmp_power);  //子弹的威力设置，由自己目前的威力决定
        if (level>1){
        es[ei]->setspd(1);}    //把敌人速度重置为1
            }
}


