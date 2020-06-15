#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<iostream>

int start_x=800;
int start_y=500;
int MainWindow::e_spd=20;          //�����ƶ�ˢ�µ�Ƶ��
int MainWindow::e_spd2=2000;    //���˲�����Ƶ��
int MainWindow::e_spd3=300;     //�ӵ�����Ƶ��
int MainWindow::e_spd4=5;        //�ӵ��ƶ�ˢ��Ƶ��

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(WINDOW_W,WINDOW_H);   //���ý����С
    initgame();
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
    //tw.push_back(Tower());     һ��ʼ��һ����
    //tw[0].set(400,320);
    //���غõ�ͼ��ѡ��ͼ��
    map.load(":/images/map.jpg");
    remove.load(":/images/chanzi.png");
    up.load(":/images/shengji.png");
    cancel.load(":/images/quxiao.png");

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
    tw[i].show(p);}
    //���濪ʼ��ÿ������ѡ�������ɾ����ȡ��
    if (m2p==1){
        QRect op1 (tw[tw_i].getx()-60, tw[tw_i].gety()+10, 50,50);
        p.drawImage(op1, remove);
        QRect op2 (tw[tw_i].getx()+10, tw[tw_i].gety()-60, 50, 50);
        p.drawImage(op2, up);
        QRect op3 (tw[tw_i].getx()+100, tw[tw_i].gety()+10, 50, 50);
        p.drawImage(op3, cancel);
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
                e1.erase(e1.begin()+i);
                score+=e1[i]->get_score();
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
        tw[i].getenemy(e1);
        tw[i].attack();}
    }
    if(id==timerid4){
        for(int i=0; i<tw.size(); i++){
        tw[i].attack();}
    }
    repaint();  //������Ľ����������ÿһ��ʱ��ˢ�µ���һ��paintevent����
}


int MainWindow::no_tower(int x, int y){
    int count=0, i=0;
    for (; i<tw.size(); i++){
        if (x==tw[i].getx() &&y==tw[i].gety()) {count++; break;}
    }
    if (count ==0) return -999;
    else return i;
}



void MainWindow::mousePressEvent(QMouseEvent *event){
    int mx=event->x();
    int my=event->y();
    mx=mx-mx%100;  //90�߳�Ϊһ����λ����      //mx��my���Ѿ�������ȡ100������
    my=my-my%100;
    int x=event->x();
    int y=event->y();
    QWidget::mousePressEvent(event);
    if (event->button()==Qt::LeftButton){                                     //�����ӣ���������򲻼�
        if (m2p==0)      //����0���Խ�����������ĳһ������ѡ��ģʽ
        {if (no_tower(mx, my)<0){    //С����˵��û��
            tw.push_back(Tower());
            double fx=static_cast<double>(mx);
            double fy=static_cast<double>(my);
            tw.back().set(fx, fy);}
        }
        if(m2p==1){
            if (x<tw[tw_i].getx()-10 && x>tw[tw_i].getx()-60 && y<tw[tw_i].gety()+60 && y>tw[tw_i].gety()+10){   //ɾ��ѡ���λ���ж�
                tw.erase(tw.begin()+tw_i);
            }
            if (x<tw[tw_i].getx()+60 && x>tw[tw_i].getx()+10 && y<tw[tw_i].gety()-10 && y>tw[tw_i].gety()-60){
                tw[tw_i].levelup();
            }
            if(x<tw[tw_i].getx()+150 && x>tw[tw_i].getx()+100 && y<tw[tw_i].gety()+60 && y>tw[tw_i].gety()+10){
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event){}

void MainWindow::mouseMoveEvent(QMouseEvent *event){}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //˫��ʵ���������������
    //int x=event->x();
    //int y=event->y();
    //int mx=x-x%100;
    //int my=y-y%100;
    //if (no_tower(mx,my)>=0){ int i=no_tower(mx,my); tw[i].levelup();
}

