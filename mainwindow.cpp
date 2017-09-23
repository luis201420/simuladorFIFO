#include "mainwindow.h"

MainWindow::MainWindow(QRect screen)
{
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
    this->table= new QTableWidget(counter);
    this->table->setRowCount(10);
    this->table->setColumnCount(3);
    this->table->resize(counter->width(),counter->height());
    QStringList tableHeader;
    tableHeader<<"ID Proceso"<<"Tiempo llegada"<<"Duracion";
    this->table->setHorizontalHeaderLabels(tableHeader);
    this->table->horizontalHeader()->setStretchLastSection(true);


    /*********************************************************/

    /** PANEL DE RESULTADOS **/
    /** GRAFICA **/
}

bool isNumber(QString a){
    for(int i=0;i<a.size();i++){
        if(a[i]<'0' || a[i]>'9')return false;
    }
    return true;
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
         if(cont.toInt()>100){
             msgBox.setText("Asegurese de haber puesto un valor entre [1-100].");
             msgBox.exec();
         }
         else{
             this->processNumber=cont.toInt();
         }
    }
    else{
        msgBox.setText("El valor puesto es incorrecto.");
        msgBox.exec();
    }
}
