#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;

db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet_2A");
db.setUserName("abdou2");//inserer nom de l'utilisateur
db.setPassword("abdou2");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
