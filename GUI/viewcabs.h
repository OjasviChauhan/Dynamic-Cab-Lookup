#ifndef VIEWCABS_H
#define VIEWCABS_H

#include <QDialog>

namespace Ui {
class ViewCabs;
}

class ViewCabs : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCabs(QWidget *parent = nullptr);
    ~ViewCabs();

private:
    Ui::ViewCabs *ui;
};

#endif // VIEWCABS_H
