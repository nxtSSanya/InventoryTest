#ifndef INVENTORYCONTROLLER_H
#define INVENTORYCONTROLLER_H

#include <QObject>

#include "IItemModel.h"
#include "mainwindow.h"

class InventoryController : public QObject
{
    Q_OBJECT
public:
    explicit InventoryController(MainWindow* view, QObject *parent = 0);
    virtual ~InventoryController();

signals:

public slots:

protected:
    IItemModel* m_model;
    MainWindow* m_view;

    QString m_windowTitle = "Inventory test";

};

#endif // INVENTORYCONTROLLER_H
