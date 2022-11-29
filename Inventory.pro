#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T10:46:55
#
#-------------------------------------------------

QT       += core gui sql multimedia widgets


TARGET = Inventory
TEMPLATE = app


SOURCES += main.cpp\
    IItemModel.cpp \
    database.cpp \
        mainwindow.cpp \
    mainmenu.cpp \
    inventoryitem.cpp \
    inventorytable.cpp \
    inventorycontroller.cpp

HEADERS  += mainwindow.h \
    IItemModel.h \
    database.h \
    info.h \
    mainmenu.h \
    inventoryitem.h \
    inventorytable.h \
    inventorycontroller.h

FORMS    += mainwindow.ui

RESOURCES += \
    inventory.qrc
