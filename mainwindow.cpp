#include "mainwindow.h"
#include <QSqlTableModel>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = QString("/home/actiso/Test_DB/example.db");
    _sqlTut = new connect_db(path);
    bool result = _sqlTut->createTable();
    if(!result)
        qDebug()<< "create table failed";
//    ui->lineId->setPlaceholderText("id");
    ui->lineName->setPlaceholderText("name of product");
    ui->linePrice->setPlaceholderText("Price");
    id =_sqlTut->get_last_id_record();
    mode = new QSqlTableModel(this);
    mode->setTable("yen");
    mode->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mode->select();

    mode->setHeaderData(0, Qt::Horizontal, tr("ID"));
    mode->setHeaderData(1, Qt::Horizontal, tr("First name"));
    mode->setHeaderData(2, Qt::Horizontal, tr("Last name"));

    ui->tableView->setModel(mode);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
//    ui->horizontalLayout->addWidget(ui->tableView);
//    this->setLayout(ui->horizontalLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _sqlTut;
}

void MainWindow::on_pushButton_2_clicked()
{
    ++id;
    //add new item
    QSqlQuery addFeature;
//    QString id = ui->lineId->text();
    QString nameProduct = ui->lineName->text();
    QString price = ui->linePrice->text();
    int priceInt = price.toInt();
    addFeature.prepare("INSERT INTO yen (id, nameProduct, price) VALUES \
                       (:id, :namePro, :price);");

    addFeature.bindValue(":id",id);
    addFeature.bindValue(":namePro",nameProduct);// must has ":" , if not have error : NO query
    addFeature.bindValue(":price",priceInt);
//    addFeature.addBindValue(nameProduct);
//    addFeature.addBindValue(priceInt);
//    addFeature.addBindValue(true);

    if(addFeature.exec()){
        qDebug()<< "insert successfully";

    }else{
        qDebug()<< "insert failed"<< addFeature.lastError();
    }

    addFeature.finish();

}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery printQuery;
    printQuery.prepare("SELECT * FROM yen");
    printQuery.exec();
//    int id_id= printQuery.record().indexOf("id");
//    int id_pro = printQuery.record().indexOf("nameProduct");
//    int id_price = printQuery.record().indexOf("price");
//    while(printQuery.next()){
//        QString namePro = printQuery.value(id_pro).toString();
//        int price = printQuery.value(id_price).toInt();
//        qDebug() <<namePro <<":"<<price;
//    }
    printQuery.finish();
    mode->database().transaction();//connect db
    if(mode->submitAll()){
        qDebug() <<"Commit";
        mode->database().commit();
    }else{
        qDebug() <<"roolback";
        mode->database().rollback();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //display image
}
