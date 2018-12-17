#include "addfriendpage.h"
#include "ui_addfriendpage.h"
#include "protocal.h"
#include "showresultpage.h"

AddFriendPage::AddFriendPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriendPage)
{
    ui->setupUi(this);
    socket = new QUdpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvHandler()));
}

AddFriendPage::~AddFriendPage()
{
    delete socket;
    delete ui;
}

void AddFriendPage::recvHandler()
{
    struct tianjiahaoyou_st tianjiahaoyou;
    ShowResultPage *showResultPage = new ShowResultPage();
    showResultPage->setAttribute(Qt::WA_DeleteOnClose);
    QTreeWidgetItem *item;

    socket->readDatagram((char *)&tianjiahaoyou, sizeof(tianjiahaoyou), NULL, NULL);
    switch (tianjiahaoyou.status) {
        case TIANJIAHAOYOU_STATUS_ERROR:
            showResultPage->setMsg(QString("抱歉！添加失败"));
            showResultPage->setButtonMsg(QString("重新添加"), QString("还是算了"));
            showResultPage->show();
            break;
        case TIANJIAHAOYOU_STATUS_OK:
            item = new QTreeWidgetItem(friendList);
            item->setIcon(0, QIcon(QString("/home/liangyanjie/bishe/MyTalk/images/head3.jpg")));
            item->setText(0, ui->lineEdit->text());
            break;
    }
}

void AddFriendPage::on_pushButton_clicked()
{
    struct tianjiahaoyou_st tianjiahaoyou;

    QString count = ui->lineEdit->text();
    qsnprintf(tianjiahaoyou.count, COUNT_SIZE, count.toStdString().c_str());
    qsnprintf(tianjiahaoyou.src_count, COUNT_SIZE, myCount.toStdString().c_str());
    QHostAddress *addr = new QHostAddress(QString(TIANJIAHAOYOU_SERVER_IP));
    socket->writeDatagram((const char *)&tianjiahaoyou, sizeof(tianjiahaoyou), *addr, TIANJIAHAOYOU_SERVER_PORT);
}


