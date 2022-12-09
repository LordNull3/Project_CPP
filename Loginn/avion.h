#ifndef AVION_H
#define AVION_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QDebug>
#include<QObject>
#include <QtCharts>
#include <QPieSeries>
class Avion
{


private:
    int id_a;
    int capacite_a;
    int Problem;
    int FC;
    int BC;
    int EC;
    float Charge_a;
public:

    Avion();
    Avion(int id_a,int capacite_a,int Problem,int FC,int BC,int EC,float Charge_a);


    int get_id(){return id_a;}
    int get_BC(){return BC;}
    int get_FC(){return FC;}
    int get_EC(){return EC;}
    int get_capacite(){return capacite_a;}
    int get_Problem(){return Problem;}
    int get_Charge(){return Charge_a;}

    void set_id(int id){this->id_a=id;}
    void set_BC(int BC){this->BC=BC;}
    void set_FC(int FC){this->FC=FC;}
    void set_EC(int EC){this->EC=EC;}
    void set_capacite(int capacite){this->capacite_a=capacite;}
    void set_Problem(int Problem){this->Problem=Problem;}
    void set_Charge(float Charge_a){this->Charge_a=Charge_a;}

    bool ajouter();
    bool ajouterProblem();
    QSqlQueryModel * afficher();
    QSqlQueryModel * rechercher_dynamique(QString a);
    QSqlQueryModel * sort(QString a);
    QChart * stat();
    bool supprimer(int);
    bool modifier();
    bool tester_Avion();
};
#endif // AVION_H
