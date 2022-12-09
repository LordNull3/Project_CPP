#include "gest_avion.h"
#include "ui_gest_avion.h"
#include "mydialog.h"
#include "ui_mydialog.h"
gest_avion::gest_avion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_avion)
{
    ui->setupUi(this);
    ui->tableAvion->setModel(A.afficher());
    QChart *  chart = new QChart();
         chart=A.stat();
        QChartView * chartview = new QChartView(chart,ui->widget);
        chartview->resize(400,300);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setBackgroundBrush(Qt::transparent);
    chartview->show();

    QSqlQuery q;
    QSqlQueryModel * model=new QSqlQueryModel();
    q.exec("SELECT ID_EMP FROM EMPLOYEE");
    model->setQuery(q);
    ui->Employe_combobox_a->setModel(model);

    QSqlQuery q1;
    QSqlQueryModel * model1=new QSqlQueryModel();
    q1.exec("SELECT ID_PROBLEM FROM EMP_REG_AVION WHERE ETAT='active'");
    model1->setQuery(q1);
    ui->Problem_combobox->setModel(model1);
}

gest_avion::~gest_avion()
{
    delete ui;
}


void gest_avion::on_Ajouter_a_clicked()
{
    int id_a=ui->Id_a_input->text().toInt();
    int capacite_a=ui->Capacite_a_input->text().toInt();
    int Problem=ui->Problem_a_input->text().toInt();
    int FC=ui->FC_a_input->text().toInt();
    int BC=ui->BC_a_input->text().toInt();
    int EC=ui->EC_a_input->text().toInt();
    float Charge_a=ui->Charge_a_input->text().toFloat();

   Avion A(id_a,capacite_a,Problem,FC,BC,EC,Charge_a);

   if(A.tester_Avion())
   {
       bool test=A.ajouter();
       if(test)
       {
           QMessageBox::information(nullptr, QObject::tr("Ajouter un Avion"),
                            QObject::tr("Avion ajouté.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tableAvion->setModel(A.afficher());

           QString objet="AJOUT Avion";
           QString message=" Votre Avion a été ajouté avec succés" ;

       }

           else {
               QMessageBox::critical(nullptr, QObject::tr("Ajouter un Avion"),
                           QObject::tr("Avion non ajouté.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

       }
   }
   else
   {
       QMessageBox::critical(nullptr, QObject::tr("Ajouter un Avion"),
                   QObject::tr("Donnée invalide.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }

}


void gest_avion::on_Supprimer_a_clicked()
{
    Avion A1;
    A1.set_id(ui->tableAvion->selectionModel()->currentIndex().data().toInt());
    bool test=A1.supprimer(A1.get_id());


    QMessageBox msgBox;

    if(test){

        msgBox.setText("Suppression avec succes.");
        ui->tableAvion->setModel(A.afficher());
    }else{
    msgBox.setText("Echec ");
    msgBox.exec();
}
}

void gest_avion::on_Modifier_a_clicked()
{
    int id_a=ui->Id_a_input->text().toInt();
    int capacite_a=ui->Capacite_a_input->text().toInt();
    int Problem=ui->Problem_a_input->text().toInt();
    int FC=ui->FC_a_input->text().toInt();
    int BC=ui->BC_a_input->text().toInt();
    int EC=ui->EC_a_input->text().toInt();
    float Charge_a=ui->Charge_a_input->text().toFloat();

   Avion A1(id_a,capacite_a,Problem,FC,BC,EC,Charge_a);

   if(A1.tester_Avion())
   {
       bool test=A1.modifier();
       if(test)
       {
           QMessageBox::information(nullptr, QObject::tr("Modifier un Avion"),
                            QObject::tr("Avion modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tableAvion->setModel(A.afficher());

           QString objet="Modifier Avion";
           QString message=" Votre Avion a été modifié avec succés" ;

       }

           else {
               QMessageBox::critical(nullptr, QObject::tr("Modifier un Avion"),
                           QObject::tr("Avion non modifié.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           }
     }
   else
   {
       QMessageBox::critical(nullptr, QObject::tr("Modifier un Avion"),
                   QObject::tr("Donnée invalide.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }
}

void gest_avion::on_search_a_input_textChanged(const QString &arg1)
{
    Avion a;
    ui->tableAvion->setModel(a.rechercher_dynamique(arg1));
}

void gest_avion::on_Tri_Avion_clicked()
{
    Avion A;
    ui->tableAvion->setModel(A.sort( ui->Tri_Combobox_a->currentText()));
}

void gest_avion::on_PDF_a_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tableAvion->model()->rowCount();
                const int columnCount = ui->tableAvion->model()->columnCount();

                out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("strTitle")
                    <<  "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"

                    //     "<align='right'> " << datefich << "</align>"
                    "<center><h1 style='color:#732626;'>Liste des clients</h1></br></br><table border=1 cellspacing=0 cellpadding=2 color=#732626>\n";

                // headers

                //les noms des colonnes
                out << "<thead><tr bgcolor=#f0f0f0> <th style='color:#732626;'>Numero</th>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableAvion->isColumnHidden(column))
                        out << QString("<th style='color:#732626;'>%1</th>").arg(ui->tableAvion->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";


                //remplir le tableau
                for (int row = 0; row < rowCount; row++)
                {
                    out << "<tr> <td  bkcolor=0>" << row + 1 << "</td>";
                    for (int column = 0; column < columnCount; column++)
                    {
                        if (!ui->tableAvion->isColumnHidden(column))
                        {
                            QString data = ui->tableAvion->model()->data(ui->tableAvion->model()->index(row, column)).toString().simplified();
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
                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                doc.print(&printer);
}

void gest_avion::on_Image_a_clicked()
{
    QString picpath=QFileDialog::getOpenFileName
               (
                   this,
               tr("Open File"),
               "D:/ImageQT//",
               "All File (*.*);;JPG File (*.jpg);;PNG File (*.png)"
                   );

       QSqlQuery qry;
       int id_a=ui->Id_a_input_3->text().toInt();
       QString id_string= QString::number(id_a);
       qry.prepare("update AVION set IMAG ='"+picpath+"'where ID_AVION='"+id_string+"'");
       if(qry.exec()){

          QMessageBox::information(this,tr("Update Result"),tr("<font color=black>Profile Photo Update Completed"));

       qry.prepare("select IMAG from AVION where ID_AVION='"+id_string+"'");
       if(qry.exec())
           while(qry.next())
           {
               QPixmap pro_pic;
               QString location=qry.value(0).toString();
               pro_pic.load(location);
               ui->label_img_a->setPixmap(pro_pic);
               ui->label_img_a->setScaledContents(true);
           }
       }
}

void gest_avion::on_Add_Problem_Button_a_clicked()
{
    Problem P;
    int id_a=ui->Id_a_input_3->text().toInt();
    P.set_id_p(ui->Id_Problem_a->text().toInt());
    P.set_Etat("active");
    QString id_e=ui->Employe_combobox_a->currentText();
    P.ajouter(id_a,id_e);
}

void gest_avion::on_pushButton_3_clicked()
{
    Problem P;
    P.set_id_p(ui->Problem_combobox->currentText().toInt());
    P.Fix();
}

void gest_avion::on_back_clicked()
{
    this->close();
        MYDialog d;
        d.show();
        d.exec();
}
