#include "user.h"
#define DATABASE_NAME "users.db"

User::User(QString name)
{
    level = UserLevel::User;
    data["username"] = name;
    QString tableName="PERSONAL";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    db.open();
    readFromDatabase(name);
    emit onLogin();
}
User::User(QString name, QString bosss){
    level = UserLevel::User;
    this->setUserName(name);
    this->setBossName(bosss);
    QString tableName="PERSONAL";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    db.open();
    readFromDatabase(name);
    emit onLogin();
}
User::User(){
    level = UserLevel::User;
    QString tableName="PERSONAL";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    db.open();
    emit onLogin();
}
User::User(QString name ,Firma* f1 ,QString boss){
    level = UserLevel::User;
    data["username"] = name;
    firma = f1 ;
    this->setBossName(boss);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    db.open();
    readFromDatabase(name);
    emit onLogin();
}

void User::readFromDatabase(QString name) {
    data = UserManager::getUserData(name);
}

