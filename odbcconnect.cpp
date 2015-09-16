#include "odbcconnect.h"
#include <QtSql>
#include <QTableView>

odbcConnect::odbcConnect()
{
}
QString odbcConnect::error;

bool odbcConnect::save(QString filePath, QStringList headers, QList<QStringList> data, QString comment){
    QString sheetName = "Interviewer";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
    QString dsn = "DRIVER={Microsoft Excel Driver (*.xls)};"
            "DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"test.xls\";DBQ=test.xls";
    db.setDatabaseName(dsn);
    if(!db.open()){
        qDebug() << "1";
        error = QString("Error1");
        return false;
    }

    QSqlQuery query(db);
    QString sql;

    sql = QString("DROP TABLE [%1]").arg(sheetName);
    query.exec(sql);

    sql = QString("CREATE TABLE [%1] (").arg(sheetName);
    foreach(QString name, headers){
        sql += QString("[%1] varchar(200)").arg(name);
        if(name != headers.last()){
            sql += ",";
        }
    }
    sql += ")";
    query.prepare(sql);
    if(!query.exec()){
        printError(query.lastError());
        db.close();
        return false;
    }

    foreach(QStringList slist, data){
        insert(query, sheetName, slist);
    }

    if(!comment.isEmpty()){
        QStringList slist;
        slist << comment;
        for(int i = 0, n = headers.size()-1; i < n; ++i){
            slist << "";
        }
        insert(query, sheetName, slist);
    }

    db.close();
    return true;
}

bool odbcConnect::saveFromTable(QString filePath, QTableView *tableView, QString comment){
    QAbstractItemModel* model=  tableView->model();

    const int column = model->columnCount();
    const int row = model->rowCount();

    QStringList headers;
    for(int i = 0; i < column; ++i){
        headers << model->headerData(i, Qt::Horizontal).toString();
    }

    QStringList list;
    QList<QStringList> data;
    for(int i = 0; i < row; ++i){
        if(model->index(i, 0).data().isNull())
            continue;
        list.clear();
        for(int j = 0; j < column; ++j){
            list << model->index(i, j).data().toString();
        }
        data << list;
    }
    return save(filePath, headers, data, comment);
}

void odbcConnect::printError(QSqlError error){
    QString sqlerr = error.text();
    error = sqlerr;
    qCritical() << sqlerr;
}

bool odbcConnect::insert(QSqlQuery &query, QString sheetName, QStringList slist){
    QString sSql = QString("INSERT INTO [%1] VALUES(").arg(sheetName);
    for(int i = 0, n = slist.size(); i < n; ++i){
        sSql += QString(":%1").arg(i);
        if(i != n - 1){
            sSql += ",";
        }
        else{
            sSql += ")";
        }
    }
    query.prepare(sSql);
    for(int i = 0, n = slist.size(); i < n; ++i){
        query.bindValue(QString(":%1").arg(i), slist.at(i));
    }
    if(!query.exec()){
        printError(query.lastError());
        return false;
    }
    return true;
}


