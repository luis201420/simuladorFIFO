#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>

#include <algorithm>
#include <vector>
#include <utility>

#include "startbutton.h"

using namespace std;

class MainWindow:public QWidget
{
private:

    int   height        ;
    int   width         ;
    int   processNumber ;
    QTextEdit    * text   ;
    StartButton  * button ;
    QWidget      * counter;
    QTableWidget * table  ;
    vector< pair<QString,pair<int,int>> > processes;

public:
    MainWindow(QRect screen);

    inline int  getHeight()     {return this->height;}
    inline int  getWidth()      {return this->width; }
    inline void setHeight(int n){this->height=n;}
    inline void setWidth(int n) {this->width=n; }

    void iniciar() ;
    void llenar()  ;
    void procesar();
};

#endif // MAINWINDOW_H
