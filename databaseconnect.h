#ifndef DATABASECONNECT_H
#define DATABASECONNECT_H

#include <QtSql>

#include <QDebug>

static bool DatabaseConnect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("Propaganda_Department");
    db.setDatabaseName("Interviewer.db");
    db.setUserName("Erwa");

    if(!db.open()){
        qDebug() << "Can't open database!\n";
        return false;
    }

    QSqlQuery query;
    query.exec(QString("create table type(id int primary key, name varchar)"));
    query.exec(QString("insert into type value(0, 'Person')"));
    query.exec(QString("create table brand(id int primary key, name varchar, "
                       "phone varchar, gender varchar, profile int, skill int, "
                       "nature int, performance int, comment varchar)"));

    query.exec("create table password(pwd varchar primary key)");
    query.exec("insert into password value('0')");

    return true;
}

#endif // DATABASECONNECT_H

