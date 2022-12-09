#include "gest_employee.h"
#include "ui_gest_employee.h"
#include <QMessageBox>
#include <QApplication>
#include "employee.h"
#include <QPrinter>
#include <QPrintDialog>
#include "stat_combo.h"
#include "ui_stat_combo.h"
#include <QFileDialog>
#include <QTextStream>
#include <QHostAddress>
#include "arduino.h"
gest_employee::gest_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_employee)
{
    ui->setupUi(this);
    ui->ShowEMP->setModel(E.afficher());
    ui->lineEdit_ID->setPlaceholderText("Entrez l'ID");
    ui->lineEdit_NOM->setPlaceholderText("Entrez le Nom");
    ui->lineEdit_PRE->setPlaceholderText("Entrez le prenom");
    ui->Mail->setPlaceholderText("Entrez le mail");
    ui->MDP->setPlaceholderText("Entrez le mot de passe");
    ui->lineEditUser->setPlaceholderText("Entrez le nom d'utilisateur");
    ui->lineEdit_Salaire->setPlaceholderText("Entrez le salaire");
    ui->textEdit->setReadOnly(true);
    //chat
    C.connect_arduino();
    socket.connectToHost(QHostAddress("127.0.0.1"), 9999);
        connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        connect(ui->sendButton, SIGNAL(pressed()), this, SLOT(onSendButtonPressed()));

}

gest_employee::~gest_employee()
{
    delete ui;
}


void gest_employee::on_bouton1_2_clicked()
{
    int ID_EMP=ui->lineEdit_ID->text().toInt();
    QString NOM=ui->lineEdit_NOM->text();
    QString PRENOM=ui->lineEdit_PRE->text();
    QString mail=ui->Mail->text();
    QString USERNAME=ui->lineEditUser->text();
    QString MDP=ui->MDP->text();
    QString Sexe=ui->SexeCombo->currentText();
    int   SALAIRE=ui->lineEdit_Salaire->text().toInt();
    employee E(NOM,PRENOM,mail,USERNAME,MDP,Sexe,ID_EMP,SALAIRE);
    bool test=E.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    ui->ShowEMP->setModel(E.afficher());
    ui->lineEdit_ID->setText("");
    ui->lineEdit_NOM->setText("");
    ui->lineEdit_PRE->setText("");
    ui->lineEdit_Salaire->setText("");
    ui->Mail->setText("");
    ui->lineEditUser->setText("");
    ui->MDP->setText("");
    ui->SexeCombo->currentText();
}


void gest_employee::on_SuppButt_clicked()
{
    QModelIndex index = ui->ShowEMP->currentIndex();
          int ID_EMP = index.data(Qt::DisplayRole).toInt();

        bool test =E.supprimer(ID_EMP);
        if(test && ID_EMP!=0)
        {

            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("suppression effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
                                    ui->ShowEMP->setModel(E.afficher());
    }
        else{

            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("suppression non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
}

void gest_employee::on_b2_2_clicked()
{
            int ID_EMP=ui->lineEdit_ID->text().toInt();
            QString NOM=ui->lineEdit_NOM->text();
            QString PRENOM=ui->lineEdit_PRE->text();
            QString mail=ui->Mail->text();
            QString USERNAME=ui->lineEditUser->text();
            QString MDP=ui->MDP->text();
            QString Sexe=ui->SexeCombo->currentText();
            int   SALAIRE=ui->lineEdit_Salaire->text().toInt();
            employee E(NOM,PRENOM,mail,USERNAME,MDP,Sexe,ID_EMP,SALAIRE);
               if((ID_EMP==0)&&(NOM=="")&&(PRENOM=="")&&(SALAIRE==0)&&(mail=="")&&(USERNAME=="")&&(MDP=="")&&(Sexe==""))
                  {
                      QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Veuillez remplir les champs"), QMessageBox::Ok);
                   }
                 else if(ID_EMP == 0)
                  {
                      QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Veuillez remplir l'id"), QMessageBox::Ok);

                  }
                  else if(NOM =="")
                     {
                         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("Veuillez remplir le nom"), QMessageBox::Ok);

                     }
                  else if(PRENOM =="")
                     {
                         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("Veuillez remplir le prenom"), QMessageBox::Ok);

                     }
                  else if(SALAIRE ==0)
                     {
                         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("Veuillez remplir le salaire"), QMessageBox::Ok);

                     }
               else if(mail == "")
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez remplir le mail"), QMessageBox::Ok);

                }
               else if(USERNAME == "")
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez remplir le username"), QMessageBox::Ok);

                }
               else if(MDP == "")
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez remplir le mot de passe"), QMessageBox::Ok);

                }
               else if(Sexe == "")
                {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                QObject::tr("Veuillez remplir le sexe"), QMessageBox::Ok);

                }

               else {

                   if(E.modifierEmployes(ID_EMP))
                   {
                            QMessageBox::information(nullptr, QObject::tr("Modifier un employe"),
                                        QObject::tr("employe modifié.\n"), QMessageBox::Cancel);

                            ui->lineEdit_ID->setText("");
                            ui->lineEdit_NOM->setText("");
                            ui->lineEdit_PRE->setText("");
                            ui->lineEdit_Salaire->setText("");
                            ui->Mail->setText("");
                            ui->lineEditUser->setText("");
                            ui->MDP->setText("");
                            ui->SexeCombo->currentText();


                   }
                   else
                   {
                      QMessageBox::critical(nullptr, QObject::tr("Modifier un employer"),

                                            QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
                   }
               }
               ui->ShowEMP->setModel(E.afficher());
}

void gest_employee::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->ShowEMP->setModel(E.rechercherNom(arg1));
}

void gest_employee::on_pushButton_2_clicked()
{
   QString tri=ui->comboBox->currentText();
   if(tri=="ID"){
    ui->ShowEMP->setModel(E.AfficherTrieID());}
   else {if (tri=="NOM"){
       ui->ShowEMP->setModel(E.AfficherTrieNom());
   }
   else{
       ui->ShowEMP->setModel(E.AfficherTriePrenom());
   }
   }
}

void gest_employee::on_pushButton_clicked()
{
    QModelIndex index = ui->ShowEMP->currentIndex();
            QString id = index.data(Qt::DisplayRole).toString();
             QString nom = ui->ShowEMP->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
             ui->lineEdit_NOM->setText(nom);
                QString prenom = ui->ShowEMP->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
                ui->lineEdit_PRE->setText(prenom);
                 QString salaire = ui->ShowEMP->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
                 ui->lineEdit_Salaire->setText(salaire);
                 QString Mail = ui->ShowEMP->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
                 ui->Mail->setText(Mail);
                 QString MDP = ui->ShowEMP->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
                 ui->MDP->setText(MDP);
                 QString USERNAME = ui->ShowEMP->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
                 ui->lineEditUser->setText(USERNAME);
                 QString Sexe = ui->ShowEMP->model()->index(index.row(), 7).data(Qt::DisplayRole).toString();
                 ui->SexeCombo->setCurrentText(Sexe);
                  QString id_emp = ui->ShowEMP->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
                  ui->lineEdit_ID->setText(id_emp);
}

void gest_employee::on_pushButton_5_clicked()
{

    QString strStream;
           QTextStream out(&strStream);

           const int rowCount = ui->ShowEMP->model()->rowCount();
           const int columnCount = ui->ShowEMP->model()->columnCount();

           out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               <<  QString("<title>%1</title>\n").arg("strTitle")
               <<  "</head>\n"
               "<body bgcolor=#F5F5DC link=#5000A0>\n"


               "<center><h1 style='color:#4b3621;'>Liste des Employees</h1></br></br><table border=1 cellspacing=0 cellpadding=2 color=#4b3621>\n";




           out << "<thead><tr bgcolor=#F5F5DC> <th style='color:#4b3621;'>Numero</th>";
           for (int column = 0; column < columnCount; column++)
               if (!ui->ShowEMP->isColumnHidden(column))
                   out << QString("<th style='color:#4b3621;'>%1</th>").arg(ui->ShowEMP->model()->headerData(column, Qt::Horizontal).toString());
           out << "</tr></thead>\n";



           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr> <td  bkcolor=0>" << row + 1 << "</td>";
               for (int column = 0; column < columnCount; column++)
               {
                   if (!ui->ShowEMP->isColumnHidden(column))
                   {
                       QString data = ui->ShowEMP->model()->data(ui->ShowEMP->model()->index(row, column)).toString().simplified();
                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                   }
               }
               out << "</tr>\n";
           }
           out <<  "</table> </center>\n"
               "</body>\n"
               "</html>\n";

           QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty())
           {
               fileName.append(".pdf");
           }

           QPrinter printer (QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);

           printer.setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml(strStream);
           doc.print(&printer);
           QString text=E.export_pdf();
           ui->PdfEdit->setText(text);

}

void gest_employee::on_pushButton_4_clicked()
{
    stat_combo *s = new stat_combo();

        s->setWindowTitle("Les Statistiques selon le Genre");
        s->choix_pie();
        s->show();
}

//chat
void gest_employee::onReadyRead()
{
    QByteArray data = socket.readAll();

    ui->textEdit->append(QString::fromStdString(data.toStdString()));
}

void gest_employee::onSendButtonPressed()
{
    if(ui->lineEdit_3->text() == "")
        ui->lineEdit_3->setStyleSheet("border: 1px solid red;");
    else{
        ui->lineEdit_3->setStyleSheet("");
        QString text = ui->lineEdit_3->text();
        ui->lineEdit_3->setText("");
        socket.write(QByteArray::fromStdString(text.toStdString()));
   }
}

void gest_employee::on_pushButton_3_clicked()
{
    QString data = C.read_from_arduino();
        int result = data.split( "," )[0].toInt();
        if (result == 1 )
            ui->fireLabel->setText("FIRE");
        else
            ui->fireLabel->setText("NO FIRE");
}



void gest_employee::on_offButton_clicked()
{
    C.write_to_arduino("s");
}
