#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "login.h"
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <mydialog.h>
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
    void on_bouton1_4_clicked();

    void on_bouton1_5_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    Loginn L;
};
#endif // MAINWINDOW_H
