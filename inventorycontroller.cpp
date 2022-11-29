#include <QApplication>
#include <unordered_map>

#include "inventorycontroller.h"
#include "database.h"

const QString imgName = ":/images/enchanted.jpg";
const QString soundName = ":/sounds/mango.wav";

    /*
    * Contains all pairs {image, sound} for items
    */
std::unordered_map<QString, QString> fileName;

InventoryController::InventoryController(MainWindow* view, QObject *parent)
    : QObject(parent), m_view(view)
{

    m_model = new Database(this);

    if (m_view != Q_NULLPTR) {
        QObject::connect(m_model, &IItemModel::inventoryItemChanged, m_view, &MainWindow::setInventoryItem);
        QObject::connect(m_model, &IItemModel::inventoryTableCleared, m_view, &MainWindow::reset);
        QObject::connect(m_model, &IItemModel::inventoryTableChanged, m_view, &MainWindow::setInventoryTable);
        QObject::connect(m_model, &IItemModel::inventoryCellChanged, m_view, &MainWindow::setCellData);
        QObject::connect(m_view, &MainWindow::cellDataChanged, m_model, &IItemModel::updateCellData);
        QObject::connect(m_view, &MainWindow::newGame, m_model, &IItemModel::clearInventoryTable);
    }


        InventoryItemData inventoryItemData;
        inventoryItemData[itemImage] = imgName;
        inventoryItemData[itemSound] = soundName;
        m_model->setInventoryItem(inventoryItemData);


    if (m_view != Q_NULLPTR) {
        m_view->setWindowTitle(m_windowTitle);
        m_view->setInventoryTable(m_model->inventoryTable());
        m_view->show();
    }
}

InventoryController::~InventoryController()
{

}
