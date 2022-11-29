#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "info.h"
#include "IItemModel.h"

class Database : public IItemModel
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = 0);
    virtual ~Database();

    virtual InventoryItemData inventoryItem() const;
    virtual void setInventoryItem(const InventoryItemData &inventoryItemData);
    virtual InventoryTableData inventoryTable() const;

signals:

public slots:
    virtual void updateCellData(const InventoryCellData& cellData);
    virtual void clearInventoryTable();

protected:
    QString m_databaseName = "inventory.db";
    QSqlDatabase m_database;

};

#endif // DATABASE_H
