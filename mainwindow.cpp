#include "mainwindow.h"

#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QRect screen)
{
    this->height = screen.height();
    this->width = screen.width();

    this->height = (this->height)*(0.8);
    this->width = (this->width)*(0.75);

    this->resize((this->width),(this->height));
    this->setWindowTitle("Simulador FIFO");
    this->setStyleSheet("background-color:#C8C8C8;");

    this->setMaximumSize(this->width,this->height);
    this->setMinimumSize(this->width,this->height);

    /*************************************************/
    /**                 TEXTO                       **/
    QLabel *label = new QLabel(this);
    QHBoxLayout *layout = new QHBoxLayout();
    label->setText("Numero de Procesos: ");
    layout->addWidget(label);
    int posTextX=(0.04)*(this->height);
    int posTextY=(0.02)*(this->width);
    int textWidth=120;
    int textHeight=15;
    label->setGeometry(posTextX,posTextY,textWidth,textHeight);

    qDebug()<<textWidth;

    /***************************************************/
    /**                   TEXTEDIT                    **/
    QTextEdit *txt = new QTextEdit();
    txt->setParent(this);
    txt->setGeometry((posTextX+textWidth),(posTextY-5),60,30);
    txt->setStyleSheet("background-color:#FFFFFF;");
    txt->show();
}
