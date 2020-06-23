#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<iostream>

int start_x=800;
int start_y=520;
int MainWindow::e_spd=20;          //敌人移动刷新的频率
int MainWindow::e_spd2=2000;    //敌人产生的频率
int MainWindow::e_spd3=300;     //塔子弹产生频率
int MainWindow::e_spd4=5;        //塔子弹移动刷新频率
int MainWindow::e_spd5=1200;   //敌人子弹产生频率

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(WINDOW_W,WINDOW_H);   //设置界面大小
    initgame();
}

void MainWindow::recieve_start(){
    this->show();
}

Enemy* MainWindow::gen_enemy(){
    Enemy* p;
    QTime time = QTime::currentTime();     //随机数
    qsrand((uint) time.msec());
    int i = qrand() % 6+1;
    switch (i) {
    case 1:   //A
        p=new Enemy1();
        break;
    case 2:  //W
       p=new Enemy2();
        break;
    case 3:  //D
        p=new Enemy3();
        break;
    case 4:  //S
        p=new Enemy4();
        break;
    case 5:  //S
        p=new Enemy5();
        break;
    case 6:  //S
        p=new Enemy6();
        break;
    }
        return p;
}

void MainWindow::initgame(){
    timerid1=startTimer(e_spd);    //刷新敌人移动
    timerid2=startTimer(e_spd2);   //刷新敌人数量
    timerid3=startTimer(e_spd3);  //子弹产生
    timerid4=startTimer(e_spd4);  //子弹移动
    timerid5=startTimer(e_spd5);  //敌人子弹产生
    //tw.push_back(Tower());     一开始的一个塔
    //tw[0].set(400,320);
    //加载好地图、选项图标
    map.load(":/images/map1.png");
    remove.load(":/images/chanzi.png");
    up.load(":/images/shengji.png");
    cancel.load(":/images/quxiao.png");
    type1_pic.load(":/images/xiaohuolong.png");
    type2_pic.load(":/images/minilong.png");
    type3_pic.load(":/images/jienigui.png");
    type4_pic.load(":/images/leixilamu.png");
    keng_pic.load(":/images/keng.png");
    e1.push_back(gen_enemy());
    e1[0]->set(start_x,start_y);//初始位置
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);
    //画边框
    p.drawRect(MARGIN, MARGIN, WINDOW_W-2*MARGIN, WINDOW_H-2*MARGIN);
    //QRect target(800,400,100,200);
    QRect background(0,0,900,600);
    //dot.load(":/images/apple.png");
    //p.drawImage(target, dot);
    p.drawImage(background, map);    //画背景
    QRect type1(110,10,70,70);
    p.drawImage(type1, type1_pic);   //画可选塔1：小火龙
    QRect type2(210,10,70,70);
    p.drawImage(type2, type2_pic);   //画可选塔2：迷你龙
    QRect type3(310,10,70,70);
    p.drawImage(type3, type3_pic);   //画可选塔3：杰尼龟
    QRect type4(410,10,70,70);
    p.drawImage(type4, type4_pic);//画可选塔4：雷希拉姆
    //画对象
    draw(p);
}

void MainWindow::draw(QPainter &p){
    s_score="Score: "+QString::number(score);
    p.drawText(500, 100,200,50,1, s_score);
    for (int i=0; i<e1.size(); i++){
        e1[i]->show(p);
    }
    for (int i=0; i<tw.size(); i++){
    tw[i]->show(p);}
    //下面开始画每个塔的选项，升级，删除，取消
    if (m2p==1){
        QRect op1 (tw[tw_i]->getx()-60, tw[tw_i]->gety()+10, 50,50);
        p.drawImage(op1, remove);
        QRect op2 (tw[tw_i]->getx()+10, tw[tw_i]->gety()-60, 50, 50);
        p.drawImage(op2, up);
        QRect op3 (tw[tw_i]->getx()+100, tw[tw_i]->gety()+10, 50, 50);
        p.drawImage(op3, cancel);
    }
    if(m2p==2){
        QRect size(local_x,local_y,80,80);
        p.setBrush(Qt::NoBrush);
        if (show_keng==1) {QRect keng_size(local_x+40-(local_x+40)%100,local_y+40-(local_y+40)%100,100,100); p.drawImage(keng_size, keng_pic); }
        if (type_id==1) {p.drawImage(size, type1_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}   //小火龙射程200
        if (type_id==2) {p.drawImage(size, type2_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 180, 180);}  //  2号塔迷你龙射程180
        if (type_id==3) {p.drawImage(size, type3_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  3号塔杰尼龟射程200
        if (type_id==4) {p.drawImage(size, type4_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  4号塔雷希拉姆射程250

    }

    for (int i=0; i<ebs.size(); i++){
    ebs[i]->show(p);      //敌人的子弹单独画
    }
}

void MainWindow::timerEvent(QTimerEvent *e){
    int id = e->timerId();
    if (id==timerid1){
        for (int i=0; i<e1.size(); i++){
            //e1[i].setspd(1);
            e1[i]->move();
            m1.collide_check(e1[i]);
            //cout<<e1[i].gethp()<<endl;
            if(m1.outbound(e1[i]) || e1[i]->die()){
                score+=e1[i]->get_score();
                delete e1[i];    //释放指向的敌人对象内存----------------
                e1.erase(e1.begin()+i);   //删除数组的指针元素
            }
        }
        for (int i=0; i<tw.size();i++){    //检测 塔是否阵亡
            if (tw[i]->get_hp()<=0){
                delete tw[i];
                tw.erase(tw.begin()+i);
            }
        }
    }
    if(id==timerid2){
        if (e1.size()<7){
        e1.push_back(gen_enemy());
        e1.back()->set(start_x,start_y);
       /* time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n = qrand() % 5;
        timerid2=startTimer(1000*n);*/
    }
    }
    if(id==timerid3){
        for(int i=0; i<tw.size(); i++){
        tw[i]->getenemy(e1);
        tw[i]->attack();
        }
    }
    if(id==timerid4){
        for(int i=0; i<tw.size(); i++){
        tw[i]->attack();}
        ebattack();
    }
    if(id==timerid5){
        gettower(tw);
    }
    repaint();  //和上面的结合起来看，每一定时间刷新调用一次paintevent函数
}


int MainWindow::no_tower(int x, int y){
    int count=0, i=0;
    for (; i<tw.size(); i++){
        if (x==tw[i]->getx() &&y==tw[i]->gety()) {count++; break;}
    }
    if (count ==0) return -999;
    else return i;
}



void MainWindow::mousePressEvent(QMouseEvent *event){
    int mx=event->x();
    int my=event->y();
    mx=mx-mx%100;  //90边长为一个单位？？      //mx和my都已经经过了取100整处理
    my=my-my%100+20;  //-----------------------------------mx和my都是经过取整百处理，用来判断==，其中my+20了
    int x=event->x();
    int y=event->y();
    QWidget::mousePressEvent(event);

    if (y<=100){    ///////////////工具栏，选择塔类型
    if(x<160 &&x>100){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      type_id=1; //小火龙id
    }
    if(x<260 &&x>200){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      type_id=2; //迷你龙id
    }
    if(x<360 &&x>300){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      type_id=3; //杰尼龟id
    }
    if(x<460 &&x>400){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      type_id=4; //雷希拉姆id
    }
    repaint();
    }

    if (y>100) {   //在工具栏下面才能操作
    if (event->button()==Qt::LeftButton){                                     //左键添加，有喷火龙则不加
        if (m2p==0)      //等于0可以建塔，否则在某一个塔的选项模式
        {/*
            if (no_tower(mx, my)<0){    //小于零说明没塔
            Tower * twp=new Tower();
            tw.push_back(twp);   //这里压入twp其实是做了一个拷贝
            double fx=static_cast<double>(mx);
            double fy=static_cast<double>(my);
            tw.back()->set(fx, fy);} */
        }
        if(m2p==1){
            if (x<tw[tw_i]->getx()-10
                    && x>tw[tw_i]->getx()-60
                    && y<tw[tw_i]->gety()+60
                    && y>tw[tw_i]->gety()+10){   //删除选项的位置判断，注意指针记得释放指向对象的内存
                delete tw[tw_i];  //虽然tw[tw_i]是对应的原来的twp的拷贝，但是delete同样也起到了释放指向塔对象内存的作用
                tw.erase(tw.begin()+tw_i);
                m2p=0;  //非常重要！！！这里如果不化为0，则会重复删除导致内存泄漏
            }
            if (x<tw[tw_i]->getx()+60
                    && x>tw[tw_i]->getx()+10
                    && y<tw[tw_i]->gety()-10
                    && y>tw[tw_i]->gety()-60){
                tw[tw_i]->levelup();
            }
            if(x<tw[tw_i]->getx()+150
                    && x>tw[tw_i]->getx()+100
                    && y<tw[tw_i]->gety()+60
                    && y>tw[tw_i]->gety()+10){
                m2p=0;
            }
            repaint();
        }
    }
    if (event->button()==Qt::RightButton){    //右键落入一定范围后，删除
        //int i=no_tower(mx,my);
        //if (i>=0) tw.erase(tw.begin()+i);
        if (no_tower(mx,my)>=0) {
            tw_i=no_tower(mx,my);
            m2p=1; }     //右键事件被触发，传给画图
        repaint();
    }
}
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (m2p==2){
        local_x=event->x()-40;     //实际位置为鼠标位置的左上角40单位！！！------------------------
        local_y=event->y()-40;
        if (local_y>100)  show_keng=1;
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(m2p==2){
    m2p=0;
    int mx=event->x()-event->x()%100;
    int my=event->y()-event->y()%100+20;   //100取整下来一点
    if (no_tower(mx,my)<0){
    Tower * twp;
    if (type_id==1) twp=new Tower();
    if (type_id==2) twp=new Tower2();
    if (type_id==3) twp=new Tower3();
    if (type_id==4) twp=new Tower4();
    tw.push_back(twp);   //这里压入twp其实是做了一个拷贝
    double fx=static_cast<double>(mx);
    double fy=static_cast<double>(my);
    tw.back()->set(fx, fy);
    }
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //双击实现升级：威力变大
    //int x=event->x();
    //int y=event->y();
    //int mx=x-x%100;
    //int my=y-y%100;
    //if (no_tower(mx,my)>=0){ int i=no_tower(mx,my); tw[i].levelup();
}


void MainWindow::gettower(vector <Tower*> es){       //敌人的进攻在主界面实现
    for (int i=0; i<e1.size(); i++){
        if (e1[i]->get_id()==4){
            int x=e1[i]->getx();
            int y=e1[i]->gety();
        int ei=0;
        for(; ei<es.size(); ei++){
            //cout<<es.size()<<endl;
            double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //平方距离
            if(d<es[ei]->get_range()*es[ei]->get_range()) {/*cout<<ei<<endl;*/  break;}
        }
        //cout<<ei<<endl;
        if (ei==es.size()) ei=9999;   //说明没有发现敌人
        else {
            double ex=es[ei]->getx();
            double ey=es[ei]->gety();//否则，定位到第ei个敌人(-1)
            //cout<<ex<<"------"<<ey<<endl;
            EBullet *bp=new EBullet();
            ebs.push_back(bp);
            ebs.back()->set(x+30, y+30, es[ei]);
            ebs.back()->setspd(e1[i]->get_bullet_spd());     //初始化子弹的射速
            ebs.back()->setpower(e1[i]->get_power());   //子弹威力
            cout<<"launch"<<endl;
                }
        }
    }
}

void MainWindow::ebattack(){
    for(int i=0; i<ebs.size(); i++){         //每颗子弹都移动, 自己的方向已经设置好了
        ebs[i]->move();
        if (ebs[i]->shootdown()){
            delete ebs[i];         //删除子弹对象占有的内存
            ebs.erase(ebs.begin()+i);                  //打中扣血，子弹消失
        }
        else if (ebs[i]->getx()>960 || ebs[i]->gety()>540 || ebs[i]->getx()<0 || ebs[i]->gety()<0){
            delete ebs[i];                      //删除子弹对象占有的内存
            ebs.erase(ebs.begin()+i);          //到界外了，删除
        }
    }
}

