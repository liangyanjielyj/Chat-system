#include "database.h"

database::database(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../server/talk.sqlite");
    db.open();
}

database::~database(){
    this -> db.close();
}
