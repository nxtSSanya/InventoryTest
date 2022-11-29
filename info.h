#ifndef INFO_H
#define INFO_H

#include <QMap>
#include <QString>
#include <QVariant>

/* Информация о предмете для передачи между моделью и представлением image - имя картинки, sound - имя звука */
const QString itemImage = "image";
const QString itemSound = "sound";
using InventoryItemData = QMap<QString, QString> ;

/* Информация о предмете для передачи между моделью и представлением
 *  image - имя картинки
 *  sound - имя звука
 *  row - строка ячейки инвентаря
 *  column - колонка ячейки инвентаря
 *  count - количество предметов в ячейке
 */

const QString cellRow = "row";
const QString cellColumn = "column";
const QString cellCount = "count";
const QString cellImage = "image";
const QString cellSound = "sound";
using InventoryCellData = QMap<QString, QVariant>;

/* Набор данных инвентаря для обмена между моделью и представлением */
using InventoryTableData = QList<InventoryCellData>;

#endif // INFO_H
