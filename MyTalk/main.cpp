#include "loginpage.h"
#include <QApplication>
#include "QTextCodec"
#include "database.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new database();
    LoginPage w;
    w.show();
    return a.exec();
}
