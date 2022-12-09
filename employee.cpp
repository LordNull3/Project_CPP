#include "employee.h"
#include<QDebug>
#include "connection.h"
#include<QObject>

Employee::Employee()
{
id_emp="";
num_tel=0;
NOM_EMP="";
PRENOM_EMP="";
MAIL="";
SEXE="";
PROMOTION="";
MDP="";
SALAIRE=0;
}
Employee::Employee (QString id_emp,int num_tel,QString NOM_EMP,QString PRENOM_EMP,QString MAIL,QString SEXE,QString PROMOTION,QString MP,int SALAIRE){
   this->id_emp=id_emp;
    this->num_tel=num_tel;
    this->NOM_EMP=NOM_EMP;
    this->PRENOM_EMP=PRENOM_EMP;
    this->MAIL=MAIL;
    this->SEXE=SEXE;
    this->PROMOTION=PROMOTION;
    this->MDP=MP;
    this->SALAIRE=SALAIRE;
}
QString Employee:: getid_emp(){return id_emp;}
int Employee:: getnum_tel(){return num_tel;}
QString Employee:: getNOM_EMP (){return NOM_EMP;}
QString Employee:: getPRENOM_EMP (){return PRENOM_EMP;}
QString Employee:: getMAIL (){return MAIL;}
QString Employee:: getSEXE (){return SEXE;}
QString Employee:: getPROMOTION (){return PROMOTION;}
QString Employee:: getMP (){return MDP;}
int Employee:: getSALAIRE (){return SALAIRE;}

void Employee:: setid_emp(QString id_emp){this->id_emp=id_emp;}
void Employee:: setnum_tel(int num_tel){this->num_tel=num_tel;}
void Employee:: setNOM_EMP(QString NOM_EMP){this->NOM_EMP=NOM_EMP;}
void Employee:: setPRENOM_EMP(QString PRENOM_EMP){this->PRENOM_EMP=PRENOM_EMP;}
void Employee:: setMAIL(QString MAIL){this->MAIL=MAIL;}
void Employee:: setSEXE(QString SEXE){this->SEXE=SEXE;}
void Employee:: setPROMOTION(QString PROMOTION){this->PROMOTION=PROMOTION;}
void Employee:: setMP(QString MP){this->MDP=MP;}
void Employee:: setSALAIRE(int SALAIRE){this->SALAIRE=SALAIRE;}


bool Employee::ajouter(){

QSqlQuery query;
  QString du = QString::number(num_tel);
    QString a = QString::number(SALAIRE);

query.prepare("insert into employee (ID_EMP, NOM_EMP,PRENOM_EMP, MAIL, SEXE, PROMOTION,SALAIRE, MDP,NUM_TEL) "
                        "VALUES (:ID_emp, :NOM_EMP,:PRENOM_EMP, :MAIL, :SEXE, :PROMOTION, :SALAIRE,:MP,:num_tel)");
          query.bindValue(":ID_emp", id_emp);
          query.bindValue(":NOM_EMP", NOM_EMP);
          query.bindValue(":PRENOM_EMP",PRENOM_EMP);
          query.bindValue(":MAIL",MAIL);
          query.bindValue(":SEXE",SEXE);
          query.bindValue(":PROMOTION",PROMOTION);
          query.bindValue(":SALAIRE",a);
          query.bindValue(":MP",MDP);
          query.bindValue(":num_tel",du);

return query.exec();
}

bool Employee::supprimer(QString id_emp){
QSqlQuery query;
query.prepare("Delete Employee where id_emp=:id");
query.bindValue(":id", id_emp);
return query.exec();
}


QSqlQueryModel * Employee:: afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Employee");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_emp"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_EMP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_EMP"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("PROMOTION"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("MDP"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("SALAIRE"));
    return  model ;
}
bool Employee::modifier(QString id_emp)
{
    QSqlQuery Q1;

    Q1.prepare("update Employee set  NOM_EMP=:nom,PRENOM_EMP=:PRENOM_EMP,SEXE=SEXE , num_tel=:num_tel , MAIL=:MAIL , SALAIRE=SALAIRE , MDP=MP , PROMOTION=PROMOTION WHERE id_emp=:id_emp");

    Q1.bindValue(":id_emp",id_emp);
    Q1.bindValue(":nom",NOM_EMP);
    Q1.bindValue(":PRENOM_EMP",PRENOM_EMP);
    Q1.bindValue(":num_tel",num_tel);
    Q1.bindValue(":MAIL",MAIL);
    Q1.bindValue(":SEXE",SEXE);
    Q1.bindValue(":PROMOTION",PROMOTION);
    Q1.bindValue(":SALAIRE",SALAIRE);
    Q1.bindValue(":MP",MDP);


    return Q1.exec();
}
QSqlQueryModel * Employee::AfficherTri()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee ORDER BY NOM_EMP");

    model->setHeaderData(3,Qt::Horizontal,QObject::tr("id_EMP"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM_EMP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_EMP"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_tel"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("PROMOTION"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("MDP"));
    return model;
}

QSqlQueryModel * Employee::AfficherTriid()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee ORDER BY id_EMP");

    return model;
}
QSqlQueryModel * Employee::AfficherTrivoy()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM e ORDER BY num_tel");

    return model;
}
QSqlQueryModel * Employee::AfficherTrivol()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee ORDER BY SALAIRE");

    return model;
}
QSqlQueryModel * Employee::rechercherNom(QString nom)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from Employee where id_emp like '"+nom+"%' or NOM_EMP LIKE '"+nom+"%'  ");
    q.addBindValue("%"+ nom +"%");
    q.exec();
    model->setQuery(q);
    return (model);

}
