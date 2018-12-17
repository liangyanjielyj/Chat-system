#include "loginpage.h"
#include "ui_loginpage.h"
#include "QPixmap"
#include "registerpage.h"
#include "talkpage.h"
#include "showresultpage.h"
#include "protocal.h"
#include "showresultpage.h"
#include "QCryptographicHash"
#include "QDesktopWidget"
#include "mibao.h"

void LoginPage::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void LoginPage::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void LoginPage::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    QPixmap *pix = new QPixmap(QString("/home/liangyanjie/bishe/MyTalk/images/background.jpg"));
    *pix = pix->scaled(ui->backlabel->size());
    ui->backlabel->setPixmap(*pix);
    delete pix;

    pix = new QPixmap(QString("/home/liangyanjie/bishe/MyTalk/images/head1.jpg"));
    *pix = pix->scaled(ui->headLabel->size());
    ui->headLabel->setPixmap(*pix);
    delete pix;

    ui->pushButton_4->setIcon(QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/close.png")));
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());

    socket = new QUdpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvHandler()));

    this->setWindowFlags(Qt::FramelessWindowHint);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

LoginPage::~LoginPage()
{
    delete socket;
    delete ui;
}

void LoginPage::recvHandler()
{
   struct denglu_st denglu;
   ShowResultPage *showResultPage = new ShowResultPage();
   showResultPage->setAttribute(Qt::WA_DeleteOnClose);
   TalkPage *talkPage;

   socket->readDatagram((char *)&denglu, sizeof(denglu), NULL, NULL);
   switch (denglu.status) {
   case DENGLU_STATUS_ERROR:
       showResultPage->setMsg(QString("抱歉，登录失败"));
       showResultPage->setButtonMsg(QString("重新登录"), QString("还是算了"));
       showResultPage->show();
       break;
   case DENGLU_STATUS_OK:
       talkPage = new TalkPage();
       talkPage->setAttribute(Qt::WA_DeleteOnClose);
       delete showResultPage;
       talkPage->count = ui->countLineEdit->text();
       talkPage->talkPageShow();
       close();
   default:
       break;
   }
}

void LoginPage::on_pushButton_2_clicked()
{
    RegisterPage *registerPage = new RegisterPage();
    registerPage->setAttribute(Qt::WA_DeleteOnClose);
    registerPage->show();
}

void LoginPage::on_pushButton_clicked()
{
    struct denglu_st denglu;
    QString p = "$%^FG%$^&$FDFG$^%%$%^G";
    QString q = ",";

    QString count = ui->countLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    //QByteArray ba = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5).toHex();
    password = QString("%1%2%3").arg(p).arg(q).arg(password);
    qsnprintf(denglu.count, COUNT_SIZE, count.toStdString().c_str());
    qsnprintf(denglu.password, COUNT_SIZE, password.toStdString().c_str());

    QHostAddress *addr = new QHostAddress(QString(DENGLU_SERVER_IP));
    socket->writeDatagram((const char *)&denglu, sizeof(denglu), *addr, DENGLU_SERVER_PORT);
}

void LoginPage::on_pushButton_4_clicked()
{
    close();
}

void LoginPage::on_pushButton_5_clicked()
{
    close();
}

void LoginPage::on_pushButton_3_clicked()
{
    mibao * mi = new mibao();
    mi->show();
    this->close();
}
