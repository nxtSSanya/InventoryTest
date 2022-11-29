#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

#include "inventoryitem.h"

InventoryItem::InventoryItem(bool changed, QWidget *parent, Qt::WindowFlags f)
    : InventoryItem(tr(""), changed, parent, f)
{

}

InventoryItem::InventoryItem(const QString &text, bool changed, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    if (changed) {
        resizeWidget();
    }
}

void InventoryItem::resizeWidget()
{
    setMaximumWidth(200);

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);
}

bool InventoryItem::hasHeightForWidth() const
{
    return true;
}

int InventoryItem::heightForWidth(int w) const
{
    return w;
}

InventoryItem::~InventoryItem()
{

}

void InventoryItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << *pixmap();

        QMimeData* mimeData = new QMimeData();
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap()->scaled(size()));
        drag->setHotSpot(event->pos());

        drag->exec();
    }
}
