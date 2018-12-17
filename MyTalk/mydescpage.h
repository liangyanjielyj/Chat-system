#ifndef MYDESCPAGE_H
#define MYDESCPAGE_H

#include <QDialog>

namespace Ui {
class MyDescPage;
}

class MyDescPage : public QDialog
{
    Q_OBJECT

public:
    explicit MyDescPage(QWidget *parent = 0);
    ~MyDescPage();
    void setCount(QString count);

private:
    Ui::MyDescPage *ui;
};

#endif // MYDESCPAGE_H
