#include "avion.h"

Avion::Avion()
{
    id_a=0;
    capacite_a=0;
    Problem=0;
    FC=0;
    BC=0;
    EC=0;
    Charge_a=0;

}

Avion::Avion(int id_a,int capacite_a,int Problem,int FC,int BC,int EC,float Charge_a)
{
    this->id_a=id_a;
    this->capacite_a=capacite_a;
    this->Problem=Problem;
    this->FC=FC;
    this->BC=BC;
    this->EC=EC;
    this->Charge_a=Charge_a;
}




bool Avion ::ajouter()
{

    QSqlQuery query;
    QString id_string= QString::number(id_a);
    QString capacite_string= QString::number(capacite_a);
    QString P_string= QString::number(Problem);
    QString FC_string= QString::number(FC);
    QString BC_string= QString::number(BC);
    QString EC_string= QString::number(EC);
    QString Charge_string= QString::number(Charge_a);

          query.prepare("INSERT INTO AVION (ID_AVION ,CAPACITE , N_PROBLEM,FIRST_CLASS , ECONOMY_CLASS, BUSINESS_CLASS, CHARGE) "
                        "VALUES (:id_a, :capacite_a, :Problem, :FC, :EC, :BC, :Charge_a)");

          //qDebug() << "test = "<<Charge_a<<Charge_string   ;

          query.bindValue(":id_a", id_string);
          query.bindValue(":capacite_a", capacite_string);
          query.bindValue(":Problem",P_string);
          query.bindValue(":FC", FC_string);
          query.bindValue(":EC", EC_string);
          query.bindValue(":BC", BC_string);
          query.bindValue(":Charge_a", Charge_string);

        return   query.exec();
}


QSqlQueryModel *Avion::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Avion");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Capacite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Problem"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("BC"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Charge"));

    return model;
}

bool Avion::supprimer(int id_a)
{
    QSqlQuery query;
    QString id_string= QString::number(id_a);
    query.prepare("DELETE FROM AVION WHERE ID_AVION = :id_a");
    query.bindValue(":id_a", id_string);
    return    query.exec();
}

bool Avion::modifier()
{
    QSqlQuery query;
    QString id_string= QString::number(id_a);
    QString capacite_string= QString::number(capacite_a);
    QString P_string= QString::number(Problem);
    QString FC_string= QString::number(FC);
    QString BC_string= QString::number(BC);
    QString EC_string= QString::number(EC);
    QString Charge_string= QString::number(Charge_a);

    query.prepare("UPDATE AVION SET ID_AVION= :id_a, CAPACITE = :capacite_a, N_PROBLEM= :Problem, FIRST_CLASS = :FC, ECONOMY_CLASS = :EC, BUSINESS_CLASS = :BC, CHARGE = :Charge_a WHERE ID_AVION =:id_a ");

    query.bindValue(":id_a", id_string);
    query.bindValue(":capacite_a", capacite_string);
    query.bindValue(":Problem",P_string);
    query.bindValue(":FC", FC_string);
    query.bindValue(":EC", EC_string);
    query.bindValue(":BC", BC_string);
    query.bindValue(":Charge_a", Charge_string);

    return    query.exec();
}

bool Avion::tester_Avion()
{
    if(id_a<0 or capacite_a<0 or Problem<0 or FC<0 or BC<0 or EC<0 or Charge_a<0)
        return  false;
    else if(FC+BC+EC!=capacite_a)
        return false;
    else return true;
}

QSqlQueryModel * Avion::rechercher_dynamique(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM AVION where ID_AVION like '"+a+"' ||'%'");
    query.bindValue(":id",a);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Capacite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Problem"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("BC"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Charge"));

        return model;
}

QSqlQueryModel * Avion::sort(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from Avion ORDER BY "+a);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Capacite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Problem"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FC"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EC"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("BC"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Charge"));
            return model;
}

bool Avion ::ajouterProblem()
{

    QSqlQuery query;
    QString id_string= QString::number(id_a);
    QString capacite_string= QString::number(capacite_a);
    QString P_string= QString::number(Problem);
    QString FC_string= QString::number(FC);
    QString BC_string= QString::number(BC);
    QString EC_string= QString::number(EC);
    QString Charge_string= QString::number(Charge_a);

          query.prepare("INSERT INTO AVION (ID_AVION ,CAPACITE , N_PROBLEM,FIRST_CLASS , ECONOMY_CLASS, BUSINESS_CLASS, CHARGE) "
                        "VALUES (:id_a, :capacite_a, :Problem, :FC, :EC, :BC, :Charge_a)");

          //qDebug() << "test = "<<Charge_a<<Charge_string   ;

          query.bindValue(":id_a", id_string);
          query.bindValue(":capacite_a", capacite_string);
          query.bindValue(":Problem",P_string);
          query.bindValue(":FC", FC_string);
          query.bindValue(":EC", EC_string);
          query.bindValue(":BC", BC_string);
          query.bindValue(":Charge_a", Charge_string);

        return   query.exec();
}

QChart * Avion ::stat(){
QSqlQuery q,q1,q2,q3,q4,q5;

    q.prepare("Select SUM(CAPACITE) from AVION ");
    q.exec();
    int total=q.first();

   q1.prepare("Select SUM(FIRST_CLASS) from AVION ");
   q1.exec();
   int FC=q1.first();

   q2.prepare("Select SUM(BUSINESS_CLASS) from AVION ");
   q2.exec();
   int BC=q2.first();

   q3.prepare("Select SUM(ECONOMY_CLASS) from AVION ");
   q3.exec();
   int EC=q3.first();

   qreal FirstClass=(FC*100)/total;
   qreal BusinessClass=(BC*100)/total;
   qreal EconomyClass=(EC*100)/total;



   QPieSeries * series = new QPieSeries();
    series->append("First class",FirstClass);
    series->append("Business affaires",BusinessClass);
    series->append("Economic eco",EconomyClass);

    QPieSlice * slice0=  series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice * slice1  =  series->slices().at(1);

    slice1->setLabelVisible();

    slice1->setBrush(Qt::green);

    QPieSlice * slice2= series->slices().at(2);
    slice2->setLabelVisible();
     slice2->setBrush(Qt::red);

    QChart * chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Places class chart");
    chart->legend()->hide();



   return chart;
}
