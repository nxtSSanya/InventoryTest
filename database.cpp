#include <QFile>
#include <QSqlError>
#include <QVariant>

#include "database.h"

Database::Database(QObject *parent) : IItemModel(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databaseName);
    m_database.open();

    QSqlQuery query = QSqlQuery(m_database);
    query.exec("CREATE TABLE IF NOT EXISTS InventoryItem (id INTEGER PRIMARY KEY, name TEXT UNIQUE, sound TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS InventoryTable (id INTEGER PRIMARY KEY, row INTEGER, column INTEGER, count INTEGER)");
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS InventoryTableSize ON InventoryTable (row, column)");

}

Database::~Database()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

InventoryItemData Database::inventoryItem() const
{

    QSqlQuery query = QSqlQuery(m_database);
    query.exec("SELECT name, sound FROM InventoryItem LIMIT 1");
    query.first();

    InventoryItemData inventoryItemData;
    inventoryItemData[itemImage] = query.value(0).toString();
    inventoryItemData[itemSound] = query.value(1).toString();
    return inventoryItemData;
}

void Database::setInventoryItem(const InventoryItemData &inventoryItemData)
{

    QSqlQuery query = QSqlQuery(m_database);
    query.exec("DELETE FROM InventoryItem");
    query.prepare("INSERT OR IGNORE INTO InventoryItem (name, sound) VALUES (:name, :sound)");
    query.bindValue(":name", inventoryItemData[itemImage]);
    query.bindValue(":sound", inventoryItemData[itemSound]);
    query.exec();
    emit inventoryItemChanged(inventoryItemData);
}

InventoryTableData Database::inventoryTable() const
{
    InventoryCellData cell;
    InventoryTableData data;

    QSqlQuery query = QSqlQuery(m_database);

    query.exec("SELECT name, sound FROM InventoryItem LIMIT 1");
    query.first();
    QString imageName = query.value(0).toString();

    query.exec("SELECT row, column, count FROM InventoryTable");

    while (query.next()) {
        cell[cellRow] = query.value(0).toInt();
        cell[cellColumn] = query.value(1).toInt();
        cell[cellCount] = query.value(2).toInt();
        cell[cellImage] = imageName;
        data.push_back(cell);
    }

    return data;
}

void Database::updateCellData(const InventoryCellData& cellData)
{

    int row = cellData[cellRow].toInt();
    int column = cellData[cellColumn].toInt();
    int count = cellData[cellCount].toInt();
    QSqlQuery query = QSqlQuery(m_database);

    if (count <= 0) {
        query.prepare("DELETE FROM InventoryTable WHERE row = :row AND column = :column");
    } else {
        query.prepare("INSERT OR REPLACE INTO InventoryTable (row, column, count) VALUES (:row, :column, :count)");
        query.bindValue(":count", count);
    }
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.exec();
}

void Database::clearInventoryTable()
{
    QSqlQuery query = QSqlQuery(m_database);
    query.exec("DELETE FROM InventoryTable");
    emit inventoryTableCleared();
}
