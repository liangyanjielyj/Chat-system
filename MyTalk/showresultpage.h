#ifndef SHOWRESULTPAGE_H
#define SHOWRESULTPAGE_H

#include <QDialog>

namespace Ui {
class ShowResultPage;
}

class ShowResultPage : public QDialog
{
    Q_OBJECT

public:
    explicit ShowResultPage(QWidget *parent = 0);
    ~ShowResultPage();

    void setMsg(QString msg);
    void setButtonMsg(QString msg1, QString msg2);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowResultPage *ui;
};

#endif // SHOWRESULTPAGE_H
