#include "start_window.h"
#include "ui_start_window.h"

start_window::start_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start_window)
{
    ui->setupUi(this);
    this->resize(900,600);
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
    MainWindow *w=new MainWindow(this);          //Ìø×ªÒ³Ãæ
    w->show();
    this->hide();
    //emit showmain1();
}
