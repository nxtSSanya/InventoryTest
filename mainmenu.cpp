#include <QLayout>

#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();
    QColor color = parent->palette().color(QPalette::AlternateBase);

    pal.setColor(QPalette::Window, color);
    setPalette(pal);
    setAutoFillBackground(true);

    buttonStart = new QPushButton(tr("Start"), this);
    buttonExit = new QPushButton(tr("Exit"), this);

    const int _width = 400;
    buttonStart->setMaximumWidth(_width);
    buttonExit->setMaximumWidth(_width);

    connect(buttonStart, SIGNAL(clicked(bool)), this, SIGNAL(clickedStart()));
    connect(buttonExit, SIGNAL(clicked(bool)), this, SIGNAL(clickedExit()));

    setLayout(new QHBoxLayout(this));
    layout()->addWidget(buttonStart);
    layout()->addWidget(buttonExit);
}

MainMenu::~MainMenu()
{

}
