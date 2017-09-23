#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRect rec = QApplication::desktop()->screenGeometry();

    MainWindow * nuevo=new MainWindow(rec);

    nuevo->show();

    return a.exec();
}
