#include "problem.h"


bool Problem ::ajouter(int Id_a,QString Id_e)
{

       QSqlQuery query;
       QString id_a_string= QString::number(Id_a);

       QString id_p_string= QString::number(Id_p);

              query.prepare("INSERT INTO EMP_REG_AVION (ID_EMP ,ID_AVION , ETAT,ID_PROBLEM) "
                            "VALUES (:id_e, :id_a, :Etat, :id_p)");

              //qDebug() << "test = "<<Charge_a<<Charge_string   ;

              query.bindValue(":id_a", id_a_string);
              query.bindValue(":id_e", Id_e);
              query.bindValue(":Etat",Etat);
              query.bindValue(":id_p", id_p_string);

            return   query.exec();
}

bool Problem ::Fix()
{
    QSqlQuery query;
    QString id_p_string= QString::number(Id_p);
    query.prepare("UPDATE EMP_REG_AVION SET ETAT=:fix  WHERE ID_PROBLEM =:id_p ");
    query.bindValue(":id_p", id_p_string);
    query.bindValue(":fix", "fixed");
    return   query.exec();
}
