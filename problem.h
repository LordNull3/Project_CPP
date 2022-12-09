#ifndef PROBLEM_H
#define PROBLEM_H
#include "avion.h"

class Problem
{
public:
    int get_id_p(){return Id_p;}
    QString get_Etat(){return Etat;}

    void set_id_p(int Id_p){this->Id_p=Id_p;}
    void set_Etat(QString Etat){this->Etat=Etat;}

    bool ajouter(int,QString);
    bool Fix();
private:
    int Id_p;
    QString Etat;

};

#endif // PROBLEM_H
