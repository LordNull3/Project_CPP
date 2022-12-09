#ifndef GEST_VOL_H
#define GEST_VOL_H
#include "vol.h"
#include "stats.h"
#include <QDialog>

namespace Ui {
class gest_vol;
}

class gest_vol : public QDialog
{
    Q_OBJECT

public:
    explicit gest_vol(QWidget *parent = nullptr);
    ~gest_vol();
private slots:
    void on_AjouterButton_clicked();


    void on_Del_button_clicked();


    void on_tri_vol_button_clicked();

    void on_Modifer_button_clicked();

    void on_Afficher_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_Pdf_Ex_clicked();

    void on_Stats_Button_clicked();

    void on_Excel_Button_clicked();

    void on_arduino_clicked();

    void on_back_clicked();

private:
    Ui::gest_vol *ui;
    Vol V;
    stats *s;
};

#endif // GEST_VOL_H
