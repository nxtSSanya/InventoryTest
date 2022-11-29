#include <QPropertyAnimation>
#include <QSignalTransition>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/* VIEW */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_inventoryTable = new InventoryTable(3, 3, true, this);
    ui->horizontalLayout->insertWidget(1, m_inventoryTable);
    ui->horizontalLayout->setAlignment(m_inventoryTable, Qt::AlignVCenter);

    ui->pushButtonMenu->setMaximumWidth(200);

    m_inventoryItem = new InventoryItem(true, this);
    ui->verticalLayout->insertWidget(1, m_inventoryItem);

    ui->horizontalLayout->setStretch(1, 6);
    ui->horizontalLayout->setStretch(4, 1);

    const int menuHeight = 50;
    m_mainMenu = new MainMenu(this);
    m_mainMenu->setGeometry(0, 0, width(), menuHeight);

    connect(m_mainMenu, SIGNAL(clickedStart()), this, SIGNAL(newGame()));
    connect(m_mainMenu, SIGNAL(clickedExit()), this, SLOT(close()));
    connect(m_mainMenu, SIGNAL(clickedStart()), this, SLOT(enableTable()));
    connect(m_inventoryTable, &InventoryTable::cellDataChanged, this, &MainWindow::cellDataChanged);

    QState* start = new QState();
    QState* finish = new QState();

    QSignalTransition* t_menu = start->addTransition(m_mainMenu, SIGNAL(clickedStart()), finish);
    QSignalTransition* t_menuBack = finish->addTransition(ui->pushButtonMenu, SIGNAL(clicked()), start);

    QPropertyAnimation* anim = new QPropertyAnimation(m_mainMenu, "geometry", this);
    anim->setDuration(1000);

    t_menu->addAnimation(anim);
    t_menuBack->addAnimation(anim);

    start->assignProperty(m_mainMenu, "geometry", QRect(0, 0, width(), menuHeight));
    finish->assignProperty(m_mainMenu, "geometry", QRect(0, 0, width(), 0));


    m_stateMachine.addState(start);
    m_stateMachine.addState(finish);
    m_stateMachine.setInitialState(start);
    m_stateMachine.start();
    m_inventoryTable->setEnabled(false);
    m_inventoryItem->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    m_inventoryTable->clearContents();
    m_inventoryTable->clearFocus();
}

void MainWindow::enableTable(){
    m_inventoryTable->setEnabled(true);
    m_inventoryItem->setEnabled(true);
    ui->ItemName->setText("Mango");
}

void MainWindow::setInventoryItem(const InventoryItemData &inventoryItemData)
{
    m_inventoryItem->setPixmap(QPixmap(inventoryItemData[itemImage]));
    m_inventoryTable->setSoundName(inventoryItemData[itemSound]);
}

void MainWindow::setInventoryTable(const InventoryTableData &inventoryTableData)
{
    for (auto it = inventoryTableData.begin(); it != inventoryTableData.end(); ++it) {
        m_inventoryTable->addNewItem(*it);
    }
}

void MainWindow::setCellData(const InventoryCellData &inventoryCellData)
{
    m_inventoryTable->addNewItem(inventoryCellData);
}


void MainWindow::resizeEvent(QResizeEvent* )
{
    m_mainMenu->resize(width(), m_mainMenu->height());
}

void MainWindow::on_pushButtonMenu_clicked()
{
    m_inventoryTable->setDisabled(true);
    m_inventoryItem->setDisabled(true);
    reset();
}
