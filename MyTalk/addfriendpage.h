#ifndef ADDFRIENDPAGE_H
#define ADDFRIENDPAGE_H

#include <QDialog>
#include <qtreewidget.h>
#include <QUdpSocket>

namespace Ui {
class AddFriendPage;
}

class AddFriendPage : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendPage(QWidget *parent = 0);
    ~AddFriendPage();
    QTreeWidget *friendList;
    QString myCount;
public slots:
    void recvHandler();
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddFriendPage *ui;
    QUdpSocket *socket;
};

#endif // ADDFRIENDPAGE_H
