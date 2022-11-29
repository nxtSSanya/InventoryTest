#include <QApplication>

#include "inventorycontroller.h"
#include "mainwindow.h"

/* Точка входа */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    InventoryController controller(&w);

    return a.exec();
}
