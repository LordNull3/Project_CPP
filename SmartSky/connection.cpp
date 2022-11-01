#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;

db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet_A2");
db.setUserName("ahmed2");//inserer nom de l'utilisateur
db.setPassword("ahmed2");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
