#include "showresultpage.h"
#include "ui_showresultpage.h"

ShowResultPage::ShowResultPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowResultPage)
{
    ui->setupUi(this);
}

void ShowResultPage::setButtonMsg(QString msg1, QString msg2)
{
    ui->pushButton->setText(msg1);
    ui->pushButton_2->setText(msg2);
}

void ShowResultPage::setMsg(QString msg)
{
    ui->label->setText(msg);
}

ShowResultPage::~ShowResultPage()
{
    delete ui;
}

void ShowResultPage::on_pushButton_clicked()
{
    close();
}

void ShowResultPage::on_pushButton_2_clicked()
{
    close();
}
