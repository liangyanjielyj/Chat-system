#include "mibao.h"
#include "ui_mibao.h"
#include "database.h"
#include <QSqlError>
#include "loginpage.h"

mibao::mibao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mibao)
{
    ui->setupUi(this);
    //new database();
}

mibao::~mibao()
{
    delete ui;
}

void mibao::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../server/talk.sqlite");
    db.open();
    QSqlQuery qry;
    QSqlQuery query;
    QString uname = ui->namelineEdit->text();
    QString umibao = ui->mibaolineEdit->text();
    QString sql = "SELECT * FROM `register_table` WHERE `name` = '"+uname+"' and `mibao` = '"+umibao+"'";
    qry.prepare(sql);
    if( !qry.exec() ){
        qDebug() << "qry.lastError()";
    }else{
        if(qry.first()){
            QString name = qry.value(2).toString();
            QString password = qry.value(3).toString();
            QString mib      = qry.value(4).toString();
            QString pas = password.section(",",1,1);
            QString dd = "请记好你的密码:";
            pas = QString("%1%2").arg(dd).arg(pas);
            QMessageBox msgBox;
            msgBox.setText(pas);
            msgBox.exec();
            LoginPage *s = new LoginPage();
            s->show();
            this->close();
        }else {
            QMessageBox msgBox;
            msgBox.setText("用户名与密宝不匹配无法找回密码");
            msgBox.exec();
        }
    }
}

void mibao::on_pushButton_2_clicked()
{
    this->close();
}
