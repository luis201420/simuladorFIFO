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
    this->resultCounter->setGeometry((posTextX+(0.4*this->width)+100),(posTextY+textHeight+30),(0.4*this->width),(0.35*this->height));
    this->resultCounter->setStyleSheet("background-color:#FFFFFF;");

    /** TABLE **/
    this->resultTable = new QTableWidget(resultCounter);
    this->resultTable->setColumnCount(3);
    this->resultTable->resize(resultCounter->width(),resultCounter->height());
    QStringList tableHeader2;
    tableHeader2<<"ID Proceso"<<"Tiempo Final"<<"Tiempo Retorno";
    this->resultTable->setHorizontalHeaderLabels(tableHeader2);
    this->resultTable->horizontalHeader()->setStretchLastSection(true);

    /** GRAFICA **/
    this->grafic = new QLabel(this);
    this->grafic->setGeometry(0,0,(0.90*this->width),(0.4*this->height));
    this->grafic->setStyleSheet("background-color:#FFFFFF;");

    this->grafic_area = new QScrollArea(this);
    this->grafic_area->setGeometry((0.05*this->width),(posTextY+textHeight+85+this->counter->height()),(0.90*this->width),(0.4*this->height));
    this->grafic_area->setWidget(this->grafic);
    this->grafic_area->setWidgetResizable(false);

    this->grafic_area->show();

    this->line = new QLabel(this->grafic);

    /** MOSTRADOR DE RESULTADOS FINALES DEL ALGORITMO **/
    this->finalresults = new QLabel(this);
    this->finalresults->setGeometry((posTextX+(0.4*this->width)+100),(posTextY-10),(0.4*this->width),50);
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
             this->graficar();
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
    for(int i=1;i<=(this->processNumber);i++){

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
    int t_espera,t_entrega,t_nuevo;

    float n_espera=0,n_entrega=0;

    for(unsigned i=0;i<this->processes.size();i++){
        if(((t_actual)-((this->processes[i]).second).first)<=0){
            t_espera=0;
            t_actual+=abs(((t_actual)-((this->processes[i]).second).first));
            t_nuevo = this->processes[i].second.second+t_actual+t_espera;
        }
        else{
            t_espera=((t_actual)-((this->processes[i]).second).first);
            t_nuevo = this->processes[i].second.second+t_espera;
        }
        t_entrega=t_actual+(((this->processes[i]).second).second);

        this->results.push_back(make_pair(((this->processes[i]).first),make_pair(t_nuevo,t_entrega)));

        n_espera+=t_espera;
        n_entrega+=t_entrega;

        t_actual+=((this->processes[i]).second).second;
    }
    n_espera/=this->processNumber;
    n_entrega/=this->processNumber;

    this->mostrar_resultados_finales(n_espera,n_entrega);

    this->mostrar();
}

#include <QThread>

void MainWindow::mostrar()
{
    this->resultTable->setRowCount(this->processNumber);

    for(unsigned int i=0;i<(this->results.size());i++){

        QString id =(this->results[i]).first;
        int t1=((this->results[i]).second).second;
        int t2=((this->results[i]).second).first;

        this->resultTable->setItem(i, 0, new QTableWidgetItem(id));
        this->resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(t1)));
        this->resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(t2)));
    }
}

void MainWindow::graficar()
{
    this->limpiar();

    int proporcion = 15;

    if(this->processNumber>=12){
        this->grafic->setGeometry(0,0,((((this->results[this->results.size()-1]).second).second)*proporcion)+20,(0.4*this->height));
    }
    else{
        this->grafic->setGeometry(0,0,(this->grafic_area->width()),(this->grafic_area->height()));
    }

    this->line->setGeometry(10,(this->grafic->height()/2),((((this->results[this->results.size()-1]).second).second)*proporcion)+15,2);
    this->line->setStyleSheet("background-color:#000000;");
    this->line->show();

    int x = 15;
    int tam;
    int r,g,b;
    for(unsigned i = 0 ; i < this->results.size();i++){
        r=(rand() % 155) +100;
        g=(rand() % 155) +100;
        b=(rand() % 155) +100;

        if(i==0){
            QLabel * time = new QLabel(this->grafic);
            time->setGeometry((x-7),(this->grafic->height()/2)+2,15,10);
            time->setStyleSheet("background-color:#FFFFFF");
            time->setText(QString::number(this->processes[i].second.first));
            time->setAlignment(Qt::AlignCenter);
            time->show();
            this->times.push_back(time);
        }

        tam = this->processes[i].second.second;

        QLabel * bloque = new QLabel(this->grafic);
        bloque->setGeometry(x,(this->grafic->height()/2)-50,tam*proporcion,50);
        bloque->setStyleSheet("background-color:rgb("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+");");
        bloque->setText(this->results[i].first);
        bloque->setAlignment(Qt::AlignCenter);
        bloque->show();
        this->processes_grafic.push_back(bloque);

        x+=tam*proporcion;

        QLabel * time = new QLabel(this->grafic);
        time->setGeometry((x-7),(this->grafic->height()/2)+2,15,10);
        time->setStyleSheet("background-color:#FFFFFF");
        time->setText(QString::number(this->results[i].second.second));
        time->setAlignment(Qt::AlignCenter);
        time->show();
        this->times.push_back(time);

    }
    this->grafic_area->setWidget(this->grafic);
    this->grafic_area->setWidgetResizable(false);

    this->grafic_area->show();
}

void MainWindow::limpiar()
{
    this->line->setStyleSheet("background-color:#FFFFFF");
    this->line->show();

    for(unsigned i =0 ;i < this->processes_grafic.size();i++){
        this->processes_grafic[i]->setStyleSheet("background-color:#FFFFFF");
        this->processes_grafic[i]->setText("");
        this->processes_grafic[i]->show();
    }
    for(unsigned i=0;i<this->times.size();i++){
        this->times[i]->setText("");
        this->times[i]->show();
    }
    this->processes_grafic.clear();
    this->times.clear();
}

void MainWindow::mostrar_resultados_finales(float a,float b)
{
    this->finalresults->setText("Tiempo Retorno Normalizado: \t"+QString::number(a)+"\nTiempo Final Normalizado: \t"+QString::number(b));
}
