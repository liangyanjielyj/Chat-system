#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>
#include "QUdpSocket"

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = 0);
    ~RegisterPage();

private slots:
    void on_pushButton_clicked();
    void recvHandler();

    void on_maleBox_clicked();

    void on_femaleBox_clicked();

private:
    Ui::RegisterPage *ui;
    QUdpSocket *socket;
};

#endif // REGISTERPAGE_H
