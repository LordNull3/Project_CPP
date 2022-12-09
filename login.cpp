#include "login.h"
#include <QSqlQuery>






Loginn::Loginn()
{
    NOM_EMP="";
    PRENOM_EMP="";
    id_emp="";
    mail="";
    MDP="";
    Sexe="";
}



Loginn::Loginn(QString NOM,QString PRENOM,QString Email,QString MDP,QString USERNAME,QString Sexe)
{
    this->NOM_EMP=NOM;
    this->PRENOM_EMP=PRENOM;
    this->mail=Email;
    this->MDP=MDP;
    this->id_emp=USERNAME;
    this->Sexe=Sexe;
}

bool Loginn::ajouter()
{

    QSqlQuery qry;
    qry.prepare("INSERT INTO EMPLOYEE(NOM_EMP,PRENOM_EMP,MAIL,MDP,id_emp,SEXE)""values(:NOM,:PRENOM,:MAIL,:MDP,:USERNAME,:SEXE)");
    qry.bindValue(":NOM",NOM_EMP);
    qry.bindValue(":PRENOM",PRENOM_EMP);
    qry.bindValue(":MAIL",mail);
    qry.bindValue(":MDP",MDP);
    qry.bindValue(":USERNAME",id_emp);
    qry.bindValue(":SEXE",Sexe);
    return qry.exec();
}


bool Loginn::LOGINNN(QString USERNAME , QString MDP)
{
    QSqlQuery qry;
    qry.prepare("SELECT id_emp, MDP FROM EMPLOYEE WHERE id_emp=\'"+ USERNAME +"\' AND MDP=\'" + MDP + "\'");
    qry.addBindValue(USERNAME);
    qry.addBindValue(MDP);
    if(qry.exec())
        if(qry.next())
            {
                QString user = QVariant(qry.value(0)).toString();
            if(user==USERNAME)
            {return true;}
        }
    return false;

}
