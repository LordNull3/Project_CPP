#include "gest_emp.h"
#include "ui_gest_emp.h"
#include "employee.h"
#include "connection.h"
#include <QMessageBox>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QPrintDialog>
#include "mydialog.h"
#include "ui_mydialog.h"
gest_emp::gest_emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_emp)
{
    ui->setupUi(this);
    ui->NUMLINE->setValidator(new QIntValidator(0,99999999,this)) ;
        ui->SALAIRELINE->setValidator(new QIntValidator(0,99999999,this)) ;
ui->tableView->setModel(emp.afficher());
}

gest_emp::~gest_emp()
{
    delete ui;
}
void gest_emp::on_ajouter_clicked()
{
    QSqlQuery query;
    QString id_emp=ui->IDLINE->text();
    QString NOM_EMP=ui->NomLine->text();
    int num_tel=ui->NUMLINE->text().toInt();
    QString PRENOM_EMP=ui->PRENOMLINE->text();
    QString MAIL=ui->MAILINE->text();
    int SALAIRE=ui->SALAIRELINE->text().toInt();
    QString SEXE=ui->SEXELINE->text();
    QString MP=ui->MPLINE->text();
    QString PROMOTION=ui->PROMOTIONLINE->text();

   Employee E (id_emp, num_tel, NOM_EMP, PRENOM_EMP, MAIL, SEXE, PROMOTION, MP, SALAIRE);
   bool test= E.ajouter();
       if(test)
       {
           ui->tableView->setModel(emp.afficher());
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("ajouter successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else{
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("ajouter failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}
}






void gest_emp::on_supp_clicked()
{
  // emp.setid_Employee(ui->linesupp->text());
   // QString id_emp=ui->linesupp->text();
    QModelIndex index = ui->tableView->currentIndex();
      QString id_emp = index.data(Qt::DisplayRole).toString();
      // emp.setid_Employee
    bool test =emp.supprimer(id_emp);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel(emp.afficher());
}
    else{
         ui->tableView->setModel(emp.afficher());
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}


   //pdf ::::


void gest_emp::on_supp_3_clicked()
{
        ui->tableView->setModel(emp.AfficherTri());
}

void gest_emp::on_pdf_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tableView->model()->rowCount();
                        const int columnCount = ui->tableView->model()->columnCount();

                        out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"

                           //     "<align='right'> " << datefich << "</align>"
                             "<center> <H1> SmartSky \n \n\n\n</H1><H2>Liste des employe \n \n\n\n</H2><H3> \n \n\n\n</H3></br></br><table border=1 cellspacing=3 cellpadding=2>\n";

                        // headers
                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tableView->isColumnHidden(column)) {
                                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table> </center>\n"
                            "</body>\n"
                            "</html>\n";

                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc ;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);

}

void gest_emp::on_lineEdit_3_textChanged(const QString &arg1)
{
    ui->tableView->setModel(emp.rechercherNom(arg1));
}

void gest_emp::on_pdf_2_clicked()
{QString id_emp=ui->IDLINE->text();
    QString NOM_EMP=ui->NomLine->text();
    int num_tel=ui->NUMLINE->text().toInt();
    QString PRENOM_EMP=ui->PRENOMLINE->text();
    QString MAIL=ui->MAILINE->text();
    float SALAIRE=ui->SALAIRELINE->text().toFloat();
    QString SEXE=ui->SEXELINE->text();
    QString MP=ui->MPLINE->text();
    QString PROMOTION=ui->PROMOTIONLINE->text();
   Employee E (id_emp, num_tel, NOM_EMP, PRENOM_EMP, MAIL, SEXE, PROMOTION, MP, SALAIRE);
   if(E.modifier(id_emp))
   {
            QMessageBox::information(nullptr, QObject::tr("Modifier un employee"),
                        QObject::tr("employee modifié.\n"), QMessageBox::Cancel);
            ui->tableView->setModel(emp.afficher());
            ui->IDLINE->setText("");
            ui->NomLine->setText("");
            ui->PRENOMLINE->setText("");
            ui->NUMLINE->setText("");
            ui->MAILINE->setText("");
            ui->SEXELINE->setText("");
            ui->MPLINE->setText("");
            ui->SALAIRELINE->setText("");
            ui->PROMOTIONLINE->setText("");



   }
   else
   {
      QMessageBox::critical(nullptr, QObject::tr("Modifier un Employee"),

                            QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);


   }


}

void gest_emp::on_back_clicked()
{
    this->close();
        MYDialog d;
        d.show();
        d.exec();
}
