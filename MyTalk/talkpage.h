#ifndef TALKPAGE_H
#define TALKPAGE_H

#include <QDialog>
#include "mydescpage.h"
#include "QTreeWidgetItem"
#include "QUdpSocket"
#include <QMouseEvent>


namespace Ui {
class TalkPage;
}

class TalkPage : public QDialog
{
    Q_OBJECT

public:
    explicit TalkPage(QWidget *parent = 0);
    ~TalkPage();
    QString count;
    void talkPageShow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void recvHandler();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    Ui::TalkPage *ui;
    MyDescPage myDescPage;
    QUdpSocket *socket;
    QPoint last;
};

#endif // TALKPAGE_H
