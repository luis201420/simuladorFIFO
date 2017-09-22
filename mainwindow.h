#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow:public QWidget
{
private:
    int height;
    int width;
public:
    MainWindow(QRect screen);
    int getHeight(){return this->height;}
    int getWidth(){return this->width;}
    void setHeight(int n){this->height=n;}
    void setWidth(int n){this->width=n;}
};

#endif // MAINWINDOW_H
