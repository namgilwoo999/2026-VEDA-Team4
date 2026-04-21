#include "mainwindow.h"
#include "databasemanager.h"
#include "itemseed.h"
#include "itemdb.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager::Init();
    ItemDB db;
    ItemSeed::load(db);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
