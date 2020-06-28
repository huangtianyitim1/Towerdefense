#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<iostream>

int start_x=800;
int start_y=520;
int MainWindow::e_spd=20;          //敌人移动刷新的频率
int MainWindow::e_spd2=2000;    //敌人产生的频率
int MainWindow::e_spd3=600;     //塔子弹产生频率
int MainWindow::e_spd4=5;        //塔子弹移动刷新频率
int MainWindow::e_spd5=1200;   //敌人子弹产生频率
int MainWindow::e_spd6=5000;  //每波间隔时间

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(WINDOW_W,WINDOW_H);   //设置界面大小
    initgame();
    setAttribute(Qt::WA_DeleteOnClose);    //子窗口关闭则停止运行
}

void MainWindow::initgame(){
    allhp=1000;
    hp=allhp;
    score=100000;   //------------------------------------------------------------------
    timerid1=startTimer(e_spd);    //刷新敌人移动
    timerid2=startTimer(e_spd2);   //刷新敌人数量
    timerid3=startTimer(e_spd3);  //子弹产生
    timerid4=startTimer(e_spd4);  //子弹移动
    timerid5=startTimer(e_spd5);  //敌人子弹产生
    timerid6=startTimer(e_spd6);  //每波间隔
    //tw.push_back(Tower());     一开始的一个塔
    //tw[0].set(400,320);
    type_checked=new int[6]{1,3,0,0,0,0};     //初始化只有id=1,3              ---------------------------------记得delete
    type_pic=new QImage[12];
    menu_x=new int[6]{110,210,310,410,510,610};  //菜单栏间距           ------------------------记得delete
    jidi=new Tower();
    jidi->set(0,120);
    boomtimer=new QTimer(this);
    freezetimer=new QTimer(this);
    enhancetimer=new QTimer(this);
    freezeplayer = new QMediaPlayer;
    enhanceplayer=new QMediaPlayer;
    //加载好地图、选项图标
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
    //e1[0]->set(start_x,start_y);//初始位置
    gen_type();   //产生一批敌人的种类id
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

void MainWindow::gen_type(){           //产生一串敌人种类的序列
    time = QTime::currentTime();     //随机数
    qsrand((uint) time.msec());
    if(wave<Waveinfo::wave5-1)  //--------------------------------这里wave5要换图了
        cout<<Waveinfo::wave4-1<<endl;
    for (int i=0; i<Waveinfo::num_phase1; i++){
        int t=qrand()%8+1;    //记得加1，是id而不是索引，wavetype决定了每一波有多少类敌人!!!!!
        load_type.push_back(t);
    }
}

void MainWindow::load_current_wave(){
        if(is_next_load==false){   //如果当前的没有加载完，加载当前的
        e1.push_back(gen_enemy(load_type[load_current_index]));
        cout<<load_type[load_current_index]<<"  "<<load_current_index<<endl;
        e1.back()->set(start_x, start_y);        //------------------------------------初始化敌人属性
        e1.back()->wave_enhance(wave);    //随着波数变强，主要是hp变多
        load_current_index++;
        if (load_current_index==load_type.size())
        {is_next_load=true;     //如果这一波加载满了，准备--加载下一波
            load_current_index=0;  //索引归0
            load_type.clear();}   //加载的种类 数组清空
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
    if (is_next_load==true && enemy_treated>=e1.size()){   //全部处理完的话
    gen_type();   //注意和wave++的先后顺序
    e1.clear();
    wave++;
    cout<<wave<<endl;
    //cout<<"next"<<endl;
    is_next_load=false;
    have_rested=false;   //加载下一波的时候，并不是在休息后
    for (int i=0; i<e1.size(); i++){     //清理干净敌人数组
        delete e1[i];
        e1[i]=NULL;
        e1.clear();
    }
    enemy_treated=0;  //处理量归零
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
    freezetimer->start(3000);    //冰冻三秒
    killTimer(timerid1);
    freezeplayer ->setMedia(QUrl("qrc:/sounds/freeze.mp3"));
    freezeplayer ->setVolume(30);
    freezeplayer ->play();
}

void MainWindow::freezedone(){
    freezeplayer->stop();
    timerid1=startTimer(e_spd);
}

void MainWindow::get_enhance(){          //全员强化
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
    //画边框
    p.drawRect(MARGIN, MARGIN, WINDOW_W-2*MARGIN, WINDOW_H-2*MARGIN);
    //QRect target(800,400,100,200);
    QRect background(0,0,900,600);
    //dot.load(":/images/apple.png");
    //p.drawImage(target, dot);
    p.drawImage(background, map);    //画背景
    //QRect type1(110,10,70,70);
    //QRect type2(210,10,70,70);
    //QRect type3(310,10,70,70);
    //QRect type4(410,10,70,70);
    for (int i=0; i<6;i++){
        if (type_checked[i]!=0){
            int tmp=type_checked[i];
            QRect type_i(menu_x[i],10,70,70);
            p.drawImage(type_i, type_pic[tmp-1]);  //记得-1，索引是从0开始的
        }
    }
    //p.drawImage(type1, type1_pic);   //画可选塔1：小火龙
    //p.drawImage(type2, type2_pic);   //画可选塔2：迷你龙
    //p.drawImage(type3, type3_pic);   //画可选塔3：杰尼龟
    //p.drawImage(type4, type4_pic);//画可选塔4：雷希拉姆
    //画对象
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
    p.setPen(QPen(1));        //家园血条
    p.setBrush(QBrush(Qt::red));
    p.drawRect(7, 90, 80*hp/allhp, 7);             //画血条
    if (e1.size()>0){
    for (int i=0; i<e1.size(); i++){
        if (!e1[i]->die() && !m1.outbound(e1[i]))         //死的屏蔽掉、出界的屏蔽掉
        e1[i]->show(p);
    }
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
        if (type_id==1) {p.drawImage(size, type_pic[0]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}   //小火龙射程200
        if (type_id==2) {p.drawImage(size, type_pic[1]); p.drawEllipse(QPoint(local_x+40, local_y+40), 180, 180);}  //  2号塔迷你龙射程180
        if (type_id==3) {p.drawImage(size, type_pic[2]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  3号塔杰尼龟射程200
        if (type_id==4) {p.drawImage(size, type_pic[3]); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  4号塔雷希拉姆射程250
        if (type_id==5) {p.drawImage(size, type_pic[4]); p.drawEllipse(QPoint(local_x+40, local_y+40), 250, 250);}  //  5号顽皮弹射程250
         if (type_id==6) {p.drawImage(size, type_pic[5]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  6号皮卡丘射程200
         if (type_id==7) {p.drawImage(size, type_pic[6]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  7号急冻鸟
         if (type_id==8) {p.drawImage(size, type_pic[7]); p.drawEllipse(QPoint(local_x+40, local_y+40), 200, 200);}  //  8号梦幻
         if (type_id==9) {p.drawImage(size, type_pic[8]); p.drawEllipse(QPoint(local_x+40, local_y+40), 300, 300);}  //  9号拉帝亚斯
    }


    for (int i=0; i<ebs.size(); i++){
    ebs[i]->show(p);      //敌人的子弹单独画
    }
    for (int i=0; i<ebs2.size(); i++){
    ebs2[i]->show(p);      //敌人的子弹单独画
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
            else if(m1.outbound(e1[i]) &&e1[i]->has_hurt_hp==false){     //进入家园，家掉血
                hp-=e1[i]->get_damage();
                enemy_treated+=1;
                e1[i]->has_hurt_hp=true;
            }
        }
    }
    if(id==timerid2){
        if (Waveinfo::you_can_rest(wave)  && have_rested==false){emit rest(); is_on=false; }    //暂停的波数
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
        for (int i=0; i<tw.size();i++){    //检测 塔是否阵亡
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
    mx=mx-mx%100;  //90边长为一个单位？？      //mx和my都已经经过了取100整处理
    my=my-my%100+20;  //-----------------------------------mx和my都是经过取整百处理，用来判断==，其中my+20了
    int x=event->x();
    int y=event->y();
    QWidget::mousePressEvent(event);

    if (y<=100){    ///////////////工具栏，选择塔类型
    if(x<160 &&x>100){
        if (type_checked[0]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[0];
      type_id=tmp; }//(小火龙id)第一个选的塔的id
    }
    if(x<260 &&x>200){
        if (type_checked[1]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[1];
      type_id=tmp; }     //(迷你龙id)第二个选的塔id
    }
    if(x<360 &&x>300){
        if (type_checked[2]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[2];
      type_id=tmp; } //杰尼龟id
    }
    if(x<460 &&x>400){
        if (type_checked[3]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[3];
      type_id=tmp; } //雷希拉姆id------------------------------------------
    }
    if(x<560 &&x>500){
        if (type_checked[4]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[4];
      type_id=tmp; }
    }
    if(x<660 &&x>600){
        if (type_checked[5]>0){
      local_x=x;
      local_y=y;
      m2p=2;    //拖动的信号
      int tmp=type_checked[5];
      type_id=tmp; }
    }
    repaint();
    }

    if (y>100 || m2p==1) {   //在工具栏下面才能操作
    if (event->button()==Qt::LeftButton){                                     //左键添加，有喷火龙则不加
        if (m2p==0)      //等于0可以建塔，否则在某一个塔的选项模式
        {}
        if(m2p==1){   //塔选项模式
            if (x<tw[tw_i]->getx()-10
                    && x>tw[tw_i]->getx()-60
                    && y<tw[tw_i]->gety()+60
                    && y>tw[tw_i]->gety()+10){   //删除选项的位置判断，注意指针记得释放指向对象的内存
                delete tw[tw_i];  //虽然tw[tw_i]是对应的原来的twp的拷贝，但是delete同样也起到了释放指向塔对象内存的作用
                tw[tw_i]=NULL;
                tw.erase(tw.begin()+tw_i);
                score+=200;    //铲除的补偿
                m2p=0;  //非常重要！！！这里如果不化为0，则会重复删除导致内存泄漏
            }
            else if (x<tw[tw_i]->getx()+60
                    && x>tw[tw_i]->getx()+10
                    && y<tw[tw_i]->gety()-10
                    && y>tw[tw_i]->gety()-60){
                if (score>=tw[tw_i]->get_level_score()){    //分数足够才能进化
                score-=tw[tw_i]->levelup();}   //扣除进化的分数
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

    int mx=event->x()-event->x()%100;
    int my=event->y()-event->y()%100+20;   //100取整下来一点
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
    if (score>=twp->get_make_score()  && m1.can_put(mx,my-20)){        //分数足够则可以进行种塔且这个位置能种
    tw.push_back(twp);   //这里压入twp其实是做了一个拷贝
    if (tw.back()->getid()==5) emit boom();   //顽皮弹爆炸
    if (tw.back()->getid()==7) emit freeze();   //冰冻3s
    if (tw.back()->getid()==8) emit enhance();  //全员强化
    score-=twp->get_make_score();}    //消耗分数
    else {     //分数不够，或者没法放，删除
        delete twp;
        twp=NULL;
    }
    }
    m2p=0;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){    //双击也可以删除，不建议用
  /*  int mx=event->x();
    int my=event->y();
    mx=mx-mx%100;   //mx和my都已经经过了取100整处理
    my=my-my%100+20;  //-----------------------------------mx和my都是经过取整百处理，用来判断==，其中my+20了
    int i=no_tower(mx,my);      //定位到塔的索引（如果有塔）
    if (i>=0) {
        delete tw[i];     //释放指向的塔对象
        tw.erase(tw.begin()+i);
        m2p=0;    //防止选项出现后又删除
}*/
}



void MainWindow::gettower(vector <Tower*> es){       //敌人的进攻在主界面实现
    if (es.size()>0 && e1.size()>0){
    for (int i=0; i<e1.size(); i++){
        if (e1[i]->get_id()==4 && !e1[i]->die()){    //没死才能进攻
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
            EBullet *bp=new EBullet(":/images/zuqiu.png");
            ebs.push_back(bp);
            ebs.back()->set(x+30, y+30, es[ei]);
            ebs.back()->set_id(e1[i]->get_id()+10);
            ebs.back()->setspd(e1[i]->get_bullet_spd());     //初始化子弹的射速
            ebs.back()->setpower(e1[i]->get_power());   //子弹威力
            cout<<"launch"<<endl;
                }
        }
        if (e1[i]->get_id()==8 && !e1[i]->die()){    //没死才能进攻
            int x=e1[i]->getx();
            int y=e1[i]->gety();
            cout<<"1111111111111111111"<<endl;
            //cout<<ex<<"------"<<ey<<endl;
            EBullet *bp=new EBullet(":/images/huoqiu.png");
            ebs2.push_back(bp);
            ebs2.back()->set(x+30, y+30, jidi);
            ebs2.back()->set_id(e1[i]->get_id()+10);
            ebs2.back()->setspd(e1[i]->get_bullet_spd());     //初始化子弹的射速
            ebs2.back()->setpower(e1[i]->get_power());   //子弹威力
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
            ebs[i]=NULL;
            ebs.erase(ebs.begin()+i);                  //打中扣血，子弹消失
        }
        else if (ebs[i]->getx()>960 || ebs[i]->gety()>540 || ebs[i]->getx()<-10 || ebs[i]->gety()<-10){
            delete ebs[i];                      //删除子弹对象占有的内存
            ebs[i]=NULL;
            ebs.erase(ebs.begin()+i);          //到界外了，删除
        }
    }
    for(int i=0; i<ebs2.size(); i++){         //每颗子弹都移动, 自己的方向已经设置好了
        ebs2[i]->move();
        cout<<"1111111111111111111"<<endl;
        if (ebs2[i]->shootdown()){
            hp-=ebs2[i]->getp();

            delete ebs2[i];         //删除子弹对象占有的内存
            ebs2[i]=NULL;
            ebs2.erase(ebs2.begin()+i);                  //打中扣血，子弹消失
        }
        else if (ebs2[i]->getx()>960 || ebs2[i]->gety()>540 || ebs2[i]->getx()<-10 || ebs2[i]->gety()<-10){
            delete ebs2[i];                      //删除子弹对象占有的内存
            ebs2[i]=NULL;
            ebs2.erase(ebs2.begin()+i);          //到界外了，删除
        }
    }
}


void MainWindow::on_pushButton_clicked()      //暂停游戏
{
    if (is_on)  is_on=false;
    else is_on=true;
}


