#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager::Init();
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
