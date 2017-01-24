#ifndef PERSONAL_H
#define PERSONAL_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include "table.h"


namespace Ui {
class personal;
}

class personal : public QWidget
{
    Q_OBJECT

public:
    QRect p;
    explicit personal(QRect q,QWidget *parent = 0);
    ~personal();
    struct pers
    {
        QString text[7];
        int n[25];
    }inputStr[60],crit,cautStr[20];//60 este numarul maxim de intrari, poate fi modificat
    int nrStr;
    int indiceCautare=0;
    int indiceIntrare=0;
    int cautare=0;
    int editare=0;
    Table Personal;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::personal *ui;
    //QString filename_DB;
    //QFile personal_DB;
    //personal_DB.open(QIODevice::ReadOnly | QIODevice::Text);
    //QTextStream persin;
};

#endif // PERSONAL_H
