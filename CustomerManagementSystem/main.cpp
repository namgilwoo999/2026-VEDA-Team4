#include "mainwindow.h"
#include "databasemanager.h"
#include "itemseed.h"
#include "itemdb.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        a.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
    DatabaseManager::Init();
    ItemDB db;
    ItemSeed::load(db);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
