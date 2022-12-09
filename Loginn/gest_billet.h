#ifndef GEST_BILLET_H
#define GEST_BILLET_H
#include <QPrinter>
#include<QPrintDialog>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QMainWindow>
#include "billet.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QtCharts>
#include <QVBoxLayout>
#include <QDialog>

namespace Ui {
class gest_billet;
}

class gest_billet : public QDialog
{
    Q_OBJECT

public:
    explicit gest_billet(QWidget *parent = nullptr);
    ~gest_billet();
private slots:
    void on_ajouter_clicked();

    void on_supp_clicked();

    void on_modify_clicked();

    void on_modifier_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_modifier_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    void sendMail();
    void mailSent(QString);
    void browse();

    void on_arduino_clicked();

    void on_back_clicked();

private:


private:
    Ui::gest_billet *ui;
    QStringList files;
  Billet bi;
};

#endif // GEST_BILLET_H
