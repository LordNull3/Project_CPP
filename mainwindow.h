#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "billet.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    Billet bi;
};
#endif // MAINWINDOW_H
