#ifndef IITEMMODEL_H
#define IITEMMODEL_H

#include <QObject>

#include <info.h>

/*Интерфейс для модели данных*/
class IItemModel : public QObject
{
    Q_OBJECT

    /* Обмен данными между моделью и представлением */
    Q_PROPERTY(InventoryItemData inventoryItem READ inventoryItem WRITE setInventoryItem NOTIFY inventoryItemChanged)

public:
    explicit IItemModel(QObject *parent = 0);
    virtual ~IItemModel();

    /* Получение данных о Предмете */
    virtual InventoryItemData inventoryItem() const = 0;

    /* Запись в БД информации о Предмете */
    virtual void setInventoryItem(const InventoryItemData &inventoryItemData) = 0;

    /* Получение данных об инвентаре */
    virtual InventoryTableData inventoryTable() const = 0;

signals:

    /*Изменение предмета*/
    void inventoryItemChanged(const InventoryItemData &inventoryItemData);
    /*Изменение ячейки*/
    void inventoryCellChanged(const InventoryCellData &inventoryCellData);
    /**
     * @brief Событие готовности данных для инвентаря
     */
    void inventoryTableChanged(const InventoryTableData &inventoryTableData);
    /*Очистка инвентаря*/
    void inventoryTableCleared();

public slots:

    /* Запись в БД состояния текущей ячейки инвентаря*/
    virtual void updateCellData(const InventoryCellData& cellData) = 0;

    /*Очистка данных в инвентаре*/
    virtual void clearInventoryTable() = 0;

};

#endif // IITEMMODEL_H
