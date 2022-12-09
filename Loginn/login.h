#ifndef LOGIN_H
#define LOGIN_H
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include "QString"


class Loginn
{
private:
    QString NOM_EMP,PRENOM_EMP,mail,MDP,id_emp,Sexe;

public:
    Loginn() ;
    Loginn(QString,QString,QString,QString,QString,QString) ;
    ~Loginn(){}
    QString getnom(){return  NOM_EMP;}
    QString getprenom(){return  PRENOM_EMP ;}
    QString getUsername(){return  id_emp ;}
    QString getEMAIL() {return  mail ;}
    QString getMDP() {return  MDP ;}
    QString getSexe() {return  Sexe ;}

    void setnom(QString n){NOM_EMP=n ;}
    void setprenom(QString p){PRENOM_EMP=p ;}
    void setUsername(QString j){id_emp= j ;}
    void setEmail(QString e){mail=e ;}
    void setMDP(QString m){MDP=m;}
    void setSexe (QString  s ){Sexe =s ;}
    bool ajouter() ;
    bool LOGINNN(QString,QString);


};

#endif // LOGIN_H
