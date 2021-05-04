#ifndef OPTIONS_H
#define OPTIONS_H

#include "rectsearch.h"
#include "viewcabs.h"
#include "nearestneighboursearch.h"
#include <QDialog>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Options *ui;
    RectSearch *rectsearch;
    ViewCabs *viewcabs;
    NearestNeighbourSearch *nns;
};

#endif // OPTIONS_H
