#ifndef ODBCCONNECT_H
#define ODBCCONNECT_H

#include <QString>
#include <QTableView>
#include <QtSql>

class odbcConnect
{
public:
    odbcConnect();

    bool static save(QString filePath, QStringList headers, QList<QStringList> datam, QString comment="");
    bool static saveFromTable(QString filePath, QTableView *tableView, QString comment="");
    QString static getError(){return error;}

private:
    void static printError(QSqlError error);
    bool static insert(QSqlQuery &query, QString sheetName, QStringList slist);
    static QString error;
};

#endif // ODBCCONNECT_H
