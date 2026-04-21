#include "mainwindow.h"
#include "shopwidget.h"
#include "loginwidget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShopWidget* shop = new ShopWidget();
    shop->show();

    LoginWidget* login = new LoginWidget();
    login->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
