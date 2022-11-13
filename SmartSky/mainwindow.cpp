#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "vol.h"
#include "QIntValidator"
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CvAline->setValidator(new QIntValidator(100,500, this));
    ui->DuAline->setValidator(new QIntValidator(1,72, this));
    ui->ShowV->setModel(V.afficher());
    ui->LD_Avion->setModel(V.Combo_req());
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
    int id_avion=ui->LD_Avion->currentText().toInt();

    Vol V(id_vol,pdd,pda,capacite_vol,duree,id_avion);

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
    //Vol V1 ; V1.setid_vol(ui->Del_line->text());

    QModelIndex index = ui->ShowV->currentIndex();
      QString id_vol = index.data(Qt::DisplayRole).toString();
    bool test=V.supprimer(id_vol);
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

void MainWindow::on_tri_vol_button_clicked()
{
    ui->ShowV->setModel(V.tri_vol());
}

void MainWindow::on_Modifer_button_clicked()
{
    QString id_vol=ui->IdAline->text();
    int id_avion=ui->LD_Avion->currentText().toInt();
    QString pdd=ui->PddAline->text();
    QString pda=ui->PdaAline->text();
    int capacite_vol=ui->CvAline->text().toInt();
    int duree=ui->DuAline->text().toInt();


     Vol V(id_vol,pdd,pda,capacite_vol,duree,id_avion);
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

                 ui->IdAline->setText("");
                 ui->LD_Avion->currentText();
                 ui->PddAline->setText("");
                 ui->PdaAline->setText("");
                 ui->CvAline->setText("");
                 ui->DuAline->setText("");

        }
        else
        {
           QMessageBox::critical(nullptr, QObject::tr("Modifier un Vol"),

                                 QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
        }
    }
      ui->ShowV->setModel(V.afficher());
}

void MainWindow::on_Afficher_clicked()
{
    QModelIndex index = ui->ShowV->currentIndex();
         QString id_vol = index.data(Qt::DisplayRole).toString();
         ui->IdAline->setText(id_vol);
         QString id_avion = ui->ShowV->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
         ui->LD_Avion->currentText();
          QString pdd = ui->ShowV->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
          ui->PddAline->setText(pdd);
           QString pda = ui->ShowV->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
             ui->PdaAline->setText(pda);
            QString Capacite_vol = ui->ShowV->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
             ui->CvAline->setText(Capacite_vol);
             QString Duree = ui->ShowV->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
             ui->DuAline->setText(Duree);


}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->ShowV->setModel(V.rechercher(arg1));
}

void MainWindow::on_Pdf_Ex_clicked()
{
    Vol V;

                 QString text=V.export_pdf();
                 ui->PdfLine->setText(text);

                 QPrinter printer ;
                 printer.setPrinterName("imprim");
                 QPrintDialog dialog (&printer,this);
                 if(dialog.exec()==QDialog::Rejected) return ;
                 ui->PdfLine->print(&printer);
}
