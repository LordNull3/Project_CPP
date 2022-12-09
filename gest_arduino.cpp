#include "gest_arduino.h"
#include "ui_gest_arduino.h"
#include "arduino.h"

gest_arduino::gest_arduino(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_arduino)
{
    ui->setupUi(this);
    ui->comboBox->setModel(bi.afficher_2());
    int ret =a.connect_arduino();
            switch(ret){
            case(0): qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
                break ;
            case(1): qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
                break ;
            case(-1): qDebug()<<"arduino is not avaialable";
            }
           QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

gest_arduino::~gest_arduino()
{
    delete ui;
}

void gest_arduino::on_pushButton_clicked()

{
    QSqlQuery qry,q1;
    QString num_vol=ui->comboBox->currentText();

    qry.prepare("select * from vol ");
    if(qry.exec())
       {
           while(qry.next())
           {
               //Remplir tous les champs par les données concernées

   if(qry.value(0).toString()==num_vol)
   {
               ui->lineEdit->setText(qry.value(5).toString());


   }//fin if
   }//fin while
   }//fin if qry
      int capacite_vol=ui->lineEdit->text().toInt();

      QByteArray az;
      az.setNum(capacite_vol);

      a.write_to_arduino(az);


}

void gest_arduino::on_pushButton_2_clicked()
{
    QSqlQuery qry,q1;
    QString num_vol=ui->comboBox->currentText();
    q1.prepare("Select * from billet where num_vol = :nom ");
    q1.bindValue(":nom",num_vol);
    q1.exec();

    int t=0;
    while (q1.next())
        t++;
 qDebug() << "pourcentage don =" << t;

ui->label_3->setNum(t);
 QByteArray e;
 e.setNum(t);

 a.write_to_arduino(e);

}


void gest_arduino::update_label(){


 e=a.read_from_arduino();
int z=e.toInt();
 //ui->label_2->setNum(z);
ui->label_2->setText(e);


}
