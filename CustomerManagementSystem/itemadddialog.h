#ifndef ITEMADDDIALOG_H
#define ITEMADDDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class ItemAddDialog;
}

class ItemAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ItemAddDialog(QWidget *parent = nullptr);
    ~ItemAddDialog();

    Item getItem() const;

private slots:
    void onAddButton();
    void onCancelButton();

private:
    Ui::ItemAddDialog *ui;
};

#endif // ITEMADDDIALOG_H