#include "registerpage.h"
#include "ui_registerpage.h"
#include "protocal.h"
#include "showresultpage.h"
#include "QCryptographicHash"
#include "QDebug"

RegisterPage::RegisterPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
    socket = new QUdpSocket();
    ui->femaleBox->setChecked(true);
    ui->maleBox->setChecked(false);
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvHandler()));
}

RegisterPage::~RegisterPage()
{
    delete socket;
    delete ui;
}

void RegisterPage::recvHandler()
{
   struct zhuce_st zhuce;
   ShowResultPage *showResultPage = new ShowResultPage();
   showResultPage->setAttribute(Qt::WA_DeleteOnClose);

   socket->readDatagram((char *)&zhuce, sizeof(zhuce), NULL, NULL);
   switch (zhuce.status) {
   case ZHUCE_STATUS_ERROR:
       showResultPage->setMsg(QString("抱歉！注册失败"));
       showResultPage->setButtonMsg(QString("重新注册"), QString("还是算了"));
       break;
   case ZHUCE_STATUS_OK:
       showResultPage->setMsg(QString("恭喜！注册成功"));
       showResultPage->setButtonMsg(QString("再来一个"), QString("还是算了"));
   default:
       break;
   }
   showResultPage->show();
}

void RegisterPage::on_pushButton_clicked()
{
    struct zhuce_st zhuce;
    QString p = "$%^FG%$^&$FDFG$^%%$%^G";
    QString q = ",";

    QString count = ui->countLineEdit->text();
    QString password = ui->passwdLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString mibao = ui->mibaolineEdit->text();

    //QByteArray ba = password.toLatin1();
    //ba = QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex();

    //qDebug() << count << password << name << ba;
    password = QString("%1%2%3").arg(p).arg(q).arg(password);
    qsnprintf(zhuce.count, COUNT_SIZE, count.toStdString().c_str());
    qsnprintf(zhuce.name, COUNT_SIZE, name.toStdString().c_str());
    qsnprintf(zhuce.password, COUNT_SIZE, password.toStdString().c_str());
    qsnprintf(zhuce.mibao,COUNT_SIZE, mibao.toStdString().c_str());
    if (ui->femaleBox->isChecked()) {
        zhuce.sex = FEMALE;
    } else {
        zhuce.sex = MALE;
    }

    QHostAddress *addr = new QHostAddress(QString(ZHUCE_SERVER_IP));
    socket->writeDatagram((const char *)&zhuce, sizeof(zhuce), *addr, ZHUCE_SERVER_PORT);
    qDebug() << zhuce.count << zhuce.mibao;
}

void RegisterPage::on_maleBox_clicked()
{
    ui->maleBox->setChecked(true);
    ui->femaleBox->setChecked(false);
}

void RegisterPage::on_femaleBox_clicked()
{
    ui->maleBox->setChecked(false);
    ui->femaleBox->setChecked(true);
}
