#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<iostream>

int start_x=800;
int start_y=520;
int MainWindow::e_spd=20;          //�����ƶ�ˢ�µ�Ƶ��
int MainWindow::e_spd2=2000;    //���˲�����Ƶ��
int MainWindow::e_spd3=600;     //���ӵ�����Ƶ��
int MainWindow::e_spd4=5;        //���ӵ��ƶ�ˢ��Ƶ��
int MainWindow::e_spd5=1200;   //�����ӵ�����Ƶ��
int MainWindow::e_spd6=5000;  //ÿ�����ʱ��

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(WINDOW_W,WINDOW_H);   //���ý����С
    initgame();
    setAttribute(Qt::WA_DeleteOnClose);    //�Ӵ��ڹر���ֹͣ����
}

void MainWindow::initgame(){
    allhp=1000;
    hp=allhp;
    score=100000;   //------------------------------------------------------------------
    timerid1=startTimer(e_spd);    //ˢ�µ����ƶ�
    timerid2=startTimer(e_spd2);   //ˢ�µ�������
    timerid3=startTimer(e_spd3);  //�ӵ�����
    timerid4=startTimer(e_spd4);  //�ӵ��ƶ�
    timerid5=startTimer(e_spd5);  //�����ӵ�����
    timerid6=startTimer(e_spd6);  //ÿ�����
    //tw.push_back(Tower());     һ��ʼ��һ����
    //tw[0].set(400,320);
    type_checked=new int[6]{1,3,0,0,0,0};     //��ʼ��ֻ��id=1,3              ---------------------------------�ǵ�delete
    type_pic=new QImage[12];
    menu_x=new int[6]{110,210,310,410,510,610};  //�˵������           ------------------------�ǵ�delete
    jidi=new Tower();
    jidi->set(0,120);
    boomtimer=new QTimer(this);
    freezetimer=new QTimer(this);
    enhancetimer=new QTimer(this);
    freezeplayer = new QMediaPlayer;
    enhanceplayer=new QMediaPlayer;
    //���غõ�ͼ��ѡ��ͼ��
    map.load(":/images/map1.png");
    remove.load(":/images/chanzi.png");
    up.load(":/images/shengji.png");
    cancel.load(":/images/quxiao.png");
    type_pic[0].load(":/images/xiaohuolong.png");
    type_pic[1].load(":/images/minilong.png");
    type_pic[2].load(":/images/jienigui.png");
    type_pic[3].load(":/images/leixilamu.png");
    type_pic[4].load(":/images/wanpidan.png");
    type_pic[5].load(":/images/pikaqiu.png");
    type_pic[6].load(":/images/jidongniao.png");
    type_pic[7].load(":/images/menghuan.png");
    type_pic[8].load(":/images/ladiyasi.png");
    keng_pic.load(":/images/keng.png");
    //e1.push_back(gen_enemy(1));
    //e1[0]->set(start_x,start_y);//��ʼλ��
    gen_type();   //����һ�����˵�����id
    ui->boomlabel->setVisible(false);
    connect(this, SIGNAL(boom()), this, SLOT(setboom()));
    connect(this->boomtimer, SIGNAL(timeout()), this, SLOT(boomdone()));
    connect(this,SIGNAL(freeze()),this,SLOT(setfreeze()));
    connect(freezetimer,SIGNAL(timeout()),this, SLOT(freezedone()));
    connect(this, SIGNAL(enhance()), this, SLOT(get_enhance()));
    connect(enhancetimer, SIGNAL(timeout()),this, SLOT(enhancedone()));
}

void MainWindow::recieve_start(){
    this->show();
}

void MainWindow::gen_type(){           //����һ���������������
    time = QTime::currentTime();     //�����
    qsrand((uint) time.msec());
    if(wave<Waveinfo::wave5-1)  //--------------------------------����wave5Ҫ��ͼ��
        cout<<Waveinfo::wave4-1<<endl;
    for (int i=0; i<Waveinfo::num_phase1; i++){
        int t=qrand()%8+1;    //�ǵü�1����id������������wavetype������ÿһ���ж��������!!!!!
        load_type.push_back(t);
    }
}

void MainWindow::load_current_wave(){
        if(is_next_load==false){   //�����ǰ��û�м����꣬���ص�ǰ��
        e1.push_back(gen_enemy(load_type[load_current_index]));
        cout<<load_type[load_current_index]<<"  "<<load_current_index<<endl;
        e1.back()->set(start_x, start_y);        //------------------------------------��ʼ����������
        e1.back()->wave_enhance(wave);    //���Ų�����ǿ����Ҫ��hp���
        load_current_index++;
        if (load_current_index==load_type.size())
        {is_next_load=true;     //�����һ���������ˣ�׼��--������һ��
            load_current_index=0;  //������0
            load_type.clear();}   //���ص����� �������
        }
    }


Enemy* MainWindow::gen_enemy(int i){
    Enemy* p;
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
    case 7:  //S
        p=new Enemy7();
        break;
    case 8:  //S
        p=new Enemy8();
        break;

    }
        return p;
}


void MainWindow::load_next_wave(){
    if (is_next_load==true && enemy_treated>=e1.size()){   //ȫ��������Ļ�
    gen_type();   //ע���wave++���Ⱥ�˳��
    e1.clear();
    wave++;
    cout<<wave<<endl;
    //cout<<"next"<<endl;
    is_next_load=false;
    have_rested=false;   //������һ����ʱ�򣬲���������Ϣ��
    for (int i=0; i<e1.size(); i++){     //����ɾ���������
        delete e1[i];
        e1[i]=NULL;
        e1.clear();
    }
    enemy_treated=0;  //����������
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setboom(){
    double x=tw.back()->getx()-230, y=tw.back()->gety()-230;
    ui->boomlabel->setGeometry(x, y, 530, 530);
    ui->boomlabel->setScaledContents(true);
    ui->boomlabel->setVisible(true);
    movie = new QMovie(":/images/boom.gif");
    ui->boomlabel->setMovie(movie);
    movie->start();
    boomtimer->setSingleShot(true);
    boomtimer->start(1500);
}

void MainWindow::boomdone(){
    movie->stop();
    delete movie;
    movie=NULL;
    ui->boomlabel->setVisible(false);
}

void MainWindow::setfreeze(){
    freezetimer->setSingleShot(true);
    freezetimer->start(3000);    //��������
    killTimer(timerid1);
    freezeplayer ->setMedia(QUrl("qrc:/sounds/freeze.mp3"));
    freezeplayer ->setVolume(30);
    freezeplayer ->play();
}

void MainWindow::freezedone(){
    freezeplayer->stop();
    timerid1=startTimer(e_spd);
}

void MainWindow::get_enhance(){          //ȫԱǿ��
    for (int i=0; i<tw.size(); i++){
        double tmp=tw[i]->get_power();
        tw[i]->set_power(tmp+5);
    }
    enhancetimer->setSingleShot(true);
    enhancetimer->start(3000);
    enhanceplayer->setMedia(QUrl("qrc:/sounds/enhance.mp3"));
    enhanceplayer->setVolume(30);
    enhanceplayer->play();
}

void MainWindow::enhancedone(){
    enhanceplayer->stop();
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
    //QRect type1(110,10,70,70);
    //QRect type2(210,10,70,70);
    //QRect type3(310,10,70,70);
    //QRect type4(410,10,70,70);
    for (int i=0; i<6;i++){
        if (type_checked[i]!=0){
            int tmp=type_checked[i];
            QRect type_i(menu_x[i],10,70,70);
            p.drawImage(type_i, type_pic[tmp-1]);  //�ǵ�-1�������Ǵ�0��ʼ��
        }
    }
    //p.drawImage(type1, type1_pic);   //����ѡ��1��С����
    //p.drawImage(type2, type2_pic);   //����ѡ��2��������
    //p.drawImage(type3, type3_pic);   //����ѡ��3�������
    //p.drawImage(type4, type4_pic);//����ѡ��4����ϣ��ķ
    //������
    draw(p);
}

void MainWindow::draw(QPainter &p){
    s_score="Score: "+QString::number(score);
    s_wave="Wave: "+QString::number(wave);
    s_hp="Hp: "+QString::number(hp);
    QFont font("Microsoft YaHei", 12, 75);
    p.setFont(font);
    p.setPen(Qt::black);
    p.drawText(720,10,200,50,Qt::AlignLeft,s_score);
    p.drawText(720,40,200,50,Qt::AlignLeft,s_wave);
    p.setPen(Qt::red);
    p.drawText(720, 70, 200,50,Qt::AlignLeft,s_hp);
    p.setPen(QPen(1));        //��԰Ѫ��
    p.setBrush(QBrush(Qt::red));
    p.drawRect(7, 90, 80*hp/allhp, 7);             //��Ѫ��
    if (e1.size()>0){
    for (int i=0; i<e1.size(); i++){
        if (!e1[i]->die() && !m1.outbound(e1[i]))         //�������ε�����������ε�
        e1[i]->show(p);
    }
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
        if (type_id==1) {p.drawImage(size, type_pic[0]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}   //С�������200
        if (type_id==2) {p.drawImage(size, type_pic[1]); p.drawEllipse(QPoint(local_x+40, local_y+40), 180, 180);}  //  2�������������180
        if (type_id==3) {p.drawImage(size, type_pic[2]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  3������������200
        if (type_id==4) {p.drawImage(size, type_pic[3]); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  4������ϣ��ķ���250
        if (type_id==5) {p.drawImage(size, type_pic[4]); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  5����Ƥ�����250
         if (type_id==6) {p.drawImage(size, type_pic[5]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  6��Ƥ�������200
         if (type_id==7) {p.drawImage(size, type_pic[6]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  7�ż�����
         if (type_id==8) {p.drawImage(size, type_pic[7]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  8���λ�
         if (type_id==9) {p.drawImage(size, type_pic[8]); p.drawEllipse(QPoint(local_x+40, local_y+40), 300, 300);}  //  9��������˹
    }


    for (int i=0; i<ebs.size(); i++){
    ebs[i]->show(p);      //���˵��ӵ�������
    }
    for (int i=0; i<ebs2.size(); i++){
    ebs2[i]->show(p);      //���˵��ӵ�������
    }
}


void MainWindow::timerEvent(QTimerEvent *e){
    int id = e->timerId();
    if (is_on){
    if (id==timerid1){
        for (int i=0; i<e1.size(); i++){
            //e1[i].setspd(1);
            e1[i]->move();
            m1.collide_check(e1[i]);
            //cout<<e1[i].gethp()<<endl;
            if(e1[i]->die() && e1[i]->has_scored==false){
                score+=e1[i]->get_score();
                enemy_treated+=1;
                e1[i]->has_scored=true;
            }
            else if(m1.outbound(e1[i]) &&e1[i]->has_hurt_hp==false){     //�����԰���ҵ�Ѫ
                hp-=e1[i]->get_damage();
                enemy_treated+=1;
                e1[i]->has_hurt_hp=true;
            }
        }
    }
    if(id==timerid2){
        if (Waveinfo::you_can_rest(wave)  && have_rested==false){emit rest(); is_on=false; }    //��ͣ�Ĳ���
        else load_current_wave();
    repaint(); }
    if (id==timerid6){
        load_next_wave();
        repaint();
    }
    if(id==timerid3){
        for(int i=0; i<tw.size(); i++){
        tw[i]->getenemy(e1);
        tw[i]->attack();
        }
        for (int i=0; i<tw.size();i++){    //��� ���Ƿ�����
            if (tw[i]->get_hp()<=0){
                delete tw[i];
                tw[i]=NULL;
                tw.erase(tw.begin()+i);
            }
        }
        repaint();
    }
    if(id==timerid4){
        for(int i=0; i<tw.size(); i++){
        tw[i]->attack();}
        ebattack();
        repaint();
    }
    if(id==timerid5){
        gettower(tw);
        repaint();
    }

}
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
        if (type_checked[0]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[0];
      type_id=tmp; }//(С����id)��һ��ѡ������id
    }
    if(x<260 &&x>200){
        if (type_checked[1]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[1];
      type_id=tmp; }     //(������id)�ڶ���ѡ����id
    }
    if(x<360 &&x>300){
        if (type_checked[2]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[2];
      type_id=tmp; } //�����id
    }
    if(x<460 &&x>400){
        if (type_checked[3]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[3];
      type_id=tmp; } //��ϣ��ķid------------------------------------------
    }
    if(x<560 &&x>500){
        if (type_checked[4]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[4];
      type_id=tmp; }
    }
    if(x<660 &&x>600){
        if (type_checked[5]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //�϶����ź�
      int tmp=type_checked[5];
      type_id=tmp; }
    }
    repaint();
    }

    if (y>100 || m2p==1) {   //�ڹ�����������ܲ���
    if (event->button()==Qt::LeftButton){                                     //�����ӣ���������򲻼�
        if (m2p==0)      //����0���Խ�����������ĳһ������ѡ��ģʽ
        {}
        if(m2p==1){   //��ѡ��ģʽ
            if (x<tw[tw_i]->getx()-10
                    && x>tw[tw_i]->getx()-60
                    && y<tw[tw_i]->gety()+60
                    && y>tw[tw_i]->gety()+10){   //ɾ��ѡ���λ���жϣ�ע��ָ��ǵ��ͷ�ָ�������ڴ�
                delete tw[tw_i];  //��Ȼtw[tw_i]�Ƕ�Ӧ��ԭ����twp�Ŀ���������deleteͬ��Ҳ�����ͷ�ָ���������ڴ������
                tw[tw_i]=NULL;
                tw.erase(tw.begin()+tw_i);
                score+=200;    //�����Ĳ���
                m2p=0;  //�ǳ���Ҫ�����������������Ϊ0������ظ�ɾ�������ڴ�й©
            }
            else if (x<tw[tw_i]->getx()+60
                    && x>tw[tw_i]->getx()+10
                    && y<tw[tw_i]->gety()-10
                    && y>tw[tw_i]->gety()-60){
                if (score>=tw[tw_i]->get_level_score()){    //�����㹻���ܽ���
                score-=tw[tw_i]->levelup();}   //�۳������ķ���
            }
            else if(x<tw[tw_i]->getx()+150
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

    int mx=event->x()-event->x()%100;
    int my=event->y()-event->y()%100+20;   //100ȡ������һ��
    if (no_tower(mx,my)<0){
    Tower * twp;
    double fx=static_cast<double>(mx);
    double fy=static_cast<double>(my);
    if (type_id==1) {twp=new Tower(); twp->set(fx, fy); }
    if (type_id==2) {twp=new Tower2(); twp->set(fx, fy);}
    if (type_id==3) {twp=new Tower3(); twp->set(fx, fy);}
    if (type_id==4) {twp=new Tower4(); twp->set(fx, fy);}
    if (type_id==5) {twp=new Tower5(); twp->set(fx, fy);}
    if (type_id==6) {twp=new Tower6(); twp->set(fx, fy);}
    if (type_id==7) {twp=new Tower7(); twp->set(fx, fy);}
     if (type_id==8) {twp=new Tower8(); twp->set(fx, fy);}
     if (type_id==9) {twp=new Tower9(); twp->set(fx, fy);}
    if (score>=twp->get_make_score()  && m1.can_put(mx,my-20)){        //�����㹻����Խ������������λ������
    tw.push_back(twp);   //����ѹ��twp��ʵ������һ������
    if (tw.back()->getid()==5) emit boom();   //��Ƥ����ը
    if (tw.back()->getid()==7) emit freeze();   //����3s
    if (tw.back()->getid()==8) emit enhance();  //ȫԱǿ��
    score-=twp->get_make_score();}    //���ķ���
    else {     //��������������û���ţ�ɾ��
        delete twp;
        twp=NULL;
    }
    }
    m2p=0;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //˫��Ҳ����ɾ������������
  /*  int mx=event->x();
    int my=event->y();
    mx=mx-mx%100;   //mx��my���Ѿ�������ȡ100������
    my=my-my%100+20;  //-----------------------------------mx��my���Ǿ���ȡ���ٴ��������ж�==������my+20��
    int i=no_tower(mx,my);      //��λ���������������������
    if (i>=0) {
        delete tw[i];     //�ͷ�ָ���������
        tw.erase(tw.begin()+i);
        m2p=0;    //��ֹѡ����ֺ���ɾ��
}*/
}



void MainWindow::gettower(vector <Tower*> es){       //���˵Ľ�����������ʵ��
    if (es.size()>0 && e1.size()>0){
    for (int i=0; i<e1.size(); i++){
        if (e1[i]->get_id()==4 && !e1[i]->die()){    //û�����ܽ���
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
            EBullet *bp=new EBullet(":/images/zuqiu.png");
            ebs.push_back(bp);
            ebs.back()->set(x+30, y+30, es[ei]);
            ebs.back()->set_id(e1[i]->get_id()+10);
            ebs.back()->setspd(e1[i]->get_bullet_spd());     //��ʼ���ӵ�������
            ebs.back()->setpower(e1[i]->get_power());   //�ӵ�����
            cout<<"launch"<<endl;
                }
        }
        if (e1[i]->get_id()==8 && !e1[i]->die()){    //û�����ܽ���
            int x=e1[i]->getx();
            int y=e1[i]->gety();
            cout<<"1111111111111111111"<<endl;
            //cout<<ex<<"------"<<ey<<endl;
            EBullet *bp=new EBullet(":/images/huoqiu.png");
            ebs2.push_back(bp);
            ebs2.back()->set(x+30, y+30, jidi);
            ebs2.back()->set_id(e1[i]->get_id()+10);
            ebs2.back()->setspd(e1[i]->get_bullet_spd());     //��ʼ���ӵ�������
            ebs2.back()->setpower(e1[i]->get_power());   //�ӵ�����
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
            ebs[i]=NULL;
            ebs.erase(ebs.begin()+i);                  //���п�Ѫ���ӵ���ʧ
        }
        else if (ebs[i]->getx()>960 || ebs[i]->gety()>540 || ebs[i]->getx()<-10 || ebs[i]->gety()<-10){
            delete ebs[i];                      //ɾ���ӵ�����ռ�е��ڴ�
            ebs[i]=NULL;
            ebs.erase(ebs.begin()+i);          //�������ˣ�ɾ��
        }
    }
    for(int i=0; i<ebs2.size(); i++){         //ÿ���ӵ����ƶ�, �Լ��ķ����Ѿ����ú���
        ebs2[i]->move();
        cout<<"1111111111111111111"<<endl;
        if (ebs2[i]->shootdown()){
            hp-=ebs2[i]->getp();

            delete ebs2[i];         //ɾ���ӵ�����ռ�е��ڴ�
            ebs2[i]=NULL;
            ebs2.erase(ebs2.begin()+i);                  //���п�Ѫ���ӵ���ʧ
        }
        else if (ebs2[i]->getx()>960 || ebs2[i]->gety()>540 || ebs2[i]->getx()<-10 || ebs2[i]->gety()<-10){
            delete ebs2[i];                      //ɾ���ӵ�����ռ�е��ڴ�
            ebs2[i]=NULL;
            ebs2.erase(ebs2.begin()+i);          //�������ˣ�ɾ��
        }
    }
}


void MainWindow::on_pushButton_clicked()      //��ͣ��Ϸ
{
    if (is_on)  is_on=false;
    else is_on=true;
}


