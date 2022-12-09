#ifndef GEST_EMP_H
#define GEST_EMP_H

#include <QDialog>
#include <employee.h>
namespace Ui {
class gest_emp;
}

class gest_emp : public QDialog
{
    Q_OBJECT

public:
    explicit gest_emp(QWidget *parent = nullptr);
    ~gest_emp();
private slots:
    void on_ajouter_clicked();



    void on_supp_clicked();

  //  void on_modify_clicked();

    void on_supp_3_clicked();

    void on_pdf_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_pdf_2_clicked();

    void on_back_clicked();

private:
    Ui::gest_emp *ui;
    Employee emp;
};

#endif // GEST_EMP_H
