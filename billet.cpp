#include "billet.h"

#include<QDebug>
#include "connection.h"
#include<QObject>
Billet::Billet()
{
id_billet="";
classement="";
emplacement="";
num_vol="";
num_voyageur="";
nom="";
}

Billet::Billet (QString id_billet,QString classement,QString emplacemet,QString num_vol,QString num_voyageur,QString nom){
   this->id_billet=id_billet;
    this->classement=classement;
    this->num_voyageur=num_voyageur;
    this->num_vol=num_vol;
    this->emplacement=emplacemet;
    this->nom=nom;
}

QString Billet:: getid_billet(){return id_billet;}
QString Billet ::getemplacement(){return emplacement;}
QString Billet:: getnum_vol(){return num_vol;}
QString Billet::getnum_voyageur(){return num_voyageur;}
QString Billet ::getclassemen(){return classement;}
void Billet::setid_billet(QString id_billet){this->id_billet=id_billet;}
void Billet::setemplacement(QString empalcement) {this->emplacement=emplacement;}
void Billet::setnum_vol(QString num_vol){this->num_vol = num_vol;}
void Billet::setclassement(QString classement){this->classement=classement; }
void Billet:: setnom(QString nom){this->nom=nom;}
void Billet:: setnum_voyageur(QString num_voyageur){this->num_voyageur=num_voyageur;}


bool Billet::ajouter(){

QSqlQuery query;

query.prepare("insert into billet (nom, emplacement, classement,id_billet,num_vol,num_voyageur) "
                        "VALUES (:surname, :emplacement, :classement,:id_billet,:num_vol,:num_voyageur)");
          query.bindValue(":id_billet", id_billet);
          query.bindValue(":class",classement);
          query.bindValue(":emplacement", emplacement);
          query.bindValue(":num_vol",num_vol);

query.bindValue(":num_voyageur",num_voyageur);
          query.bindValue(":surname",nom);



return query.exec();
}

bool Billet::supprimer(QString id_billet){
QSqlQuery query;
query.prepare("Delete from billet where id_billet=:id");
query.bindValue(":id", id_billet);
return query.exec();
}


QSqlQueryModel * Billet:: afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from BILLET");
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CLASSEMENT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_VOL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("EMPLACEMENT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_VOYAGEUR"));
    return  model ;
}
bool Billet::modifier(QString id_billet)
{
    QSqlQuery Q1;

    Q1.prepare("update billet set  nom=:nom,emplacement=:emplacement,classement=:classement , num_vol=:num_vol , num_voyageur=:num_voyageur WHERE id_billet=:id_billet");

    Q1.bindValue(":id_billet",id_billet);
    Q1.bindValue(":classement",classement);
    Q1.bindValue(":emplacement",emplacement);
    Q1.bindValue(":num_vol",num_vol);
    Q1.bindValue(":num_voyageur",num_voyageur);
    Q1.bindValue(":nom",nom);

    return Q1.exec();

}



