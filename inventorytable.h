#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H

#include <QTableWidget>

#include "info.h"

class InventoryTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit InventoryTable(bool changed = false, QWidget *parent = Q_NULLPTR);
    InventoryTable(int rows, int columns, bool changed = false, QWidget *parent = Q_NULLPTR);

    /* Настройка отображения и работы виджета*/
    void resizeWidget();
    virtual bool hasHeightForWidth() const;
    virtual int squareItem(int width) const;
    virtual ~InventoryTable();

    /* Установка звука при уменьшении предмета */
    void setSoundName(const QString &soundName);

    /* Добавление в инвентарь */
    QTableWidgetItem* addNewItem(const InventoryCellData& cellData);
    /* Тоже добавление, только явно заданный конструктор */
    QTableWidgetItem* addNewItem(int row, int column, int count = 0, const QIcon &icon = QIcon(), const QString& sound = "");

signals:
    /* Изменение предмета в инвентаре */
    void cellDataChanged(const InventoryCellData& cellData);

protected:
    /* Для записи пользовательских данных в ячейку инвентаря */
    enum UserRole {
        UserDataCount = Qt::UserRole
    };

    /* Тип DragDrop события*/
    QString mimeType() const;
    /*DragDrop events*/
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

    QString m_soundName;
};

#endif // INVENTORYTABLE_H
