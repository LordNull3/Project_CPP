#include "gest_billet.h"
#include "ui_gest_billet.h"
#include "billet.h"
#include "connection.h"
#include <QMessageBox>
#include<QObject>
#include<QDebug>
#include "smtp.h"
#include"qrcodegen.h"
#include <QFileDialog>
#include <QtCharts>
#include "gest_arduino.h"
#include "ui_gest_arduino.h"
#include "mydialog.h"
#include "ui_mydialog.h"
gest_billet::gest_billet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gest_billet)
{
    ui->setupUi(this);
    ui->tableView->setModel(bi.afficher());

    ui->comboBox_2->setModel(bi.afficher_2());
    QRegularExpression r1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",QRegularExpression::CaseInsensitiveOption);
     QRegExp mailREX ("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
             mailREX.setPatternSyntax(QRegExp::RegExp);

        ui->nom->setValidator(new QRegularExpressionValidator(r1, this));
    QChart *chart = new QChart();
         chart=bi.stat();
        QChartView *chartview = new QChartView(chart,ui->widget);
        chartview->resize(500,400);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setBackgroundBrush(Qt::transparent);
    chartview->show();

        connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
}

gest_billet::~gest_billet()
{
    delete ui;
}


void  gest_billet::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   gest_billet::sendMail()
{
    Smtp* smtp = new Smtp("abdoubenayed44@gmail.com","wxtkztlytbhxxsdi", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("abdoubenayed44@gmail.com", ui->lineEdit_11->text() , ui->lineEdit_12->text(),ui->textEdit->toPlainText(), files );
    else
        smtp->sendMail("abdoubenayed44@gmail.com", ui->lineEdit_11->text() , ui->lineEdit_12->text(),ui->textEdit->toPlainText());
}
void   gest_billet::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
     ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->file->clear();
   ui->textEdit->clear();

}









void gest_billet::on_ajouter_clicked()
{
    QSqlQuery query;
    QString id_billet=ui->id->text();
    QString nom=ui->nom->text();
    QString num_vol=ui->comboBox_2->currentText();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();
    QString classement=ui->comboBox->currentText();
    QString mail=ui->mail->text();
   Billet b (id_billet,classement,emplacement,num_vol,num_voyageur,nom,mail);
   bool test= b.ajouter();
       if(test)
       {
           ui->tableView->setModel(bi.afficher());
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("ajouter successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           QChart *chart = new QChart();
                chart=bi.stat();
               QChartView *chartview = new QChartView(chart,ui->widget);
               chartview->resize(500,400);
               chartview->setRenderHint(QPainter::Antialiasing);

   }
       else{
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("ajouter failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);}
}

void gest_billet::on_supp_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
      QString id_billet = index.data(Qt::DisplayRole).toString();

    bool test =bi.supprimer(id_billet);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("suppression effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(bi.afficher());
        QChart *chart = new QChart();
             chart=bi.stat();
            QChartView *chartview = new QChartView(chart,ui->widget);
            chartview->resize(500,400);
            chartview->setRenderHint(QPainter::Antialiasing);

}
    else{
         ui->tableView->setModel(bi.afficher());
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void gest_billet::on_modify_clicked()
{
    QString id_billet=ui->id->text();
    QString nom=ui->nom->text();
      QString num_vol=ui->comboBox_2->currentText();
    QString num_voyageur=ui->voy->text();
    QString emplacement=ui->emp->text();
 QString mail=ui->mail->text();
    QString classement=ui->comboBox->currentText();
   Billet b (id_billet,classement,emplacement,num_vol,num_voyageur,nom,mail);
   if(b.modifier(id_billet))
   {
            QMessageBox::information(nullptr, QObject::tr("Modifier un billet"),
                        QObject::tr("billet modifié.\n"), QMessageBox::Cancel);
            ui->tableView->setModel(bi.afficher());
            QChart *chart = new QChart();
                 chart=bi.stat();
                QChartView *chartview = new QChartView(chart,ui->widget);
                chartview->resize(500,400);
                chartview->setRenderHint(QPainter::Antialiasing);



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

void gest_billet::on_modifier_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
             QString id_billet = index.data(Qt::DisplayRole).toString();
             QString nom = ui->tableView->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();
             ui->nom->setText(nom);
             QString num_vol = ui->tableView->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();
             ui->comboBox_2->setCurrentText(num_vol);
             QString classement = ui->tableView->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();
             ui->comboBox->setCurrentText(classement);
             QString emplacement = ui->tableView->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();
             ui->emp->setText(emplacement);
             QString num_voyageur = ui->tableView->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
             ui->voy->setText(num_voyageur);
             QString id = ui->tableView->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
             ui->id->setText(id);
             QString mail = ui->tableView->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
             ui->mail->setText(mail);

}

void gest_billet::on_lineEdit_3_textChanged(const QString &arg1)
{
  ui->tableView->setModel(bi.rechercherNom(arg1));
}

void gest_billet::on_pushButton_4_clicked()
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

void gest_billet::on_modifier_2_clicked()
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
                             "<center> <H1> SmartSky \n \n\n\n</H1><H2>Liste des billet \n \n\n\n</H2><H3> \n \n\n\n</H3></br></br><table border=1 cellspacing=3 cellpadding=2>\n";
                       " <img src=':/new/prefix1/unknown.png' alt='HTML5 Icon' style='width:512px;height:512px'>";

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

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);

}

void gest_billet::on_pushButton_5_clicked()
{
    QString text ="detail du Billet  :"+ ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString()
               +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString()
               +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString()
               +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString()
               +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toString()
             +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6)).toString();


       using namespace qrcodegen;
         QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
         qint32 sz = qr.getSize();
         QImage im(sz,sz, QImage::Format_RGB32);
           QRgb black = qRgb(0, 0, 0);
           QRgb white = qRgb(255,255,255);
         for (int y = 0; y < sz; y++)
           for (int x = 0; x < sz; x++)
             im.setPixel(x,y,qr.getModule(x, y) ? black : white );
         ui->qrcode->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void gest_billet::on_pushButton_6_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
             QString id_billet = index.data(Qt::DisplayRole).toString();
             QString nom = ui->tableView->model()->index(index.row(), 0).data(Qt::DisplayRole).toString();

             QString num_vol = ui->tableView->model()->index(index.row(), 4).data(Qt::DisplayRole).toString();

             QString classement = ui->tableView->model()->index(index.row(), 2).data(Qt::DisplayRole).toString();

             QString emplacement = ui->tableView->model()->index(index.row(), 1).data(Qt::DisplayRole).toString();

             QString num_voyageur = ui->tableView->model()->index(index.row(), 5).data(Qt::DisplayRole).toString();
QString mail = ui->tableView->model()->index(index.row(), 6).data(Qt::DisplayRole).toString();
             QString id = ui->tableView->model()->index(index.row(), 3).data(Qt::DisplayRole).toString();
             QString text="id:  "+id +"              "+"nom:  "+nom+"                "+"classement:  "+classement+"               "+"emplacement:  "+emplacement+"               "+"numero vol:  "+num_vol+"                   "+"numero voyageur:  "+num_voyageur;
            ui->textEdit->setPlainText(text);
            ui->lineEdit_11->setText(mail);
}

void gest_billet::on_arduino_clicked()
{
    gest_arduino z;
    z.show();
    z.exec();
}

void gest_billet::on_back_clicked()
{this->close();
    MYDialog d;
    d.show();
    d.exec();
}
