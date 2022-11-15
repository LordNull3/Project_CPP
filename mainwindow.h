#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "billet.h"
#include <QMainWindow>
#include <QPrinter>
#include<QPrintDialog>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
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
    void on_ajouter_clicked();



    void on_supp_clicked();

    void on_modify_clicked();

    void on_modifier_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_modifier_2_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();

    void on_pushButton_5_clicked();

   // void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
      QStringList files;
    Billet bi;
};
#endif // MAINWINDOW_H
