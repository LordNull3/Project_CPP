#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "login.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->User->setPlaceholderText("Entrez votre Username");
    ui->Name->setPlaceholderText("Entrez votre nom");
    ui->Prenom->setPlaceholderText("Entrez votre prenom");
    ui->MDP->setPlaceholderText("Entrez votre Mot de passe");
    ui->Mail->setPlaceholderText("Entrez votre E-mail");
    ui->USS->setPlaceholderText("Entrez votre username");
    ui->MDP_3->setPlaceholderText("Entrez votre MDP");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bouton1_4_clicked()
{

    QString NOM = ui->Name->text();
    QString PRENOM = ui->Prenom->text();
    QString MAIL = ui->Mail->text();
    QString MDP = ui->MDP->text();
    QString USERNAME = ui->User->text();
    QString Sexe=ui->comboBox->currentText();
    Loginn L(NOM,PRENOM,MAIL,MDP,USERNAME,Sexe);
    bool test=L.ajouter();
    if(test){
        QMessageBox::information(this, "Inserted","Data Inserted Succesfully");
    }
    else{
        QMessageBox::information(this, "Not Inserted","Data Is Not Inserted");
    }
}


void MainWindow::on_bouton1_5_clicked()
{

    QSqlQuery qry;
     QString  USERNAME=ui->USS->text();
     QString  MDP=ui->MDP_3->text();

        if(qry.exec("SELECT id_emp, MDP FROM EMPLOYEE WHERE id_emp=\'"+ USERNAME +"\' AND MDP=\'" + MDP + "\'"))
        {
            if(qry.next())
            {
                QMessageBox::information(this, "Success","Log In Success");
                qry.exec();
                MYDialog dialog;
              //  dialog.setModal(true);
                this->close();
                dialog.show();
                dialog.exec();

                       }else{


                QMessageBox::information(this, "Failed","Log In Failed");

                        }

            }
        }
