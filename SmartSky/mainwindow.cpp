#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "vol.h"
#include "QIntValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CvAline->setValidator(new QIntValidator(100,500, this));
    ui->DuAline->setValidator(new QIntValidator(1,72, this));
    ui->ShowV->setModel(V.afficher());
}







MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AjouterButton_clicked()
{
    QString id_vol=ui->IdAline->text();
    QString pdd=ui->PddAline->text();
    QString pda=ui->PdaAline->text();
    int capacite_vol=ui->CvAline->text().toInt();
    int duree=ui->DuAline->text().toInt();

    Vol V(id_vol,pdd,pda,capacite_vol,duree);

    bool test = V.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("ajout effectué.\n",
                                             "click Cancel to exist."), QMessageBox::Cancel);
    }else{
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                                 QObject::tr("ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
         ui->ShowV->setModel(V.afficher());

}

void MainWindow::on_Del_button_clicked()
{
    Vol V1 ; V1.setid_vol(ui->Del_line->text());
    bool test=V1.supprimer(V1.getid_vol());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("delete effectué.\n",
                                             "click Cancel to exist."), QMessageBox::Cancel);
    }else{
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                                 QObject::tr("delete non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
     ui->ShowV->setModel(V.afficher());

}



void MainWindow::on_Modifier_clicked()
{
           QString id_vol=ui->IdMline->text();
           QString pdd=ui->PdMline->text();
           QString pda=ui->PaMline->text();
           int capacite_vol=ui->CMline->text().toInt();
           int duree=ui->DMline->text().toInt();

            Vol V(id_vol,pdd,pda,capacite_vol,duree);
           if((id_vol=="")&&(pdd=="")&&(pda=="")&&(capacite_vol==0)&&(duree==0))
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
               }
             else if(id_vol == "")
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir l'identifiant"), QMessageBox::Ok);

              }
              else if(pdd =="")
                 {
                     QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Veuillez remplir le pays de depart"), QMessageBox::Ok);

                 }
              else if(pda =="")
                 {
                     QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Veuillez remplir le pays d'arriveé"), QMessageBox::Ok);

                 }
              else if(capacite_vol ==0)
                 {
                     QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Veuillez remplir la capaciter de vol"), QMessageBox::Ok);

                 }

              else if(duree ==0)
                 {
                     QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("Veuillez remplir la duree de vol"), QMessageBox::Ok);

                 }

           else {

               if(V.modifier(id_vol))
               {
                        QMessageBox::information(nullptr, QObject::tr("Modifier un Vol"),
                                    QObject::tr("Vol modifié.\n"), QMessageBox::Cancel);

                        ui->IdMline->setText("");
                        ui->PdMline->setText("");
                        ui->PaMline->setText("");
                        ui->CMline->setText("");
                        ui->DMline->setText("");

               }
               else
               {
                  QMessageBox::critical(nullptr, QObject::tr("Modifier un Vol"),

                                        QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
               }
           }
             ui->ShowV->setModel(V.afficher());
}


