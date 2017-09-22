#include "mainwindow.h"

MainWindow::MainWindow(QRect screen)
{
    this->height = screen.height();
    this->width = screen.width();

    this->height = (this->height)*(0.8);
    this->width = (this->width)*(0.75);

    this->resize((this->width),(this->height));
    this->setWindowTitle("Simulador FIFO");
    this->setStyleSheet("background-color:#C8C8C8;");

}
