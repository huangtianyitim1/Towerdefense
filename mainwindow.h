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
    Enemy* gen_enemy(int i);    //����һ��ָ��ĳһ������˵Ļ���ָ��
    int no_tower(int x, int y);   //�ж����� �Ƿ�������û�з���-999���еĻ����ص�ǰ�����������
    void gettower(vector<Tower *> es);     //�߼��������˵��ӵ����ú�����յ�
    void ebattack();    //�����ӵ�����
    void gen_type();   //����һ�����˵�����id
    void load_current_wave();   //���ص�ǰ��һ���Ĵ���
    void load_next_wave();    //������һ����Ԥ--�������²�������Ч
    bool is_on=true;    //���ڽ���
    bool have_rested=false;   //�Ѿ���Ϣ���˵ı�ʶ
    int * type_checked;   //ѡ�е�����˳���id

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

signals:
    void rest();

private:
    Ui::MainWindow *ui;
    static const int WINDOW_W=900;  //�����
    const static int WINDOW_H=600;
    static const int MARGIN=0;  //��Ϸ�߽�
    QImage dot, map, remove, up, cancel;
    vector <Enemy *> e1 ;  //һȺ����(��һ��������ͬ)��ָ��
    int timerid1; //�����ƶ�ˢ�µ�id
    static int e_spd;  //�����ƶ�ˢ�µ�Ƶ��
    int timerid2;
    static int e_spd2; //���˲�����Ƶ��
    int timerid3;  //�ӵ�ˢ�²���id
    static int e_spd3;  //�ӵ�����Ƶ��
    int timerid4;  //�ӵ�ˢ���ƶ�id
    static int e_spd4;  //�ӵ��ƶ�ˢ��Ƶ��
    int timerid5;  //�����ӵ�ˢ���ƶ�id
    static int e_spd5;  //�����ӵ��ƶ�ˢ��Ƶ��
    int timerid6;  //ÿ�����id
    static int e_spd6;    //ÿ�����ʱ��
    const map1 m1;              //��ͼ������
    QTime time;
    vector <Tower *> tw;
    vector <EBullet *>ebs;   //���˵��ӵ����⻥�����ã�ֱ�ӷ�������
    int score;    //����
    QString s_score, s_wave, s_hp;  //�������֡�������Ѫ��
    int allhp;
    int hp;
    int m2p=0;   //���ͻ�ͼ���ӵ��ź�-------1���Ҽ���ѡ�����2��ѡ�������ഥ��
    int show_keng=0;   //��ʶ�ܷ񻭿�
    int tw_i;  //����������¼
    QImage* type_pic;    //��������˵���ͼ����
    QImage keng_pic;    //��ʱ����
    int local_x, local_y;  //���=�϶��õ����λ��
    int type_id; //��������
    int wave=1;    //���˲�������ʼ��Ϊ��1��
    bool is_next_load=false;   //�Ƿ������һ��
    vector <int> load_type;    //ÿһ�����˵�����
    int load_current_index=0; //���ص���һ���ĵڼ�������
    int *menu_x;       //�˵����ļ��
};

#endif // MAINWINDOW_H
