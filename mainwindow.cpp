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
    QRect target(800,400,10,20);
    QRect background(0,0,900,600);
    dot.load(":/images/button.png");
    p.drawImage(target, dot);
    map.load(":/images/map.jpg");
    p.drawImage(background, map);
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


bool MainWindow::no_tower(int x, int y){
    int count=0;
    for (int i=0; i<tw.size(); i++){
        if (x==tw[i].getx() &&y==tw[i].gety()) count++;
    }
    if (count ==0) return true;
    else return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int mx=event->x();
    int my=event->y();
    mx=mx-mx%100;  //90�߳�Ϊһ����λ����
    my=my-my%100;
    int x=event->x();
    int y=event->y();
    QWidget::mousePressEvent(event);
    if (event->button()==Qt::LeftButton){                                     //�����ӣ���������򲻼�
        if (no_tower(mx, my)){
            tw.push_back(Tower());
            double fx=static_cast<double>(mx);
            double fy=static_cast<double>(my);
            tw.back().set(fx, fy);}
    }
    if (event->button()==Qt::RightButton){    //�Ҽ�����һ����Χ��ɾ��
        for (int i=0; i<tw.size(); i++){
            if (tw[i].getx()+70>x && tw[i].getx()+20<x && tw[i].gety()+70>y
                    && tw[i].gety()+20<y) tw.erase(tw.begin()+i);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){}

void MainWindow::mouseMoveEvent(QMouseEvent *event){}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //˫��ʵ�����������ٱ��
    int x=event->x();
    int y=event->y();
    for (int i=0; i<tw.size(); i++){
        if (tw[i].getx()+70>x && tw[i].getx()+20<x && tw[i].gety()+70>y
                && tw[i].gety()+20<y) {tw[i].setspd(10); tw[i].levelup();
            }
}
}
