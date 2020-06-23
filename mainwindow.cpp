#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<iostream>

int start_x=800;
int start_y=520;
int MainWindow::e_spd=20;          //�����ƶ�ˢ�µ�Ƶ��
int MainWindow::e_spd2=2000;    //���˲�����Ƶ��
int MainWindow::e_spd3=300;     //���ӵ�����Ƶ��
int MainWindow::e_spd4=5;        //���ӵ��ƶ�ˢ��Ƶ��
int MainWindow::e_spd5=1200;   //�����ӵ�����Ƶ��

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(WINDOW_W,WINDOW_H);   //���ý����С
    initgame();
}

void MainWindow::recieve_start(){
    this->show();
}

Enemy* MainWindow::gen_enemy(){
    Enemy* p;
    QTime time = QTime::currentTime();     //�����
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
    timerid1=startTimer(e_spd);    //ˢ�µ����ƶ�
    timerid2=startTimer(e_spd2);   //ˢ�µ�������
    timerid3=startTimer(e_spd3);  //�ӵ�����
    timerid4=startTimer(e_spd4);  //�ӵ��ƶ�
    timerid5=startTimer(e_spd5);  //�����ӵ�����
    //tw.push_back(Tower());     һ��ʼ��һ����
    //tw[0].set(400,320);
    //���غõ�ͼ��ѡ��ͼ��
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
    e1[0]->set(start_x,start_y);//��ʼλ��
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
    //���߿�
    p.drawRect(MARGIN, MARGIN, WINDOW_W-2*MARGIN, WINDOW_H-2*MARGIN);
    //QRect target(800,400,100,200);
    QRect background(0,0,900,600);
    //dot.load(":/images/apple.png");
    //p.drawImage(target, dot);
    p.drawImage(background, map);    //������
    QRect type1(110,10,70,70);
    p.drawImage(type1, type1_pic);   //����ѡ��1��С����
    QRect type2(210,10,70,70);
    p.drawImage(type2, type2_pic);   //����ѡ��2��������
    QRect type3(310,10,70,70);
    p.drawImage(type3, type3_pic);   //����ѡ��3�������
    QRect type4(410,10,70,70);
    p.drawImage(type4, type4_pic);//����ѡ��4����ϣ��ķ
    //������
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
    //���濪ʼ��ÿ������ѡ�������ɾ����ȡ��
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
        if (type_id==1) {p.drawImage(size, type1_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}   //С�������200
        if (type_id==2) {p.drawImage(size, type2_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 180, 180);}  //  2�������������180
        if (type_id==3) {p.drawImage(size, type3_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  3������������200
        if (type_id==4) {p.drawImage(size, type4_pic); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  4������ϣ��ķ���250

    }

    for (int i=0; i<ebs.size(); i++){
    ebs[i]->show(p);      //���˵��ӵ�������
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
                delete e1[i];    //�ͷ�ָ��ĵ��˶����ڴ�----------------
                e1.erase(e1.begin()+i);   //ɾ�������ָ��Ԫ��
            }
        }
        for (int i=0; i<tw.size();i++){    //��� ���Ƿ�����
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
    repaint();  //������Ľ����������ÿһ��ʱ��ˢ�µ���һ��paintevent����
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
    mx=mx-mx%100;  //90�߳�Ϊһ����λ����      //mx��my���Ѿ�������ȡ100������
    my=my-my%100+20;  //-----------------------------------mx��my���Ǿ���ȡ���ٴ��������ж�==������my+20��
    int x=event->x();
    int y=event->y();
    QWidget::mousePressEvent(event);

    if (y<=100){    ///////////////��������ѡ��������
    if(x<160 &&x>100){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      type_id=1; //С����id
    }
    if(x<260 &&x>200){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      type_id=2; //������id
    }
    if(x<360 &&x>300){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      type_id=3; //�����id
    }
    if(x<460 &&x>400){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      type_id=4; //��ϣ��ķid
    }
    repaint();
    }

    if (y>100) {   //�ڹ�����������ܲ���
    if (event->button()==Qt::LeftButton){                                     //�����ӣ���������򲻼�
        if (m2p==0)      //����0���Խ�����������ĳһ������ѡ��ģʽ
        {/*
            if (no_tower(mx, my)<0){    //С����˵��û��
            Tower * twp=new Tower();
            tw.push_back(twp);   //����ѹ��twp��ʵ������һ������
            double fx=static_cast<double>(mx);
            double fy=static_cast<double>(my);
            tw.back()->set(fx, fy);} */
        }
        if(m2p==1){
            if (x<tw[tw_i]->getx()-10
                    && x>tw[tw_i]->getx()-60
                    && y<tw[tw_i]->gety()+60
                    && y>tw[tw_i]->gety()+10){   //ɾ��ѡ���λ���жϣ�ע��ָ��ǵ��ͷ�ָ�������ڴ�
                delete tw[tw_i];  //��Ȼtw[tw_i]�Ƕ�Ӧ��ԭ����twp�Ŀ���������deleteͬ��Ҳ�����ͷ�ָ���������ڴ������
                tw.erase(tw.begin()+tw_i);
                m2p=0;  //�ǳ���Ҫ�����������������Ϊ0������ظ�ɾ�������ڴ�й©
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
    if (event->button()==Qt::RightButton){    //�Ҽ�����һ����Χ��ɾ��
        //int i=no_tower(mx,my);
        //if (i>=0) tw.erase(tw.begin()+i);
        if (no_tower(mx,my)>=0) {
            tw_i=no_tower(mx,my);
            m2p=1; }     //�Ҽ��¼���������������ͼ
        repaint();
    }
}
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (m2p==2){
        local_x=event->x()-40;     //ʵ��λ��Ϊ���λ�õ����Ͻ�40��λ������------------------------
        local_y=event->y()-40;
        if (local_y>100)  show_keng=1;
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(m2p==2){
    m2p=0;
    int mx=event->x()-event->x()%100;
    int my=event->y()-event->y()%100+20;   //100ȡ������һ��
    if (no_tower(mx,my)<0){
    Tower * twp;
    if (type_id==1) twp=new Tower();
    if (type_id==2) twp=new Tower2();
    if (type_id==3) twp=new Tower3();
    if (type_id==4) twp=new Tower4();
    tw.push_back(twp);   //����ѹ��twp��ʵ������һ������
    double fx=static_cast<double>(mx);
    double fy=static_cast<double>(my);
    tw.back()->set(fx, fy);
    }
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //˫��ʵ���������������
    //int x=event->x();
    //int y=event->y();
    //int mx=x-x%100;
    //int my=y-y%100;
    //if (no_tower(mx,my)>=0){ int i=no_tower(mx,my); tw[i].levelup();
}


void MainWindow::gettower(vector <Tower*> es){       //���˵Ľ�����������ʵ��
    for (int i=0; i<e1.size(); i++){
        if (e1[i]->get_id()==4){
            int x=e1[i]->getx();
            int y=e1[i]->gety();
        int ei=0;
        for(; ei<es.size(); ei++){
            //cout<<es.size()<<endl;
            double d=(es[ei]->getx()-x)*(es[ei]->getx()-x)+(es[ei]->gety()-y)*(es[ei]->gety()-y);    //ƽ������
            if(d<es[ei]->get_range()*es[ei]->get_range()) {/*cout<<ei<<endl;*/  break;}
        }
        //cout<<ei<<endl;
        if (ei==es.size()) ei=9999;   //˵��û�з��ֵ���
        else {
            double ex=es[ei]->getx();
            double ey=es[ei]->gety();//���򣬶�λ����ei������(-1)
            //cout<<ex<<"------"<<ey<<endl;
            EBullet *bp=new EBullet();
            ebs.push_back(bp);
            ebs.back()->set(x+30, y+30, es[ei]);
            ebs.back()->setspd(e1[i]->get_bullet_spd());     //��ʼ���ӵ�������
            ebs.back()->setpower(e1[i]->get_power());   //�ӵ�����
            cout<<"launch"<<endl;
                }
        }
    }
}

void MainWindow::ebattack(){
    for(int i=0; i<ebs.size(); i++){         //ÿ���ӵ����ƶ�, �Լ��ķ����Ѿ����ú���
        ebs[i]->move();
        if (ebs[i]->shootdown()){
            delete ebs[i];         //ɾ���ӵ�����ռ�е��ڴ�
            ebs.erase(ebs.begin()+i);                  //���п�Ѫ���ӵ���ʧ
        }
        else if (ebs[i]->getx()>960 || ebs[i]->gety()>540 || ebs[i]->getx()<0 || ebs[i]->gety()<0){
            delete ebs[i];                      //ɾ���ӵ�����ռ�е��ڴ�
            ebs.erase(ebs.begin()+i);          //�������ˣ�ɾ��
        }
    }
}

