#ifndef SECDIALOG_H
#define SECDIALOG_H

#include "options.h"
#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecDialog *ui;
    Options *option;
};

#endif // SECDIALOG_H
