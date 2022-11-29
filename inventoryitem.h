#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QLabel>

#include "info.h"

/* Предмет инвентаря */
class InventoryItem : public QLabel
{
    Q_OBJECT

public:
    explicit InventoryItem(bool changed = false, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    explicit InventoryItem(const QString &text, bool adopted = false, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /* Настройка отображения и работы виджета*/
    void resizeWidget();
    /* Настройка представления предмета */
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int w) const;
    virtual ~InventoryItem();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // INVENTORYITEM_H
