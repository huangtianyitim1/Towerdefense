#include "start_window.h"
#include "ui_start_window.h"

start_window::start_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start_window)
{
    ui->setupUi(this);
    this->resize(900,600);
    pre=new Prepare(this);    //�г���Ϣ����ĳ�ʼ��
}

start_window::~start_window()
{
    delete ui;
}

void start_window::paintEvent(QPaintEvent * ){
    QPainter p(this);
    background.load(":/images/fengmian_1.jpg");
    QRect size(0,0,900,600);
    p.drawImage(size, background);
}

void start_window::on_pushButton_clicked()
{
    w=new MainWindow(this);          //��תҳ��
    connect(w,SIGNAL(rest()),this,SLOT(show_prepare()));
    connect(pre,SIGNAL(back()),this,SLOT(showmain1()));
    w->show();
    this->minimumSize();
    //emit showmain1();
}

void start_window::show_prepare(){//�ص��г���Ϣ����
    pre->show();
}

void start_window::showmain1(){
    pre->hide();
    w->show();
    w->have_rested=true;
    w->is_on=true;
}
