#ifndef NEARESTNEIGHBOURSEARCH_H
#define NEARESTNEIGHBOURSEARCH_H

#include <QDialog>

namespace Ui {
class NearestNeighbourSearch;
}

class NearestNeighbourSearch : public QDialog
{
    Q_OBJECT

public:
    explicit NearestNeighbourSearch(QWidget *parent = nullptr);
    ~NearestNeighbourSearch();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NearestNeighbourSearch *ui;
};

#endif // NEARESTNEIGHBOURSEARCH_H
