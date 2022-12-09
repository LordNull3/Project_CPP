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
    id_avion=0;
}




Vol::Vol(QString id_vol,QString pdd,QString pda,int capacite_vol,int duree,int id_avion)
{
    this->id_vol=id_vol;
    this->pdd=pdd;
    this->pda=pda;
    this->capacite_vol=capacite_vol;
    this->duree=duree;
    this->id_avion=id_avion;
}

bool Vol::ajouter()
{
   QSqlQuery Q1;
   QString du = QString::number(duree);
   QString cv = QString::number(capacite_vol);
   QString a = QString::number(id_avion);
   Q1.prepare("insert into vol(id_vol,pdd,pda,capacite_vol,duree,id_avion)" "values(:id_vol,:pdd,:pda,:capacite_vol,:duree,:id_avion)");
   Q1.bindValue(":id_vol",id_vol);
   Q1.bindValue(":pdd",pdd);
   Q1.bindValue(":pda",pda);
   Q1.bindValue(":capacite_vol",cv);
   Q1.bindValue(":duree",du);
   Q1.bindValue(":id_avion",a);
   return Q1.exec();
}


bool Vol::supprimer(QString id_vol)
{
    QSqlQuery Q1;
        Q1.prepare("Delete from Vol where id_vol=:id");
        Q1.bindValue(":id",id_vol);

    return Q1.exec();


}



bool Vol::modifier(QString id_vol)
{
    QSqlQuery Q1;
    QString r1 = QString::number(capacite_vol);
    QString r2 = QString::number(duree);
    QString r3 = QString::number(id_avion);

    Q1.prepare("UPDATE Vol set pdd=:pdd , pda=:pda , capacite_vol=:capacite_vol , duree=:duree , id_avion=:id_avion WHERE id_vol=:id_vol");

    Q1.bindValue(":id_vol",id_vol);
    Q1.bindValue(":pdd",pdd);
    Q1.bindValue(":pda",pda);
    Q1.bindValue(":capacite_vol",r1);
    Q1.bindValue(":duree",r2);
    Q1.bindValue(":id_avion",r3);


    return Q1.exec();

}





QSqlQueryModel* Vol::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT id_vol, id_avion , pdd , pda , capacite_vol , duree   FROM Vol");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}

QSqlQueryModel * Vol::tri()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_vol, id_avion,pdd,pda,capacite_vol,duree FROM vol ORDER BY pdd,pda,duree");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}

QSqlQueryModel * Vol::Tri_pdd()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_vol, id_avion,pdd,pda,capacite_vol,duree FROM vol ORDER BY pdd");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}

QSqlQueryModel * Vol::Tri_pda()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_vol, id_avion,pdd,pda,capacite_vol,duree FROM vol ORDER BY pda");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}

QSqlQueryModel * Vol::Tri_duree()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT id_vol, id_avion,pdd,pda,capacite_vol,duree FROM vol ORDER BY duree");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Id_Vol"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("Id_avion"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Pdd"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Pda"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Capacite_vol"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Duree"));
    return model;
}





QSqlQueryModel * Vol::rechercher(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select id_vol,pdd,pda,capacite_vol,duree,id_avion from vol where id_vol like '"+nom+"%' or capacite_vol LIKE '"+nom+"%' or duree like '"+nom+"%' ");
    q.addBindValue("%"+ nom +"%");
    q.exec();
    model->setQuery(q);
    return (model);

}




QString Vol:: export_pdf()
 {
    QString text="          **** Les Vols  ****      \n \n " ;
     QSqlQuery query ;
     QString i,x,z,a,b,e;



      query.exec("select id_vol,pdd,pda,capacite_vol,duree,id_avion from vol ");
      while (query.next())
      {
         i=query.value(0).toString();
         e=query.value(1).toString();
         x=query.value(2).toString();
         z=query.value(3).toString();
         a=query.value(4).toString();
         b=query.value(5).toString();


        text += "\n Vol Id : "+i+"\n \n Avion Id : "+e+"\n \n - Pay de depart : "+ x+"\n - Pays d'arriveé : "+ z+"\n - capacite du vol:"+a+"\n - Duree :"+b+"\n" ;


     }


             return text ;
 }


QSqlQueryModel * Vol:: Combo_req(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select ID_AVION from AVION ");


    return  model ;
}

















