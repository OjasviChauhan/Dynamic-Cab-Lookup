#include "mainwindow.h"
#include "secdialog.h"
#include "options.h"
#include "ui_secdialog.h"
#include <QPixmap>
#include <QVector>
#include <QDebug>
#include <QVarLengthArray>
#include <QMessageBox>
#include <iostream>
using namespace std;

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
}

SecDialog::~SecDialog()
{
    delete ui;
}

node* insert(node* root, int point[], unsigned depth) {
    if (root == NULL)
        return new node(point);

    unsigned cd = depth % k;

    if (point[cd] < (root->point[cd]))
        root->left  = insert(root->left, point, depth + 1);
    else
        root->right = insert(root->right, point, depth + 1);

    return root;
}

int *points = new int[2];
QString CD;
node* root = NULL;

void SecDialog::on_pushButton_clicked()
{
    CD = ui->textEdit->toPlainText();
    QStringList list = CD.split("\n");

    if(list.size() < c.toInt()){
        int diff = c.toInt() - list.size();
        QString s = QString::number(diff);
        QMessageBox::warning(this,"","You have inserted less data!! Insert "+ s +" more");
    }
    else{
        if(list.size() > c.toInt()){
            QMessageBox::warning(this,"","You have inserted more data!!\n"
            "The Previous final data will be considered");
        }
        for(int i=0; i < qMin(list.size(),c.toInt()); i++){
            QStringList p = list[i].split(" ");
            points[0] = p[0].toInt();
            points[1] = p[1].toInt();
            root = insert(root, points, 0);
        }
        QMessageBox::information(this,"","All data inserted Successfully!!");
        hide();
        option = new Options(this);
        option->show();
    }
}
