#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

class MainWindow;

class StartButton:public QPushButton
{
private:
    MainWindow * parent;
public:
    StartButton(MainWindow * p, int x, int y);
    void mousePressEvent(QMouseEvent * e);
};

#endif // STARTBUTTON_H
