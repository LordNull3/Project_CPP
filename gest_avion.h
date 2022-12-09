#ifndef GEST_AVION_H
#define GEST_AVION_H
#include "avion.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QPainter>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include<QObject>
#include <QtCharts>
#include <QPieSeries>
#include "problem.h"
#include <QDialog>

namespace Ui {
class gest_avion;
}

class gest_avion : public QDialog
{
    Q_OBJECT

public:
    explicit gest_avion(QWidget *parent = nullptr);
    ~gest_avion();
private slots:
     void on_Ajouter_a_clicked();


     void on_Supprimer_a_clicked();

     void on_Modifier_a_clicked();

     void on_search_a_input_textChanged(const QString &arg1);

     void on_Tri_Avion_clicked();

     void on_PDF_a_clicked();

     void on_Image_a_clicked();

     void on_Add_Problem_Button_a_clicked();

     void on_pushButton_3_clicked();

     void on_back_clicked();

private:
    Ui::gest_avion *ui;
     Avion A;
};

#endif // GEST_AVION_H
