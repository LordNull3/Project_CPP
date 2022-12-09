#include "connexion.h"

connexion::connexion() {}
bool connexion ::createconnection()
{
db= QSqlDatabase :: addDatabase("QODBC");
bool test=false;

db.setDatabaseName("Source_Projet_2A");
db.setUserName("abdou2");//inserer nom de l'utilisateur
db.setPassword("abdou2");//inserer mot de passe de cet utilisateur

if(db.open()) test=true;
return test;
}
void connexion::closeConnection(){db.close();}

