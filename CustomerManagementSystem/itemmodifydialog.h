#ifndef ITEMMODIFYDIALOG_H
#define ITEMMODIFYDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class ItemModifyDialog;
}

class ItemModifyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ItemModifyDialog(const Item& item, QWidget *parent = nullptr);
    ~ItemModifyDialog();

    Item getItem() const;

private slots:
    void onModifyButton();
    void onCancelButton();

private:
    Ui::ItemModifyDialog *ui;
};

#endif // ITEMMODIFYDIALOG_H