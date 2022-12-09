#include "gest_vol.h"
#include "ui_gest_vol.h"
#include <QMessageBox>
#include <QApplication>
#include "vol.h"
#include "QIntValidator"
#include <QPrinter>
#include <QPrintDialog>
#include "stats.h"
#include "exportexcelobject.h"
#include <QFileDialog>
#include "webaxwidget.h"
#include <QSettings>
#include <QObject>
#include <QtDebug>
#include "gest_arduino.h"
#include "ui_gest_arduino.h"
#include "mydialog.h"
#include "ui_mydialog.h"
gest_vol::gest_vol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_vol)
{
    ui->setupUi(this);
    ui->CvAline->setValidator(new QIntValidator(10,500, this));
    ui->DuAline->setValidator(new QIntValidator(1,72, this));
    ui->ShowV->setModel(V.afficher());
    ui->LD_Avion->setModel(V.Combo_req());
    ui->Excel_combo->setModel(V.Combo_req());
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
    QRegularExpression r1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",QRegularExpression::CaseInsensitiveOption);

        ui->PddAline->setValidator(new QRegularExpressionValidator(r1, this));
        ui->PdaAline->setValidator(new QRegularExpressionValidator(r1, this));
}

gest_vol::~gest_vol()
{
    delete ui;
}

void gest_vol::on_AjouterButton_clicked()
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

void gest_vol::on_Del_button_clicked()
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

void gest_vol::on_tri_vol_button_clicked()
{
    QString triV=ui->Tri_CB->currentText();
    if(triV=="Id_vol"){
      ui->ShowV->setModel(V.tri());}
    else if(triV=="Pays de depart"){
       ui->ShowV->setModel(V.Tri_pdd());
    }
    else if(triV=="Pays d'arrivée"){
       ui->ShowV->setModel(V.Tri_pda());
    }
    else if(triV=="Durée"){
       ui->ShowV->setModel(V.Tri_duree());
    }
}

void gest_vol::on_Modifer_button_clicked()
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

void gest_vol::on_Afficher_clicked()
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

void gest_vol::on_lineEdit_textChanged(const QString &arg1)
{
    ui->ShowV->setModel(V.rechercher(arg1));
}

void gest_vol::on_Pdf_Ex_clicked()
{
    QString strStream;
                            QTextStream out(&strStream);

                            const int rowCount = ui->ShowV->model()->rowCount();
                            const int columnCount = ui->ShowV->model()->columnCount();

                            out <<  "<html>\n"
                                "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                <<  QString("<title>%1</title>\n").arg("strTitle")
                                <<  "</head>\n"
                                "<body bgcolor=#ffffff link=#5000A0>\n"

                               //     "<align='right'> " << datefich << "</align>"
                                 "<center> <H1> SmartSky \n \n\n\n</H1><H2>Liste des vols \n \n\n\n</H2><H3> \n \n\n\n</H3></br></br><table border=1 cellspacing=3 cellpadding=2>\n";


                            // headers
                            out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                            for (int column = 0; column < columnCount; column++)
                                if (!ui->ShowV->isColumnHidden(column))
                                    out << QString("<th>%1</th>").arg(ui->ShowV->model()->headerData(column, Qt::Horizontal).toString());
                            out << "</tr></thead>\n";

                            // data table
                            for (int row = 0; row < rowCount; row++) {
                                out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                for (int column = 0; column < columnCount; column++) {
                                    if (!ui->ShowV->isColumnHidden(column)) {
                                        QString data = ui->ShowV->model()->data(ui->ShowV->model()->index(row, column)).toString().simplified();
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

                       QTextDocument doc;
                        doc.setHtml(strStream);
                        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                        doc.print(&printer);
}

void gest_vol::on_Stats_Button_clicked()
{
    s = new stats();

  s->setWindowTitle("Stats");
  s->Stats_bar();
  s->show();

}



void gest_vol::on_Excel_Button_clicked()
{



    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->ShowV);

    //colums to export
    obj.addField(0, "ID_VOL", "char(20)");
    obj.addField(1, "ID_AVION", "NUMBER");
    obj.addField(2, "PDD", "char(20)");
    obj.addField(3, "PDA", "char(20)");
    obj.addField(4, "CAPACITE_VOL", "NUMBER");
    obj.addField(5, "DUREE", "NUMBER");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}


void gest_vol::on_arduino_clicked()
{
    gest_arduino z;
    z.show();
    z.exec();

}

void gest_vol::on_back_clicked()
{
    this->close();
        MYDialog d;
        d.show();
        d.exec();
}
