#include "mainwindow.h"
#include <QApplication>
#include "connect_db.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString path = QString("/home/actiso/Test_DB/example.db");
    connect_db test(path);
    w.show();

    return a.exec();
}
