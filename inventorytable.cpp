#include <QDrag>
#include <QHeaderView>
#include <QMimeData>
#include <QMouseEvent>
#include <QSound>
#include <memory>

#include "inventorytable.h"

InventoryTable::InventoryTable(bool changed, QWidget *parent)
    : InventoryTable(0, 0, changed, parent)
{

}

InventoryTable::InventoryTable(int rows, int columns, bool changed, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    if (changed) {
        resizeWidget();
    }
}

void InventoryTable::resizeWidget()
{
    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setMaximumWidth(600);
    setFrameShape(QFrame::NoFrame);

    setSelectionMode(QAbstractItemView::SingleSelection);

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setIconSize(QSize(100, 100));
}

bool InventoryTable::hasHeightForWidth() const
{
    return true;
}

int InventoryTable::squareItem(int width) const
{
    return width;
}

InventoryTable::~InventoryTable()
{

}

void InventoryTable::setSoundName(const QString &soundName)
{
    m_soundName = soundName;
}

QTableWidgetItem* InventoryTable::addNewItem(const InventoryCellData& cellData)
{
    return addNewItem(cellData[cellRow].toInt(),
                      cellData[cellColumn].toInt(),
                      cellData[cellCount].toInt(),
                      QPixmap(cellData[cellImage].toString()),
                      cellData[cellSound].toString());
}

QTableWidgetItem* InventoryTable::addNewItem(int row, int column, int count, const QIcon &icon, const QString& sound)
{
    QTableWidgetItem* item = takeItem(row, column);
    if (item != Q_NULLPTR && count <= 0) {
        delete item;
    } else {
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        item->setData(UserDataCount, QVariant(count));
        item->setText(QString::number(count));
        //item->setTextColor(QColor::Rgb(255, 0, 0));
        item->setIcon(icon);
        setItem(row, column, item);
    }
    QSound::play(sound);
    return item;
}

QString InventoryTable::mimeType() const
{
    return tr("application/x-dnditemdata");
}

void InventoryTable::mouseReleaseEvent(QMouseEvent *event)
{
    QTableWidgetItem* item = itemAt(event->pos());

    if (event->button() == Qt::RightButton && item != Q_NULLPTR) {
        int count = item->data(UserDataCount).toInt() - 1;
        item->setData(UserDataCount, count);
        item->setText(QString::number(count));

        QSound::play(m_soundName);

        InventoryCellData cellData;
        cellData[cellRow] = item->row();
        cellData[cellColumn] = item->column();
        cellData[cellCount] = count;
        cellData[cellImage] = "";
        cellData[cellSound] = m_soundName;
        emit cellDataChanged(cellData);

        if (count <= 0) {
            delete takeItem(item->row(), item->column());
        }

        clearSelection();
        clearFocus();
    }

    QTableWidget::mouseReleaseEvent(event);
}

void InventoryTable::startDrag(Qt::DropActions supportedActions)
{
    QTableWidgetItem *item = currentItem();
    if (item == Q_NULLPTR) {
        return;
    }

    QTableWidget::startDrag(supportedActions);
}

void InventoryTable::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() == this || event->mimeData()->hasFormat(mimeType())) {
        event->accept();
    } else {
        event->ignore();
    }
}

void InventoryTable::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->source() == this || event->mimeData()->hasFormat(mimeType())) {
        event->accept();
    } else {
        event->ignore();
    }
}

void InventoryTable::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        QTableWidgetItem* sourceItem = currentItem();
        QTableWidgetItem* targetItem = itemAt(event->pos());

        if (sourceItem == targetItem) {
            event->ignore();
            return;
        }

        if (targetItem == Q_NULLPTR) {
            targetItem = addNewItem(rowAt(event->pos().y()), columnAt(event->pos().x()));
        }

        int countSource = sourceItem->data(UserDataCount).toInt();
        sourceItem->setData(UserDataCount, 0);
        sourceItem->setText(QString::number(0));

        int countTarget = targetItem->data(UserDataCount).toInt() + countSource;
        targetItem->setData(UserDataCount, countTarget);
        targetItem->setText(QString::number(countTarget));
        targetItem->setIcon(sourceItem->icon());

        InventoryCellData cellData;
        cellData[cellRow] = sourceItem->row();
        cellData[cellColumn] = sourceItem->column();
        cellData[cellCount] = 0;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        cellData[cellRow] = targetItem->row();
        cellData[cellColumn] = targetItem->column();
        cellData[cellCount] = countTarget;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        delete takeItem(sourceItem->row(), sourceItem->column());

        clearSelection();
        clearFocus();

    } else if (event->mimeData()->hasFormat(mimeType())) {
        QTableWidgetItem* targetItem = itemAt(event->pos());

        if (targetItem == Q_NULLPTR) {
            targetItem = addNewItem(rowAt(event->pos().y()), columnAt(event->pos().x()));
        }

        QByteArray itemData = event->mimeData()->data(mimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        dataStream >> pixmap;

        int count = targetItem->data(UserDataCount).toInt() + 1;
        targetItem->setData(UserDataCount, count);
        targetItem->setText(QString::number(count));
        targetItem->setIcon(QIcon(pixmap));

        InventoryCellData cellData;
        cellData[cellRow] = targetItem->row();
        cellData[cellColumn] = targetItem->column();
        cellData[cellCount] = count;
        cellData[cellImage] = "";
        emit cellDataChanged(cellData);

        clearSelection();
        clearFocus();

    } else {
        event->ignore();
    }
}
