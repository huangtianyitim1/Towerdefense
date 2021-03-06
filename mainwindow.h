#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include<QTime>
#include"map1.h"
#include<vector>
#include"tower.h"
#include<QString>
#include"enemy_s.h"
#include"tower_s.h"
#include"enemy_bullet.h"
#include<QTimer>
#include"wave_info.h"
#include<QMovie>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initgame();
    void draw(QPainter &p);
    Enemy* gen_enemy(int i);    //返回一个指向某一子类敌人的基类指针
    int no_tower(int x, int y);   //判断这里 是否有塔，没有返回-999，有的话返回当前鼠标塔的索引
    void gettower(vector<Tower *> es);     //逻辑：给敌人的子弹设置好起点终点
    void ebattack();    //敌人子弹进攻
    void gen_type();   //产生一批敌人的种类id
    void load_current_wave();   //加载当前这一波的处理
    void load_next_wave();    //加载下一波的预--处理，更新波数和音效
    bool is_on=true;    //正在进行
    bool have_rested=false;   //已经休息过了的标识
    int * type_checked;   //选中的塔按顺序的id
    int next_wave() const {return wave;}   //下一波的波数
    friend int get_num_per_type(int wave);
    int AI_choose();    //弱AI选择起点



protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);


private slots:
    void recieve_start();
    void on_pushButton_clicked();
    void setboom();
    void boomdone();
    void setfreeze();
    void freezedone();
    void get_enhance();
    void enhancedone();

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

signals:
    void rest();
    void boom();
    void freeze();
    void enhance();
    void gameover();

private:
    Ui::MainWindow *ui;
    static const int WINDOW_W=900;  //界面宽
    const static int WINDOW_H=600;
    static const int MARGIN=0;  //游戏边界
    QImage dot, map, map2, map3, remove, up, cancel;
    vector <Enemy *> e1 ;  //一群敌人(不一定类型相同)的指针
    int timerid1; //敌人移动刷新的id
    static int e_spd;  //敌人移动刷新的频率
    int timerid2;
    static int e_spd2; //敌人产生的频率
    int timerid3;  //子弹刷新产生id
    static int e_spd3;  //子弹产生频率
    int timerid4;  //子弹刷新移动id
    static int e_spd4;  //子弹移动刷新频率
    int timerid5;  //敌人子弹刷新移动id
    static int e_spd5;  //敌人子弹移动刷新频率
    int timerid6;  //每波间隔id
    static int e_spd6;    //每波间隔时间
    const map1 m1;              //地图常对象
    QTime time;
    vector <Tower *> tw;
    vector <EBullet *>ebs;   //敌人的子弹避免互相引用，直接放主界面
    vector <EBullet*> ebs2;   //直接打基地的子弹
    int score;    //分数
    QString s_score, s_wave, s_hp;  //分数文字、波数、血量
    int allhp;
    int hp;
    int m2p=0;   //鼠标和画图连接的信号-------1是右键塔选项触发，2是选择塔种类触发
    int show_keng=0;   //标识能否画坑
    int tw_i;  //塔的索引记录
    QImage* type_pic;    //塔的种类菜单栏图数组
    QImage keng_pic;    //临时画坑
    int local_x, local_y;  //针对=拖动用的鼠标位置
    int type_id; //塔的种类
    int wave=1;    //敌人波数，初始化为第1波
    bool is_next_load=false;   //是否加载下一波
    vector <int> load_type;    //每一波敌人的种类
    int load_current_index=0; //加载的这一波的第几个敌人
    int *menu_x;       //菜单栏的间隔
    QTimer *boomtimer;
    QTimer *freezetimer;
    QTimer *enhancetimer;
    QMovie* movie; //装gif
    int enemy_treated=0;   //处理完的敌人，包括进家园和死的
    QMediaPlayer * freezeplayer;
    QMediaPlayer *enhanceplayer;
    QMediaPlayer *bgm;
    QMediaPlayer *warning;
    QMediaPlayer *scoring;
    QMediaPlayer *planting;
    QMediaPlayer *leveling;
    bool on_bgm;
    Tower *jidi;   //模拟塔目标
    int phase=1;   //大的关卡
};

#endif // MAINWINDOW_H
