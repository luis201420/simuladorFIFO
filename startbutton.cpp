#include "startbutton.h"
#include "mainwindow.h"

StartButton::StartButton(MainWindow *p, int x, int y)
{
    this->parent = p;
    this->setParent(p);
    this->setGeometry(x,y,80,30);
    this->setText("Iniciar");
}

void StartButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        parent->iniciar();
    }
}
