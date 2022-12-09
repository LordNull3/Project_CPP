#include "mydialog.h"
#include "ui_mydialog.h"
#include "gest_billet.h"
#include "ui_gest_billet.h"
#include "billet.h"
#include "gest_vol.h"
#include "ui_gest_vol.h"
#include "gest_emp.h"
#include "ui_gest_emp.h"
#include "employee.h"
#include "gest_avion.h"
#include "ui_gest_avion.h"
MYDialog::MYDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MYDialog)
{
    ui->setupUi(this);
}

MYDialog::~MYDialog()
{
    delete ui;
}


void MYDialog::on_pushButton_2_clicked()
{this->close();
    gest_billet b;
    b.show();
    b.exec();
}


void MYDialog::on_pushButton_3_clicked()
{this->close();
    gest_vol v;
    v.show();
    v.exec();

}

void MYDialog::on_pushButton_clicked()
{this->close();
    gest_emp e;
    e.show();
    e.exec();
}

void MYDialog::on_pushButton_4_clicked()
{this->close();
    gest_avion a;
    a.show();
    a.exec();
}
