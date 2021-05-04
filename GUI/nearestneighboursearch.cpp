#include "mainwindow.h"
#include "nearestneighboursearch.h"
#include "ui_nearestneighboursearch.h"
#include <QDebug>
#include <QVarLengthArray>
#include <QVector>
#include <QPair>
#include <QMessageBox>
#include <QPixmap>

NearestNeighbourSearch::NearestNeighbourSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NearestNeighbourSearch)
{
    ui->setupUi(this);
    QPixmap pix(":/img/cabLookup.jpg");
    ui->label_pic->setPixmap(pix.scaled(size()));
}

NearestNeighbourSearch::~NearestNeighbourSearch()
{
    delete ui;
}


double dist(int point[], int p[]) {
    int x1 = point[0];
    int y1 = point[1];
    int x2 = p[0];
    int y2 = p[1];
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

node* nearestNeighbourSearch(node* current, int p[], node* nearest, double &closest) {
    if (current == NULL) {
        //cout<<"hit base case"<<endl;
        closest = dist(nearest->point, p);
        return nearest;
    }

    if (dist(current->point, p) < dist(nearest->point, p)) {
        //cout<<"node is farther than current nearest"<<endl;
        nearest = current;
    }

    node* left = nearestNeighbourSearch(current->left, p, nearest, closest);
    if (dist(left->point, p) < dist(nearest->point, p)) {
        //cout<<"new champion: "<<left->point[0]<<","<<left->point[1]<<endl;
        nearest = left;
    }

    node* right = nearestNeighbourSearch(current->right, p, nearest, closest);
    if (dist(right->point, p) < dist(nearest->point, p)) {
        //cout<<"new champion: "<<right->point[0]<<","<<right->point[1]<<endl;
        nearest = right;
    }

    return nearest;
}

int *p = new int[2];
double closest = INT32_MAX;
void NearestNeighbourSearch::on_pushButton_clicked()
{
    QStringList l = ui->lineEditQP->text().split(" ");
    p[0] = l[0].toInt();
    p[1] = l[1].toInt();
    node* ans = nearestNeighbourSearch(root, p, root, closest);
    //qDebug() << ans->point[0] << " " << ans->point[1] << " "<< closest;
    QString res, dist;
    res += '(';
    res += QString::number(ans->point[0]);
    res += ',';
    res += QString::number(ans->point[1]);
    res += ')';

    dist += QString::number(closest);
    ui->textBrowser_dist->setText(dist);
    ui->textBrowser_res->setText(res);
}
