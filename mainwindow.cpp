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
    QString num_vol=ui->comboBox_2->currentText();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();
    QString classement=ui->comboBox->currentText();
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
      QString num_vol=ui->comboBox_2->currentText();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();

    QString classement=ui->comboBox->currentText();
   Billet b (id_billet,classement,emplacement,num_vol,num_voyageur,nom);
   if(b.modifier(id_billet))
   {
            QMessageBox::information(nullptr, QObject::tr("Modifier un billet"),
                        QObject::tr("billet modifié.\n"), QMessageBox::Cancel);
            ui->tableView->setModel(bi.afficher());



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("Modifier "),

                            QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
      ui->id->setText("");
      ui->nom->setText("");
    ui->comboBox_2->setCurrentText("");
      ui->voy->setText("");
      ui->emp->setText("");
     ui->comboBox->setCurrentText("");
   }
}

void MainWindow::on_modifier_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
         QString id_billet = index.data(Qt::DisplayRole).toString();
          QString nom = ui->tableView->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
          ui->nom->setText(nom);
           QString num_vol = ui->tableView->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
             ui->comboBox_2->setCurrentText(num_vol);
            QString classement = ui->tableView->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
             ui->comboBox->setCurrentText(classement);
             QString emplacement = ui->tableView->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
             ui->emp->setText(emplacement);
              QString num_voyageur = ui->tableView->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
              ui->voy->setText(num_voyageur);

               QString id = ui->tableView->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
               ui->id->setText(id);
   }


void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
     ui->tableView->setModel(bi.rechercherNom(arg1));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString trie=ui->comboBox_3->currentText();
    if(trie=="NOM"){
      ui->tableView->setModel(bi.AfficherTri());}
    else if(trie=="ID"){
       ui->tableView->setModel(bi.AfficherTriid());
    }
    else if(trie=="NUM_VOY"){
       ui->tableView->setModel(bi.AfficherTrivoy());
    }
    else if(trie=="NUM_VOL"){
       ui->tableView->setModel(bi.AfficherTrivol());
    }
}

void MainWindow::on_modifier_2_clicked()
{
    Billet M;

            QString text=M.apercu_pdf();
            ui->imp_2->setText(text);

                     QPrinter printer ;
                     printer.setPrinterName("imprim");
                     QPrintDialog dialog (&printer,this);
                     if(dialog.exec()==QDialog::Rejected) return ;
                      ui->imp_2->print(&printer);
}
