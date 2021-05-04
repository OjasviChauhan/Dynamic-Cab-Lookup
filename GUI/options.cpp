#include "mainwindow.h"
#include "options.h"
#include "ui_options.h"
#include <QPixmap>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
    ui->label_RRS->setStyleSheet("background-color: rgba(255, 255, 255);");
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_clicked()
{
    rectsearch = new RectSearch(this);
    rectsearch->show();
}

void Options::on_pushButton_3_clicked()
{
    viewcabs = new ViewCabs(this);
    viewcabs->show();
}

void Options::on_pushButton_2_clicked()
{
    nns = new NearestNeighbourSearch(this);
    nns->show();
}
