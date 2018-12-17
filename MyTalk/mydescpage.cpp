#include "mydescpage.h"
#include "ui_mydescpage.h"

MyDescPage::MyDescPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDescPage)
{
    ui->setupUi(this);
    ui->lineEdit->setDisabled(true);
    QPixmap *pix = new QPixmap(QString("/home/liangyanjie/bishe/MyTalk/images/desc.jpg"));
    *pix = pix->scaled(ui->label->size());
    ui->label->setPixmap(*pix);
    delete pix;
}

MyDescPage::~MyDescPage()
{
    delete ui;
}

void MyDescPage::setCount(QString count)
{
    ui->lineEdit->setText(count);
}
