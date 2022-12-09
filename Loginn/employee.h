#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include <QSqlQueryModel>
#include<QPrinter>
#include<QSqlQuery>
class Employee
{
private:
    int num_tel;
    QString  id_emp ,NOM_EMP, PRENOM_EMP, MAIL, SEXE, PROMOTION, MDP;
    int SALAIRE;

public:

    Employee();
    Employee(QString,int,QString,QString,QString,QString,QString,QString,int);
    QString getid_emp();
    int getnum_tel ();
    QString getNOM_EMP ();
    QString getPRENOM_EMP ();
    QString getMAIL ();
    QString getSEXE ();
    QString getPROMOTION ();
    QString getMP ();
    int getSALAIRE ();

    void setid_emp(QString);
    void setnum_tel(int);
    void setNOM_EMP(QString);
    void setPRENOM_EMP(QString);
    void setMAIL(QString);
    void setSEXE(QString);
    void setPROMOTION(QString);
    void setMP(QString);
    void setSALAIRE(int);
    bool ajouter();
    bool supprimer(QString);
    QSqlQueryModel * afficher();
    bool modifier(QString);
    QSqlQueryModel * AfficherTriid();
    QSqlQueryModel * AfficherTrivoy();
    QSqlQueryModel * AfficherTrivol();
    QSqlQueryModel * AfficherTri();
    QSqlQueryModel * rechercherNom(QString nom);



};

#endif // EMPLOYEE_H
