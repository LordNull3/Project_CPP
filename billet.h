#ifndef BILLET_H
#define BILLET_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
class Billet
{
public:

    Billet();
    Billet(QString,QString,QString,QString,QString,QString);
    QString getid_billet();
    QString getemplacement();
    QString getnum_vol();
    QString getnum_voyageur();
    QString getclassemen();
    void setid_billet(QString);
    void setemplacement(QString);
    void setnum_vol(QString);
    void setclassement(QString);
    QString getnom();
    void setnom(QString);
     void setnum_voyageur(QString);
     bool ajouter();
     bool supprimer(QString);
     QSqlQueryModel * afficher();
      bool modifier(QString);
private:
 QString  emplacement ,num_vol , num_voyageur ;
 QString  id_billet,classement,nom ;
};

#endif // BILLET_H
