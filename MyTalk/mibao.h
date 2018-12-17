#ifndef MIBAO_H
#define MIBAO_H

#include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "QCryptographicHash"
namespace Ui {
class mibao;
}

class mibao : public QWidget
{
    Q_OBJECT

public:
    explicit mibao(QWidget *parent = 0);
    ~mibao();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mibao *ui;
};

#endif // MIBAO_H
