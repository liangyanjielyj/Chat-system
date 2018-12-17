#ifndef XIUGMM_H
#define XIUGMM_H

#include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
namespace Ui {
class xiugmm;
}

class xiugmm : public QWidget
{
    Q_OBJECT

public:
    explicit xiugmm(QWidget *parent = 0);
    ~xiugmm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::xiugmm *ui;
};

#endif // XIUGMM_H
