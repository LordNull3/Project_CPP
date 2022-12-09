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
mail="";

}

Billet::Billet (QString id_billet,QString classement,QString emplacemet,QString num_vol,QString num_voyageur,QString nom,QString mail){
   this->id_billet=id_billet;
    this->classement=classement;
    this->num_voyageur=num_voyageur;
    this->num_vol=num_vol;
    this->emplacement=emplacemet;
    this->nom=nom;
    this->mail=mail;
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
QString Billet ::getmail(){return mail;}
void Billet::setmail(QString id_billet){this->mail=mail;}


bool Billet::ajouter(){

QSqlQuery query;

query.prepare("insert into billet (nom, emplacement, classement,id_billet,num_vol,num_voyageur,mail) "
                        "VALUES (:surname, :emplacement, :classement,:id_billet,:num_vol,:num_voyageur,:mail)");
          query.bindValue(":id_billet", id_billet);
          query.bindValue(":classement",classement);
          query.bindValue(":emplacement", emplacement);
          query.bindValue(":num_vol",num_vol);

query.bindValue(":num_voyageur",num_voyageur);
          query.bindValue(":surname",nom);
           query.bindValue(":mail",mail);



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
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("mail"));
    return  model ;
}
QSqlQueryModel * Billet:: afficher_2(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select ID_VOL from VOL ");


    return  model ;
}
bool Billet::modifier(QString id_billet)
{
    QSqlQuery Q1;

    Q1.prepare("update billet set  nom=:nom,emplacement=:emplacement,classement=:classement , num_vol=:num_vol , num_voyageur=:num_voyageur,mail=:mail WHERE id_billet=:id_billet");

    Q1.bindValue(":id_billet",id_billet);

    Q1.bindValue(":classement",classement);
    Q1.bindValue(":emplacement",emplacement);
    Q1.bindValue(":num_vol",num_vol);
    Q1.bindValue(":num_voyageur",num_voyageur);
    Q1.bindValue(":nom",nom);
        Q1.bindValue(":emplacement",emplacement);
        Q1.bindValue(":num_vol",num_vol);
        Q1.bindValue(":num_voyageur",num_voyageur);
        Q1.bindValue(":nom",nom);
          Q1.bindValue(":mail",mail);

    return Q1.exec();

}
QSqlQueryModel * Billet::rechercherNom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from billet where num_voyageur like '"+nom+"%' or id_billet LIKE '"+nom+"%' or classement like '"+nom+"%' ");
    q.addBindValue("%"+ nom +"%");
    q.exec();
    model->setQuery(q);
    return (model);

}
QSqlQueryModel * Billet::AfficherTri()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM billet ORDER BY nom");

    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CLASSEMENT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ID_VOL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("EMPLACEMENT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_VOYAGEUR"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("mail"));
    return model;
}

QSqlQueryModel * Billet::AfficherTriid()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM billet ORDER BY id_billet");

    return model;
}
QSqlQueryModel * Billet::AfficherTrivoy()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM billet ORDER BY num_voyageur");

    return model;
}
QSqlQueryModel * Billet::AfficherTrivol()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM billet ORDER BY num_vol");

    return model;
}


QString Billet:: apercu_pdf()
 {
    QString text="          ** Les Billets  **      \n \n " ;
     QSqlQuery query ;
     QString i,x,z,a,b,c,h1,h2,h3,h;


      query.exec("select * from billet  ");
      while (query.next())
      {
         i=query.value(0).toString();
         x=query.value(1).toString();
         z=query.value(2).toString();
         a=query.value(3).toString();
         b=query.value(4).toString();
         c=query.value(5).toString();



        text += "\n billet  id_billet : "+a+"\n\n - Nom : "+ i+"\n - classement : "+ z+"\n - id_vol:"+b+"\n - emplacement :"+x+"\n - num_voyageur : "+c+"_______\n\n " ;


     }


             return text ;
 }


QChart * Billet ::stat(){
QSqlQuery q,q1,q2,q3,q4,q5;
   q.exec("Select * from billet");
   int tot=0;
   while (q.next())
       tot++;
  qDebug() << "total =" << tot;
   q1.prepare("Select * from billet where classement = :nom ");
   q1.bindValue(":nom","premiere classe");
   q1.exec();

   int tot_don=0;
   while (q1.next())
       tot_don++;
qDebug() << "pourcentage don =" << tot_don;
   qreal pour_1=(tot_don*100)/tot;

   q2.prepare("Select *from billet where classement = :nom  ");
   q2.bindValue(":nom","classe affaires");
   q2.exec();
   int tot_event=0;
   while (q2.next())
       tot_event++;

   qreal pour_2=(tot_event*100)/tot;

   q3.prepare("Select * from billet where classement = :nom  ");
   q3.bindValue(":nom","classe eco");
   q3.exec();
   int tot_dep=0;
   while (q3.next())
       tot_dep++;
   qreal pour_3=(tot_dep*100)/tot;



   QPieSeries *series = new QPieSeries();
    series->append("premiere classe",pour_1);
    series->append("classe affaires",pour_2);
    series->append("classe eco",pour_3);

    QPieSlice *slice0= series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series->slices().at(1);

    slice1->setBrush(Qt::green);

    QPieSlice *slice2= series->slices().at(2);
    slice2->setLabelVisible();
     slice2->setBrush(Qt::red);

    QChart *chart = new QChart();

    chart->addSeries(series);

    chart->setTitle("classement des billet");
    chart->legend()->hide();
    series->setLabelsVisible();
   for(auto slice : series->slices())
    slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
 //chart->setBackgroundBrush(Qt::transparent);

   return chart;
}
