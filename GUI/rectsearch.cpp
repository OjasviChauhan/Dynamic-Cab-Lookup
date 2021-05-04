#include "mainwindow.h"
#include "rectsearch.h"
#include "ui_rectsearch.h"
#include <QDebug>
#include <QVarLengthArray>
#include <QVector>
#include <QPair>
#include <QMessageBox>
#include <QPixmap>

RectSearch::RectSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectSearch)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
}

RectSearch::~RectSearch()
{
    delete ui;
}

bool isInsideRect(int x1, int y1, int x2, int y2, int x, int y) {
    if (x > x1 and x < x2 and y > y1 and y < y2)
        return true;
    return false;
}

void rangeSearch2D(node* root, unsigned depth, int recLB[2], int recTR[], QVector<QPair<int,int>> &count) {
    if (root == NULL) {
        //cout<<"hit base case"<<endl;
        return;
    }
    //cout<<root->point[0]<<","<<root->point[1]<<endl;

    unsigned cd = depth % k;
    int x = root->point[0];
    int y = root->point[1];
    int recX1 = recLB[0];
    int recY1 = recLB[1];
    int recX2 = recTR[0];
    int recY2 = recTR[1];

    // plain is getting divided vertically
    if (cd == 0) {
        // rectangle is on the left side of dividing line
        if (x > recX1 and x > recX2) {
            //cout<<"rectangle is on the left side"<<endl;
            rangeSearch2D(root->left, depth + 1, recLB, recTR, count);
        }
        // rectangle is on the right side of dividing line
        else if (x < recX1 and x < recX2) {
            //cout<<"rectangle is on the right side"<<endl;
            rangeSearch2D(root->right, depth + 1, recLB, recTR, count);
        }
        // dividing line is intersecting the rectangle
        else if (x >= recX1 and x <= recX2) {
            //cout<<"vertically intersecting"<<endl;

            if (isInsideRect(recX1, recY1, recX2, recY2, x, y))
                count.push_back({x, y});

            rangeSearch2D(root->left, depth + 1, recLB, recTR, count);
            rangeSearch2D(root->right, depth + 1, recLB, recTR, count);
        }
    }

    // plain is dividing horizontally
    else {
        // rectangle is below
        if (y > recY1 and y > recY2) {
            //cout<<"rectangle is below"<<endl;
            rangeSearch2D(root->left, depth + 1, recLB, recTR, count);
        }
        // rectangle is above
        else if (y < recY1 and y < recY2) {
            //cout<<"rectangle is above"<<endl;
            rangeSearch2D(root->right, depth + 1, recLB, recTR, count);
        }
        // dividing line is intersecting the rectangle
        else if (y >= recY1 and y <= recY2) {
            //cout<<"horizontally intersecting"<<endl;

            if (isInsideRect(recX1, recY1, recX2, recY2, x, y))
                count.push_back({x, y});

            rangeSearch2D(root->left, depth + 1, recLB, recTR, count);
            rangeSearch2D(root->right, depth + 1, recLB, recTR, count);
        }
    }
}

int *pointLB = new int[2];
int *pointTR = new int[2];
QVector<QPair<int,int>> count;

void RectSearch::on_pushButton_clicked()
{
    QStringList l1 = ui->lineEditLeftBottom->text().split(" ");
    QStringList l2 = ui->lineEditTopRight->text().split(" ");
    pointLB[0] = l1[0].toInt();
    pointLB[1] = l1[1].toInt();
    pointTR[0] = l2[0].toInt();
    pointTR[1] = l2[1].toInt();

    count.clear();
    rangeSearch2D(root, 0, pointLB, pointTR, count);
    if(count.empty()){
        QMessageBox::critical(this,"","There are no cabs inside the Rectangle!");
    }
    else{
        QString str;
        for(int i=0;i<count.size();i++){
            str += '(';
            str += QString::number(count[i].first);
            str += ',';
            str += QString::number(count[i].second);
            str += ")\n";
        }
        ui->ansBox->setText(str);
    }
}
