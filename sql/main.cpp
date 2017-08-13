#include <QCoreApplication>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include<QtDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase qdb = QSqlDatabase::addDatabase("QPSQL");

     qdb.setHostName("localhost");
     qdb.setDatabaseName("fill");
     qdb.setUserName("postgres");
     qdb.setPassword("itonly");
     qdb.setPort(5432);

     if(qdb.open())
     {
        qDebug() << "Database connection successful!" ;
        QSqlQuery qry;
        if(qry.exec("SELECT * FROM users")){
            while(qry.next()){
                qDebug() << qry.value(1).toString();
            }
            QString query ="INSERT INTO public.users(id, nama)VALUES (:id, :name);";
            qry.prepare(query);
            qry.bindValue(":id",99);
            qry.bindValue(":name","handoko");
            if(qry.exec()){
                qDebug() << "Successfully Inserted";
            }

        }else{
             qDebug() << qdb.lastError().text();
        }
        qry.clear();
        qdb.close();
     }
     else
     {
        qDebug() << "Database connection not successful!" ;
     }

     qdb.close();

    return a.exec();
}
