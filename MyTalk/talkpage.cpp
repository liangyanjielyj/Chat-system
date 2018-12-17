#include "talkpage.h"
#include "ui_talkpage.h"
#include "addfriendpage.h"
#include "QPixmap"
#include "QIcon"
#include "QTreeWidgetItem"
#include "QDebug"
#include "protocal.h"
#include <QSqlQuery>
#include <QDebug>
#include "QTextCodec"
#include <QSqlError>
#include "database.h"
void TalkPage::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void TalkPage::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void TalkPage::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

TalkPage::TalkPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalkPage)
{
    ui->setupUi(this);

    QIcon *icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/head1.jpg"));
    ui->pushButton_4->setIcon(*icon);
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());

    icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/add.png"));
    ui->pushButton->setIcon(*icon);
    ui->pushButton->setIconSize(ui->pushButton->size());

    icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/set.png"));
    ui->pushButton_2->setIcon(*icon);
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());

    icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/1.png"));
    ui->pushButton_3->setIcon(*icon);
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());

    icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/2.png"));
    ui->pushButton_7->setIcon(*icon);
    ui->pushButton_7->setIconSize(ui->pushButton_7->size());

    icon = new QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/3.png"));
    ui->pushButton_6->setIcon(*icon);
    ui->pushButton_6->setIconSize(ui->pushButton_6->size());

    socket = new QUdpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvHandler()));

    ui->pushButton_8->setIcon(QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/close.png")));
    ui->pushButton_8->setIconSize(ui->pushButton_8->size());
    setWindowFlags(Qt::FramelessWindowHint);
}

TalkPage::~TalkPage()
{
    delete socket;
    delete ui;
}

void TalkPage::recvHandler()
{
    struct liaotian_st liaotian;
    QTreeWidgetItem *item;
    QString msg;

    socket->readDatagram((char *)&liaotian, sizeof(liaotian), NULL, NULL);
    switch (liaotian.status) {
    case HAOYOU_ITEM:
        item = new QTreeWidgetItem(ui->treeWidget);
        item->setIcon(0, QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/head3.jpg")));
        item->setText(0, liaotian.msg);
        break;
    case LIAOTIAN_STATUS_OK:
        //<font color="#FF0000">我是红色字体</font>
        msg.clear();
        msg.append(QString("<font color=\"#00FF00\" size=\"5\">"));
        msg.append(QString("["));
        msg.append(QString(liaotian.src_count));
        msg.append(QString("=>"));
        msg.append(QString(liaotian.dst_count));
        msg.append(QString("]# "));
        msg.append(QString(liaotian.msg));
        msg.append(QString("</font>"));
        ui->textEdit->append(msg);
    default:
        break;
    }
}

void TalkPage::talkPageShow()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setIcon(0, QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/head1.jpg")));
    item->setText(0, count);
    ui->label_2->setText(count);

    struct jizhudizhi_st jizhudizhi;
    qsnprintf(jizhudizhi.count, COUNT_SIZE, count.toStdString().c_str());
    QHostAddress *addr = new QHostAddress(JIZHUDIZHI_SERVER_IP);
    socket->writeDatagram((char *)&jizhudizhi, sizeof(jizhudizhi), *addr, JIZHUDIZHI_SERVER_PORT);

    show();
}

void TalkPage::on_pushButton_clicked()
{
    AddFriendPage *addFriendPage = new AddFriendPage();
    addFriendPage->setAttribute(Qt::WA_DeleteOnClose);
    addFriendPage->friendList = ui->treeWidget;
    addFriendPage->myCount = count;
    addFriendPage->show();
}

void TalkPage::on_pushButton_4_clicked()
{
    myDescPage.setGeometry(this->x(), this->y() + ui->pushButton_4->height() + 10, myDescPage.width(), myDescPage.height());
    myDescPage.setCount(count);
    myDescPage.show();
}

void TalkPage::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << item->text(0) << column;
    ui->label_2->setText(item->text(0));
}

void TalkPage::on_pushButton_5_clicked()
{
    QString msg;
    //<font color="#FF0000">我是红色字体</font>
    msg.clear();
    msg.append(QString("<font color=\"#FF0000\" size=\"5\">"));
    msg.append(QString("["));
    msg.append(count);
    msg.append(QString("=>"));
    msg.append(ui->label_2->text());
    msg.append(QString("]# "));
    msg.append(ui->textEdit_2->toPlainText());
    msg.append(QString("</font>"));

    ui->textEdit->append(msg);

    QString dstCount = ui->label_2->text();
    struct liaotian_st liaotian;

    qsnprintf(liaotian.dst_count, COUNT_SIZE, dstCount.toStdString().c_str());
    qsnprintf(liaotian.src_count, COUNT_SIZE, count.toStdString().c_str());
    qsnprintf(liaotian.msg, MSG_COUNT_SIZE, ui->textEdit_2->toPlainText().toStdString().c_str());
    QHostAddress *addr = new QHostAddress(QString(LIAOTIAN_SERVER_IP));
    socket->writeDatagram((const char *)&liaotian, sizeof(liaotian), *addr, LIAOTIAN_SERVER_PORT);
}


void TalkPage::on_pushButton_8_clicked()
{
    close();
}

void TalkPage::on_pushButton_9_clicked()
{
    QString msg;
    //<font color="#FF0000">我是红色字体</font>
    msg.clear();
    msg.append(QString("<font color=\"#FF0000\" size=\"5\">"));
    msg.append(QString("["));
    msg.append(count);
    msg.append(QString("=>"));
    msg.append(ui->label_2->text());
    msg.append(QString("]# "));
    msg.append(ui->textEdit_2->toPlainText());
    msg.append(QString("</font>"));

    ui->textEdit->append(msg);
    //调用表中好友进行群发
    QSqlQuery qry;
    struct liaotian_st liaotian;
    qDebug() << count;
    QString c = QString("%1%2").arg("table_").arg(count);
    QString sql = "select * from '"+c+"'";
    qry.prepare(sql);
    if( !qry.exec() ){
        qDebug() << qry.lastError();
    } else {
        while (qry.next()) {
            QString dstCount = qry.value(1).toString();
            qDebug() << dstCount;
            qsnprintf(liaotian.dst_count, COUNT_SIZE, dstCount.toStdString().c_str());
            qsnprintf(liaotian.src_count, COUNT_SIZE, count.toStdString().c_str());
            qsnprintf(liaotian.msg, MSG_COUNT_SIZE, ui->textEdit_2->toPlainText().toStdString().c_str());
            QHostAddress *addr = new QHostAddress(QString(LIAOTIAN_SERVER_IP));
            socket->writeDatagram((const char *)&liaotian, sizeof(liaotian), *addr, LIAOTIAN_SERVER_PORT);
        }
    }
}
