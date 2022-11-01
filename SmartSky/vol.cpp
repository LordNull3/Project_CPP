#include "vol.h"
#include <QtDebug>
#include <QObject>


Vol::Vol()
{
    id_vol="";
    pdd="";
    pda="";
    capacite_vol=0;
    duree=0;
}




Vol::Vol(QString id_vol,QString pdd,QString pda,int capacite_vol,int duree)
{
    this->id_vol=id_vol;
    this->pdd=pdd;
    this->pda=pda;
    this->capacite_vol=capacite_vol;
    this->duree=duree;
}

bool Vol::ajouter()
{
   QSqlQuery Q1;
   QString du = QString::number(duree);
   QString cv = QString::number(capacite_vol);
   Q1.prepare("insert into vol(id_vol,pdd,pda,capacite_vol,duree)" "values(:id_vol, :pdd,:pda,:capacite_vol,:duree)");
   Q1.bindValue(":id_vol",id_vol);
   Q1.bindValue(":pdd",pdd);
   Q1.bindValue(":pda",pda);
   Q1.bindValue(":capacite_vol",cv);
   Q1.bindValue(":duree",du);
   return Q1.exec();
}


bool Vol::supprimer(QString id_vol)
{
    QSqlQuery Q1;
        Q1.prepare("Delete from Vol where id_vol=:id");
        Q1.bindValue(0,id_vol);

    return Q1.exec();


}



bool Vol::modifier(QString id_vol)
{
    QSqlQuery Q1;
    QString r1 = QString::number(capacite_vol);
    QString r2 = QString::number(duree);

    Q1.prepare("UPDATE Vol set pdd=:pdd , pda=:pda , capacite_vol=:capacite_vol , duree=:duree WHERE id_vol=:id_vol");

    Q1.bindValue(":id_vol",id_vol);
    Q1.bindValue(":pdd",pdd);
    Q1.bindValue(":pda",pda);
    Q1.bindValue(":capacite_vol",r1);
    Q1.bindValue(":duree",r2);

    return Q1.exec();

}





QSqlQueryModel* Vol::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT id_vol , pdd , pda , capacite_vol , duree  FROM Vol");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}




