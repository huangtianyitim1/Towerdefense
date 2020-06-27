#include "prepare.h"
#include "ui_prepare.h"

Prepare::Prepare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prepare)
{
    ui->setupUi(this);
    this->resize(800,500);
    is_checked=new int[12]();    //选中与否数组初始化为0
}

Prepare::~Prepare()
{
    delete ui;
}

void Prepare::on_pushButton_clicked()
{
emit back();
}

void Prepare::closeEvent(QCloseEvent *event)

{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("CLOSE THE WINDOW"),
        QString(tr("Warning: If You EXIT You Should RESTART The Game, So you Cannot Exit")),
        QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        event->ignore();  //接受退出信号，程序也不退出
    }
}



void Prepare::on_penhuolong_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[0]=1;
    else is_checked[0]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);    //防止多选了，不多于6个才能返回
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_kuailong_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[1]=1;
    else is_checked[1]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_shujiangui_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[2]=1;
    else is_checked[2]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}


void Prepare::on_leixilamu_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[3]=1;
    else is_checked[3]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}
