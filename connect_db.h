#ifndef CONNECT_DB_H
#define CONNECT_DB_H
#include <QtSql/QSql>
#include <QSqlDatabase>
// class connect_db : connect to database, create table,
// add new item, insert item
class connect_db
{
private:
    QSqlDatabase m_db;
public:
    connect_db(QString& path);
    bool createTable();
    bool addNewItem();
    bool insertNewItem();
    int get_last_id_record();
    ~connect_db();
};

#endif // CONNECT_DB_H
