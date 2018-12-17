#include "xiugmm.h"
#include "ui_xiugmm.h"
#include <QSqlError>
xiugmm::xiugmm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xiugmm)
{
    ui->setupUi(this);
}

xiugmm::~xiugmm()
{
    delete ui;
}

void xiugmm::on_pushButton_clicked()
{
  /*  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../server/talk.sqlite");
    db.open();
    QSqlQuery qry;
    QString sql = "SELECT * FROM `register_table` WHERE `name` = '"+uname+"' and `mibao` = '"+umibao+"'";
    qry.prepare(sql);
    if( !qry.exec() ){
        qDebug() << qry.lastError();
    }else{
        this->close();

        }
    }*/
}
