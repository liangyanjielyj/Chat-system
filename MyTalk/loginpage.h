#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "QUdpSocket"
#include <QMouseEvent>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void recvHandler();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LoginPage *ui;
    QUdpSocket *socket;
    QPoint last;
};

#endif // LOGINPAGE_H
