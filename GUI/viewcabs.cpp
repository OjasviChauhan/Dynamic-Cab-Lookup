#include "mainwindow.h"
#include "viewcabs.h"
#include "ui_viewcabs.h"
#include <QPixmap>

QString str;
void print(node* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < k; i++){
        str += QString::number(root->point[i]);
        str += ",";
    }
    str += "\n";

    print(root->left);
    print(root->right);
}

ViewCabs::ViewCabs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewCabs)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
    str.clear();
    print(root);
    ui->CabsDataBox->setText(str);
}

ViewCabs::~ViewCabs()
{
    delete ui;
}

