#include "prepare.h"
#include "ui_prepare.h"

Prepare::Prepare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prepare)
{
    ui->setupUi(this);
    this->resize(800,500);
    is_checked=new int[12]();    //ѡ����������ʼ��Ϊ0
    ui->penhuolong->setVisible(false);
    ui->kuailong->setVisible(false);
    ui->shujiangui->setVisible(false);
    ui->leixilamu->setVisible(false);
    ui->jiekeluomu->setVisible(false);
    ui->dailong->setVisible(false);
    ui->wujitaina->setVisible(false);
    ui->wanpidan->setVisible(false);
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
    if (wave>=Waveinfo::wave1){    //��ʱwave�Ѿ�+1�ˣ����Բ�����gentype������1
        ui->penhuolong->setVisible(true);

        ui->wanpidan->setVisible(true);
        ui->shujiangui->setVisible(true);
        ui->kuailong->setVisible(true);

        ui->jiekeluomu->setVisible(true);     //��һ�����µ��˽ݿ���ķ�ǳ�
    }
    if(wave>=Waveinfo::wave2){
        ui->leixilamu->setVisible(true);

        ui->jiekeluomu->setVisible(false);
        ui->dailong->setVisible(true);
    }
    if(wave>=Waveinfo::wave3){


        ui->jiekeluomu->setVisible(false);
        ui->dailong->setVisible(true);
}
    if(wave>=Waveinfo::wave4){


        ui->dailong->setVisible(false);
        ui->wujitaina->setVisible(true);
}
}

void Prepare::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("CLOSE THE WINDOW"),
        QString(tr("Warning: If You EXIT You Should RESTART The Game, So you Cannot Exit")),
        QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
        event->ignore();  //�����˳��źţ������������
    }
    else if (button == QMessageBox::Yes) {
        event->ignore();  //�����˳��źţ�����Ҳ���˳�
    }
}



void Prepare::on_penhuolong_stateChanged(int arg1)
{
    if (arg1==Qt::Checked)  is_checked[0]=1;
    else is_checked[0]=0;
    if(accumulate(is_checked, is_checked+12, 0)>6) ui->pushButton->setEnabled(false);    //��ֹ��ѡ�ˣ�������6�����ܷ���
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
