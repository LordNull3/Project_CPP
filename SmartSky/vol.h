#ifndef VOL_H
#define VOL_H

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>


class Vol
{
private:
    QString id_vol , pdd , pda;
    int capacite_vol,duree;

public:
    //Constructeur-destructeur
    Vol();
    Vol(QString,QString,QString,int,int);
    ~Vol(){};

    //Getters
    QString getid_vol(){return id_vol;}
    QString getpdd(){return pdd;}
    QString getpda(){return pda;}
    int getcapacite_vol(){return capacite_vol;}
    int getduree(){return duree;}

    //Setters
    void setid_vol(QString v){id_vol=v;}
    void setpdd(QString pd){pdd=pd;}
    void setpda(QString pa){pda=pa;}
    void setcapacite_vol(int cv){capacite_vol=cv;}
    void setduree(int d){duree=d;}

     //fct
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
};

#endif // VOL_H
