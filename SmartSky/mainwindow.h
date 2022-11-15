#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vol.h"
#include "stats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    Vol V;
    stats *s;
};
#endif // MAINWINDOW_H
