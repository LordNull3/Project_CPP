#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billet.h"
#include "connection.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->tableView->setModel(bi.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QSqlQuery query;
    QString id_billet=ui->id->text();
    QString nom=ui->nom->text();
    QString num_vol=ui->vol->text();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();
    QString classement=ui->classs->text();
   Billet b (id_billet,classement,emplacement,num_vol,num_voyageur,nom);
   bool test= b.ajouter();
       if(test)
       {
           ui->tableView->setModel(bi.afficher());
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("ajouter successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else{
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("ajouter failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}
}






void MainWindow::on_supp_clicked()
{
  // bi.setid_billet(ui->linesupp->text());
   // QString id=ui->linesupp->text();
    QModelIndex index = ui->tableView->currentIndex();
      QString id_billet = index.data(Qt::DisplayRole).toString();
     // bi.setid_billet(id_billet);
    bool test =bi.supprimer(id_billet);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel(bi.afficher());
}
    else{
         ui->tableView->setModel(bi.afficher());
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_modify_clicked()
{
    QString id_billet=ui->id->text();
    QString nom=ui->nom->text();
    QString num_vol=ui->vol->text();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();
    QString classement=ui->classs->text();
   Billet b (id_billet,classement,emplacement,num_vol,num_voyageur,nom);
   if(b.modifier(id_billet))
   {
            QMessageBox::information(nullptr, QObject::tr("Modifier un Vol"),
                        QObject::tr("Vol modifié.\n"), QMessageBox::Cancel);
            ui->tableView->setModel(bi.afficher());



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("Modifier un Vol"),

                            QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
      ui->id->setText("");
      ui->nom->setText("");
      ui->vol->setText("");
      ui->voy->setText("");
      ui->emp->setText("");
      ui->classs->setText("");
   }
}
