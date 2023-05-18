#include "mainwindow.h"
#include "page_login.h"
#include <QApplication>
#include "stusql.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlError>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setWindowTitle("学生管理系统");
//    w.show();
    stuSql sql;
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("localhost");
//    db.setPort(3306);
//    db.setDatabaseName("studentmanage");
//    db.setUserName("root");
//    db.setPassword("root");
//    bool ok = db.open();
//    if (ok){
//        qDebug()<<"okkkkkkkkkk";
//    }
//    else {

//        qDebug()<<"error open database because"<<db.lastError().text();
//    }
//    QSqlQuery qu;
//qu.exec("insert into student (id,name,age,grade,class,studentid,phone,wechat) values (2,'qt创建数据',19,4,2,2102,'1100','1200');");
    return a.exec();
}
