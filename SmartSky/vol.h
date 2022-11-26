#ifndef VOL_H
#define VOL_H

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>


class Vol
{
private:
    QString id_vol , pdd , pda;
    int capacite_vol,duree,id_avion;

public:
    //Constructeur-destructeur
    Vol();
    Vol(QString,QString,QString,int,int,int);
    ~Vol(){};

    //Getters
    QString getid_vol(){return id_vol;}
    QString getpdd(){return pdd;}
    QString getpda(){return pda;}
    int getcapacite_vol(){return capacite_vol;}
    int getduree(){return duree;}
    int getavion(){return id_avion;}

    //Setters
    void setid_vol(QString v){id_vol=v;}
    void setpdd(QString pd){pdd=pd;}
    void setpda(QString pa){pda=pa;}
    void setcapacite_vol(int cv){capacite_vol=cv;}
    void setduree(int d){duree=d;}
    void setavion(int a){id_avion=a;}

     //fct
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);

    QSqlQueryModel * tri();
    QSqlQueryModel * Tri_pdd();
    QSqlQueryModel * Tri_pda();
    QSqlQueryModel * Tri_duree();
    QSqlQueryModel *rechercher(QString nom);
    QString  export_pdf();
    QSqlQueryModel * Combo_req();


};

#endif // VOL_H
