#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>

#include "info.h"
#include "inventoryitem.h"
#include "inventorytable.h"
#include "mainmenu.h"

namespace Ui {
class MainWindow;
}

/* VIEW */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    /*Если ячейка изменилась*/
    void cellDataChanged(const InventoryCellData& cellData);
    /*Новая игра*/
    void newGame();

public slots:
    /* Сброс данных */
    void reset();
    /* Виджет предмета */
    void setInventoryItem(const InventoryItemData &inventoryItemData);
    /* Виджет таблицы */
    void setInventoryTable(const InventoryTableData &inventoryTableData);
    /* Ячейка таблицы */
    void setCellData(const InventoryCellData &inventoryCellData);
    /* Включить таблицу */
    void enableTable();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void on_pushButtonMenu_clicked();

private:
    Ui::MainWindow* ui;
    MainMenu* m_mainMenu;
    InventoryTable* m_inventoryTable;
    InventoryItem* m_inventoryItem;

    QStateMachine m_stateMachine;
};

#endif // MAINWINDOW_H
