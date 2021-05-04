#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString c;
void MainWindow::on_pushButton_clicked()
{
    c = ui->lineEdit->text();
    if(c == "0"){
        QMessageBox::information(this,"","No Cabs");
    }
    else{
        //qDebug() << c.toInt();
        secPage = new SecDialog(this);
        secPage->show();
        //hide();
    }
}


