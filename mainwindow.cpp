#include "mainwindow.h"
#include <QSqlTableModel>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QByteArray>
#include <QPixmap>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QSqlError>
#include <QFileDialog>
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
    ui->lineNameImage->setPlaceholderText("path to Image");
    id =_sqlTut->get_last_id_record();
    mode = new QSqlTableModel(this);
    mode->setTable("imageData");
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
    QFile file(_pathImage);
    //add new item
    QSqlQuery addFeature;
//    QString id = ui->lineId->text();
    QString nameProduct = ui->lineName->text();
    QString price = ui->linePrice->text();
    //load image -> QImage->QbyteArray->save to db
//    if(!_pathImage.isEmpty())
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<"Read success";
    }else{
        qDebug()<<"Read failed";
        return;
    }
    QByteArray inByteArray = file.readAll();

    int priceInt = price.toInt();
    addFeature.prepare("INSERT INTO imageData (id, nameProduct, price, imageName) VALUES \
                       (:id, :namePro, :price,:imagedata);");

    addFeature.bindValue(":id",id);
    addFeature.bindValue(":namePro",nameProduct);// must has ":" , if not have error : NO query
    addFeature.bindValue(":price",priceInt);
    addFeature.bindValue(":imagedata",inByteArray);
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
    printQuery.prepare("SELECT imageName FROM imageData");
    printQuery.exec();
//    int id_id= printQuery.record().indexOf("id");
    int idImage = printQuery.record().indexOf("imageName");
//    int id_price = printQuery.record().indexOf("price");
    while(printQuery.next()){
        QByteArray imageArray = printQuery.value(idImage).toByteArray();
//        int price = printQuery.value(id_price).toInt();
//        qDebug() <<namePro <<":"<<price;
        QPixmap pixmap = QPixmap();
        pixmap.loadFromData(imageArray);
        QPixmap p1(pixmap.scaled(150, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        ui->labelImage->setPixmap(p1);
        ui->labelImage->show();
        ui->labelImage->setFixedHeight(p1.height());
        ui->labelImage->setFixedWidth(p1.width());
    }
    printQuery.finish();
    mode->database().transaction();//connect db
    if(mode->submitAll()){
        qDebug() <<"Commit";
        mode->database().commit();
    }else{
        qDebug() <<"roolback";
        mode->database().rollback();
    }
    _pathImage ="";
    ui->lineNameImage->setPlaceholderText("path to Image");
//debug
}

void MainWindow::on_pushButton_3_clicked()
{
    QWidget* exam = new QWidget();
    _pathImage = QFileDialog::getOpenFileName(exam, tr("Open File"),
                                              "/home", tr("Images (*.jpg *.xpm *.png *.jpeg)"));
    ui->lineNameImage->setText(_pathImage);
    exam->hide();
//    QDialog* log = new QDialog(this);
//    log->show();
}
