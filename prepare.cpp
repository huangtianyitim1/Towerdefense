#include "prepare.h"
#include "ui_prepare.h"

Prepare::Prepare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prepare)
{
    ui->setupUi(this);
    this->resize(800,500);
    is_checked=new int[12]();    //选中与否数组初始化为0
    ui->penhuolong->setVisible(false);
    ui->kuailong->setVisible(false);
    ui->shujiangui->setVisible(false);
    ui->leixilamu->setVisible(false);
    ui->jiekeluomu->setVisible(false);
    ui->dailong->setVisible(false);
    ui->wujitaina->setVisible(false);
    ui->wanpidan->setVisible(false);
    ui->pikaqiu->setVisible(false);
    ui->jidongniao->setVisible(false);
    ui->menghuan->setVisible(false);
    ui->ladiousi->setVisible(false);
    ui->liekongzuo->setVisible(false);
    ui->xueyifeilong->setVisible(false);
}

Prepare::~Prepare()
{
    delete ui;
}

void Prepare::on_pushButton_clicked()
{
emit back();
}

void Prepare::new_info(int wave){
    if (wave>=Waveinfo::wave1){    //这时wave已经+1了，所以不用像gentype那样减1
        ui->penhuolong->setVisible(true);
        ui->shujiangui->setVisible(true);
        ui->kuailong->setVisible(true);


        ui->jiekeluomu->setVisible(true);     //第一波后，新敌人捷克罗姆登场
    }
    if(wave>=Waveinfo::wave2){


        ui->jiekeluomu->setVisible(false);
        ui->dailong->setVisible(true);
    }
    if(wave>=Waveinfo::wave3){
        ui->leixilamu->setVisible(true);

        ui->jiekeluomu->setVisible(false);
        ui->dailong->setVisible(true);
}
    if(wave>=Waveinfo::wave4){
        ui->wanpidan->setVisible(true);

        ui->dailong->setVisible(false);
        ui->wujitaina->setVisible(true);
}

    if(wave>=Waveinfo::wave6){
        ui->pikaqiu->setVisible(true);

        ui->dailong->setVisible(false);
        ui->wujitaina->setVisible(true);
}

    if(wave>=Waveinfo::wave8){
        ui->jidongniao->setVisible(true);

        ui->wujitaina->setVisible(false);
        ui->xueyifeilong->setVisible(true);
}
    if(wave>=Waveinfo::wave9){
            ui->menghuan->setVisible(true);

            ui->wujitaina->setVisible(false);
            ui->xueyifeilong->setVisible(true);
    }
    if(wave>=Waveinfo::wave11){
            ui->ladiousi->setVisible(true);

            ui->xueyifeilong->setVisible(false);
            ui->liekongzuo->setVisible(true);
    }

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

void Prepare::on_wanpidan_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[4]=1;
    else is_checked[4]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_pikaqiu_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[5]=1;
    else is_checked[5]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_jidongniao_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[6]=1;
    else is_checked[6]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_menghuan_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[7]=1;
    else is_checked[7]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

void Prepare::on_ladiousi_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[8]=1;
    else is_checked[8]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}
