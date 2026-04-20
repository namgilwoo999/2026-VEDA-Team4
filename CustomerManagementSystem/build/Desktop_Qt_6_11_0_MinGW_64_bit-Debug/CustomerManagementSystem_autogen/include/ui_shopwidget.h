/********************************************************************************
** Form generated from reading UI file 'shopwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOPWIDGET_H
#define UI_SHOPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShopWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *SearchProfileLayout;
    QLineEdit *Search;
    QToolButton *Profile;
    QHBoxLayout *CategoryItemLayout;
    QListWidget *Category;
    QScrollArea *Item;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *ShopWidget)
    {
        if (ShopWidget->objectName().isEmpty())
            ShopWidget->setObjectName("ShopWidget");
        ShopWidget->resize(784, 514);
        verticalLayout_2 = new QVBoxLayout(ShopWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        SearchProfileLayout = new QHBoxLayout();
        SearchProfileLayout->setObjectName("SearchProfileLayout");
        Search = new QLineEdit(ShopWidget);
        Search->setObjectName("Search");

        SearchProfileLayout->addWidget(Search);

        Profile = new QToolButton(ShopWidget);
        Profile->setObjectName("Profile");
        Profile->setPopupMode(QToolButton::ToolButtonPopupMode::MenuButtonPopup);

        SearchProfileLayout->addWidget(Profile);

        SearchProfileLayout->setStretch(1, 5);

        verticalLayout->addLayout(SearchProfileLayout);

        CategoryItemLayout = new QHBoxLayout();
        CategoryItemLayout->setObjectName("CategoryItemLayout");
        Category = new QListWidget(ShopWidget);
        new QListWidgetItem(Category);
        Category->setObjectName("Category");

        CategoryItemLayout->addWidget(Category);

        Item = new QScrollArea(ShopWidget);
        Item->setObjectName("Item");
        Item->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 493, 453));
        Item->setWidget(scrollAreaWidgetContents);

        CategoryItemLayout->addWidget(Item);

        CategoryItemLayout->setStretch(1, 10);

        verticalLayout->addLayout(CategoryItemLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ShopWidget);

        QMetaObject::connectSlotsByName(ShopWidget);
    } // setupUi

    void retranslateUi(QWidget *ShopWidget)
    {
        ShopWidget->setWindowTitle(QCoreApplication::translate("ShopWidget", "Form", nullptr));
        Search->setText(QString());
        Search->setPlaceholderText(QCoreApplication::translate("ShopWidget", "\352\262\200\354\203\211\354\226\264\353\245\274 \354\236\205\353\240\245\355\225\264 \354\243\274\354\204\270\354\232\224.", nullptr));
        Profile->setText(QCoreApplication::translate("ShopWidget", "\355\224\204\353\241\234\355\225\204", nullptr));

        const bool __sortingEnabled = Category->isSortingEnabled();
        Category->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = Category->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("ShopWidget", "Category", nullptr));
        Category->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ShopWidget: public Ui_ShopWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOPWIDGET_H
