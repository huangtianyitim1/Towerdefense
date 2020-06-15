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
    Enemy* gen_enemy();    //����һ��ָ��ĳһ������˵Ļ���ָ��
    int no_tower(int x, int y);   //�ж����� �Ƿ�������û�з���-999���еĻ����ص�ǰ�����������

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    static const int WINDOW_W=900;  //�����
    const static int WINDOW_H=600;
    static const int MARGIN=0;  //��Ϸ�߽�
    QImage dot, map;
    vector <Enemy *> e1 ;  //һȺ����(��һ��������ͬ)��ָ��
    int timerid1; //�����ƶ�ˢ�µ�id
    static int e_spd;  //�����ƶ�ˢ�µ�Ƶ��
    int timerid2;
    static int e_spd2; //���˲�����Ƶ��
    int timerid3;  //�ӵ�ˢ�²���id
    static int e_spd3;  //�ӵ�����Ƶ��
    int timerid4;  //�ӵ�ˢ���ƶ�id
    static int e_spd4;  //�ӵ��ƶ�ˢ��Ƶ��
    map1 m1;
    QTime time;
    vector <Tower> tw;
    int score=0;    //����
    QString s_score;  //��������
};

#endif // MAINWINDOW_H
