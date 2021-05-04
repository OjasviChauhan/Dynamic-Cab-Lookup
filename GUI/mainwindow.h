#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SecDialog *secPage;
};

const int k = 2;
class node {
public:
    int point[k]; // To store k dimensional point
    node* left;
    node* right;

    // constructor to create a node of KD tree
    node(int arr[]) {
        for (int i = 0; i < k; i++) {
            point[i] = arr[i];
        }
        left = NULL;
        right = NULL;
    }
};

extern int myglobalint;
extern node* root;
extern QString c;

#endif // MAINWINDOW_H
