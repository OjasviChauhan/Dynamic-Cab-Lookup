#ifndef RECTSEARCH_H
#define RECTSEARCH_H

#include <QDialog>

namespace Ui {
class RectSearch;
}

class RectSearch : public QDialog
{
    Q_OBJECT

public:
    explicit RectSearch(QWidget *parent = nullptr);
    ~RectSearch();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RectSearch *ui;
};

#endif // RECTSEARCH_H
