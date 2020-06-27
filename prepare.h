#ifndef PREPARE_H
#define PREPARE_H

#include <QDialog>
#include<QCloseEvent>
#include<QMessageBox>
#include<QPushButton>
#include<iostream>
#include<numeric>
using namespace std ;
namespace Ui {
class Prepare;
}

class Prepare : public QDialog
{
    Q_OBJECT

public:
    explicit Prepare(QWidget *parent = 0);
    ~Prepare();
    void closeEvent(QCloseEvent *event);
    int * is_checked;

private slots:
    void on_pushButton_clicked();


    void on_penhuolong_stateChanged(int arg1);


    void on_shujiangui_stateChanged(int arg1);

    void on_kuailong_stateChanged(int arg1);

    void on_leixilamu_stateChanged(int arg1);

signals:
    void back();

private:
    Ui::Prepare *ui;
};

#endif // PREPARE_H
