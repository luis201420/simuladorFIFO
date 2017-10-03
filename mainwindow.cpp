#include "mainwindow.h"
#include "myutilities.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

MainWindow::MainWindow(QRect screen)
{
    srand (time(NULL));

    this->height = screen.height();
    this->width = screen.width();
    this->processNumber = 0;

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

    /***************************************************/
    /**                   TEXTEDIT                    **/
    this->text = new QTextEdit();
    this->text->setParent(this);
    this->text->setGeometry((posTextX+textWidth),(posTextY-5),60,30);
    this->text->setStyleSheet("background-color:#FFFFFF;");

    /*****************************************************/
    /**                    BUTTON                       **/

    this->button = new StartButton(this,((posTextX+textWidth)+70),((posTextY-5)));

    /*******************************************************/
    /**               MOSTRADOR DE DATOS                  **/

    this->counter = new QWidget(this);
    this->counter->setGeometry(posTextX,(posTextY+textHeight+30),(0.4*this->width),(0.35*this->height));
    this->counter->setStyleSheet("background-color:#FFFFFF;");

    /** TABLE **/
    this->counterTable= new QTableWidget(counter);
    this->counterTable->setColumnCount(3);
    this->counterTable->resize(counter->width(),counter->height());
    QStringList tableHeader1;
    tableHeader1<<"ID Proceso"<<"Tiempo llegada"<<"Duracion";
    this->counterTable->setHorizontalHeaderLabels(tableHeader1);
    this->counterTable->horizontalHeader()->setStretchLastSection(true);


    /*********************************************************/

    /** PANEL DE RESULTADOS **/

    this->resultCounter = new QWidget(this);
    this->resultCounter->setGeometry((posTextX+(0.4*this->width)+100),posTextY,(0.4*this->width),(0.35*this->height));
    this->resultCounter->setStyleSheet("background-color:#FFFFFF;");

    /** TABLE **/
    this->resultTable = new QTableWidget(resultCounter);
    this->resultTable->setColumnCount(3);
    this->resultTable->resize(resultCounter->width(),resultCounter->height());
    QStringList tableHeader2;
    tableHeader2<<"ID Proceso"<<"Tiempo espera"<<"Tiempo entrega";
    this->resultTable->setHorizontalHeaderLabels(tableHeader2);
    this->resultTable->horizontalHeader()->setStretchLastSection(true);

    /** GRAFICA **/
}

void MainWindow::iniciar()
{
    QString cont=(this->text)->toPlainText();
    QMessageBox msgBox;
    if(cont.isEmpty()){
        msgBox.setText("Asegurese de haber puesto un valor.");
        msgBox.exec();
    }
    else if(isNumber(cont)){
         if(cont.toInt()>100 || cont.toInt()==0){
             msgBox.setText("Asegurese de haber puesto un valor entre [1-100].");
             msgBox.exec();
         }
         else{
             this->processNumber=cont.toInt();
             this->llenar();
             this->procesar();
         }
    }
    else{
        msgBox.setText("El valor puesto es incorrecto.");
        msgBox.exec();
    }
}

void MainWindow::llenar()
{
    this->counterTable->setRowCount(this->processNumber);
    this->processes.clear();
    for(unsigned int i=1;i<=(this->processNumber);i++){

        QString id ="P"+QString::number(i);
        int t1=rand() % int(ceil((this->processNumber*2.0)/3.0)+1);
        int t2=(rand() % 10) +1;

        this->counterTable->setItem((i-1), 0, new QTableWidgetItem(id));
        this->counterTable->setItem((i-1), 1, new QTableWidgetItem(QString::number(t1)));
        this->counterTable->setItem((i-1), 2, new QTableWidgetItem(QString::number(t2)));

        this->processes.push_back(make_pair(id,make_pair(t1,t2)));
    }
}

void MainWindow::procesar()
{
    sort(this->processes.begin(),this->processes.end(),myorder);
    /** VECTOR ORDENADO PARA PROCESAR SEGUN EL TIEMPO DE LLEGADA DE CADA PROCESO **/

    this->results.clear();

    int t_actual=0;
    int t_espera,t_entrega;

    for(int i=0;i<this->processes.size();i++){
        if(((t_actual)-((this->processes[i]).second).first)<=0){
            t_espera=0;
            t_actual+=abs(((t_actual)-((this->processes[i]).second).first));
        }
        else{
            t_espera=((t_actual)-((this->processes[i]).second).first);
        }
        t_entrega=t_actual+(((this->processes[i]).second).second);

        this->results.push_back(make_pair(((this->processes[i]).first),make_pair(t_espera,t_entrega)));

        t_actual+=((this->processes[i]).second).second;
    }

    this->mostrar();
}

void MainWindow::mostrar()
{
    this->resultTable->setRowCount(this->processNumber);

    for(unsigned int i=0;i<(this->results.size());i++){

        QString id =(this->results[i]).first;
        int t1=((this->results[i]).second).first;
        int t2=((this->results[i]).second).second;

        this->resultTable->setItem(i, 0, new QTableWidgetItem(id));
        this->resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(t1)));
        this->resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(t2)));
    }
}
