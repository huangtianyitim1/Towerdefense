#ifndef PREPARE_H
#define PREPARE_H

#include <QDialog>

namespace Ui {
class Prepare;
}

class Prepare : public QDialog
{
    Q_OBJECT

public:
    explicit Prepare(QWidget *parent = 0);
    ~Prepare();

private slots:
    void on_pushButton_clicked();

signals:
    void back();

private:
    Ui::Prepare *ui;
};

#endif // PREPARE_H
