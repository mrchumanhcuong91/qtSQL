#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQuery>
#include <QtSql>
#include <QMainWindow>
#include "connect_db.h"
#include <QSqlTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    int id;
    QSqlTableModel* mode;
    Ui::MainWindow *ui;
    QString _nameTable;
    QString _pathImage;
    connect_db* _sqlTut;
};

#endif // MAINWINDOW_H
