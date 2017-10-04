#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollArea>

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

    QWidget      * counter      ;
    QWidget      * resultCounter;
    QTableWidget * counterTable ;
    QTableWidget * resultTable  ;
    QLabel       * grafic       ;
    QLabel       * line         ;
    QScrollArea  * grafic_area  ;
    vector<QLabel *> processes_grafic;
    vector< pair<QString,pair<int,int>> > processes;
    vector< pair<QString,pair<int,int>> > results  ;

public:
    MainWindow(QRect screen);

    inline int  getHeight()     {return this->height;}
    inline int  getWidth()      {return this->width; }
    inline void setHeight(int n){this->height=n;}
    inline void setWidth(int n) {this->width=n; }

    void iniciar() ;
    void llenar()  ;
    void procesar();
    void mostrar() ;
    void graficar();
    void limpiar() ;
};

#endif // MAINWINDOW_H
