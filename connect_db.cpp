#include "connect_db.h"
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
connect_db::connect_db(QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(m_db.open()){
        qDebug()<< "query to database successfully";
    }else{
        qDebug()<< "query to database failed"<< m_db.lastError();
    }
}

bool connect_db::createTable(){
    bool success = false;

    QSqlQuery tableQuery(m_db);
    tableQuery.prepare("CREATE TABLE imageData (id INTEGER PRIMARY KEY,\
                                                 nameProduct VARCHAR(64),\
                                                 price INTEGER,\
                                                 imageName BLOB)");
    if(tableQuery.exec()){
        qDebug()<< "Creat table successfully";
        success = true;
    }else {
        qDebug()<< "Create table failed";

    }
    tableQuery.finish();
    return success;

}
int connect_db::get_last_id_record(){
    QSqlQuery lastQuery(m_db);
    lastQuery.prepare("SELECT * FROM imageData ORDER BY 1 DESC LIMIT 1;");
    if(lastQuery.exec()){
        qDebug()<< "find last success";
    }else {
        qDebug()<< "find last failed";
    }
    int idInit = lastQuery.record().indexOf("id");
    while(lastQuery.next()){
        int idLast = lastQuery.value(idInit).toInt();
    //    int idInit = id_last.toInt();
        qDebug() << "id last : "<<idLast;
        lastQuery.finish();
        return idLast;
    }

}

connect_db::~connect_db(){
    if(m_db.open())
        m_db.close();
}
