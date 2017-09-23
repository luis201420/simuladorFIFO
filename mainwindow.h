#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include "startbutton.h"

class MainWindow:public QWidget
{
private:
    int height;
    int width;
    QTextEdit * text;
    StartButton * button;
public:
    MainWindow(QRect screen);

    inline int getHeight(){return this->height;}
    inline int getWidth(){return this->width;}
    inline void setHeight(int n){this->height=n;}
    inline void setWidth(int n){this->width=n;}

    void iniciar();
};

#endif // MAINWINDOW_H
