#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPushButton>
#include <QWidget>

#include "info.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = Q_NULLPTR);
    virtual ~MainMenu();

signals:
    void clickedStart();
    void clickedExit();

public slots:

public:
    QPushButton* buttonStart;
    QPushButton* buttonExit;

};

#endif // MAINMENU_H
