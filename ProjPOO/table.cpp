#include "table.h"
#include <QDebug>
#include<QFile>
#include<QTextStream>
QSqlDatabase Table::db;

struct
{
    QString text[19];
    QString n[25];
}decod;
Table::Table()
{



}

int Table::createTable(QString tbName, QString columnValues) {

    if(!QFile::exists( "procese.db" ))
    {
        db = QSqlDatabase::addDatabase("QSQLITE","procese.db");
        db.setDatabaseName(DATABASE_NAME);
        db.open();

    }
    if (!db.isOpen()) {
        connect();
    }

        //if(db.isOpen())
          //  qDebug()<<"party";
        //else qDebug()<<"nu i party";
        QSqlQuery query(db);

        QString sql = "CREATE TABLE " +  tbName + " (CRT INT PRIMARY KEY NOT NULL , " + columnValues + ");"; //Se formeaza comanda Sqlite
        qDebug()<<query.exec(sql);
        db.close();



    return 0;
}
int Table::tableSize(QString tableName){
    int count=0;
    if (!db.isOpen()) {
        connect();

    //    db.open();
    }
    QSqlQuery query(db);
    QString sql = "SELECT * FROM " +tableName +";";

   // qDebug()<<"Row count sql executed: "<<query.exec(sql);
    while(query.next())
            count++;
    numOfRows=count;


    db.close();

    return count;
}
//only for depozitare
void Table::insertQuery(QString tableName, std::map<QString,QString> stringValues,std::map<QString,float> floatValues,bool value) {

    numOfRows=tableSize(tableName);
    if (!db.isOpen()) {
        connect();
        //db.open();
    }
    qDebug()<<numOfRows;
    numOfRows++;
    //if(db.isOpen())
        //qDebug()<<"doubleParty"<<floatValues["dpo"];
        QSqlQuery query(db);
        //numOfRows=tableSize(tableName);
       // QString sql = "INSERT INTO " + tableName + " VALUES('',"  + stringValues['data']+"," + ");";
       //qDebug()<<query.exec("INSERT INTO " + tableName + " VALUES("+numOfRows+",'"  + stringValues["data"]+"', "+value+", "+floatValues["acuratete_preg_comenzi"]+", "+floatValues["rata_daune"]+", "+floatValues["acuratete_stoc"]+", "+floatValues["grad_ocupare_depozit"]+", "+floatValues["dso"]+", "+floatValues["dpo"] + ");");
        query.prepare("INSERT INTO " + tableName + " VALUES(:numOfRows,:date, :bool, :acurateteComenzi, :rata_daune, :acuratete_stoc, :grad_ocupare_depozit, :dso, :dpo );");
        query.bindValue(":numOfRows",numOfRows);
        query.bindValue(":date",stringValues["data"]);
        query.bindValue(":bool",value);
        query.bindValue(":acurateteComenzi",floatValues["acuratete_preg_comenzi"]);
        query.bindValue(":rata_daune",floatValues["rata_daune"]);
        query.bindValue(":acuratete_stoc",floatValues["acuratete_stoc"]);
        query.bindValue(":grad_ocupare_depozit",floatValues["grad_ocupare_depozit"]);
        query.bindValue(":dso",floatValues["dso"]);
        query.bindValue(":dpo",floatValues["dpo"]);
       qDebug()<<query.exec();

        numOfRows++;
        db.close();





    //return 0;
}
int Table::deleteQuery(QString tableName, int index){
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(DATABASE_NAME);
        db.open();
        QString sql = "DELETE FROM " + tableName +" WHERE CRT= "+QVariant(index).toString() +";";
        QSqlQuery query;
        query.exec(sql);
        //numOfRows=tableSize(tableName);
        numOfRows--;
    }
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
    return 0;
}
void Table::decode(QString c)
{
    for(int i=0;i<19;i++)
        decod.text[i]="";
    for(int i=0;i<25;i++)
        decod.n[i]="";
    int i=0,k=1,l=0;
    while(c[i]!=',')
    {
        decod.text[0]+=c[i];
        i++;
    }
    i++;
    int size=c.size();
    for(;i<size;i++)
    {
        if(c[i]=='\'')
        {
            while(c[i]!=','&&i<size)
            {
                decod.text[k]+=c[i];
                i++;
            }
            k++;
        }
        else
        {
            while(c[i]!=','&&i<size)
            {
                decod.n[l]+=c[i];
                i++;
            }
            l++;
        }
    }
}

int Table::updateQuery(QString tableName, QString newRowValues, int index){
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(DATABASE_NAME);
        db.open();
        char b[6]="BUGET",p[9]="PERSONAL",r[7]="RUTIER",f[9]="FEROVIAR",d[11]="DEPOZITARE",m[8]="MARITIM",a[7]="AERIAN";
        int caz=0,i;
        for(i=0;i<5&&caz==0;i++)
            if(tableName[i]!=b[i])
                break;
        if(i==5)
            caz=1;
        for(i=0;i<8&&caz==0;i++)
            if(tableName[i]!=p[i])
                break;
        if(i==8)
            caz=2;
        for(i=0;i<6&&caz==0;i++)
            if(tableName[i]!=r[i])
                break;
        if(i==6)
            caz=3;
        for(i=0;i<8&&caz==0;i++)
            if(tableName[i]!=f[i])
                break;
        if(i==8)
            caz=4;
        for(i=0;i<10&&caz==0;i++)
            if(tableName[i]!=d[i])
                break;
        if(i==10)
            caz=5;
        for(i=0;i<7&&caz==0;i++)
            if(tableName[i]!=m[i])
                break;
        if(i==7)
            caz=6;
        for(i=0;i<6&&caz==0;i++)
            if(tableName[i]!=a[i])
                break;
        if(i==6)
            caz=7;
        if(caz==1)
        {
            decode(newRowValues);
            QString sql = "UPDATE "+tableName+" SET DATA = "+decod.text[0]+", BUGET = "+decod.n[0]+", CIFRA_AFACERI = "+decod.text[1]+", COST_CUMPARARE = "+decod.text[2]+", PERSONAL = "+decod.text[3]+", TEHNOLOGIE = "+decod.text[4]+", INFRASTRUCTURA = "+decod.text[5]+", INVESTITII = "+decod.text[6]+", COST_RUTIER = "+decod.text[7]+", COST_DEPOZITARE = "+decod.text[8]+", COST_MARITIM = "+decod.text[9]+", COST_AERIAN = "+decod.text[10]+", COST_FEROVIAR = "+decod.text[11]+" WHERE CRT = "+QVariant(index).toString()+";";
            qDebug()<<sql;
            QSqlQuery query;
            query.exec(sql);
        }
    }
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
    return 0;
}

void Table::readQuery(QString tableName, int dso){
    if (!db.isOpen()) {
        db.open();}
        if(db.isOpen())
        {
            QMessageBox msg;
            msg.setText("e deschis readu");//record.value("DATA").toString());
            msg.exec();
        }
        QSqlQuery query(db);

        query.prepare("SELECT * FROM  DEPOZITARE WHERE DSO =:dso ;");
       query.bindValue(":dso",(float)dso);
        qDebug()<<query.exec();

        while(query.next())
        {
            QSqlRecord record=query.record();
           // qDebug()<<"date*: "<<record.value("DATA").toString()<<endl;


        }

        /*QString tmp ="";
        int i=1;

        int n = query.record().count();
        while(query.next() && i<n-1){
        for( i=1; i<n; i++){
            if(query.record().value(i).type() == query.record().value(1).type()){
                if(i < n-1){
                    tmp = tmp + "'" + query.record().value(i).toString() +"',";
                }
                else{
                    tmp = tmp + "'" + query.record().value(i).toString() +"'";
                }            }
            else{
                if(i < n-1){
                    tmp = tmp + query.record().value(i).toString() +",";
                }
                else{
                    tmp = tmp + query.record().value(i).toString();
                }

            }

        }
        }
        qDebug()<<tmp;
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);

    return tmp;*/

    }
void Table::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE","procese.db");
    db.setDatabaseName(DATABASE_NAME);
    db.open();
}
