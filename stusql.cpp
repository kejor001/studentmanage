#include "stusql.h"
#include <QCoreApplication>

stuSql * stuSql::ptrstuSql=nullptr;
stuSql::stuSql(QObject *parent) : QObject(parent)
{
    //init();
//    stuInfo s;
//    s.name="bar";
//    s.age=18;
//    s.grade=3;
//    s.phone="110";
//    s.wechat="119";
//    s.uiclass=1;
//    s.studentid=2109;
    //    for(int i=0;i<3;i++)
    //    {
    //        addStu(s);
    //    }
    getStuCnt();
    getPageStu(2,2);
    //delStu(5);
    stuInfo s;
    s.name="fuck you";
    s.id=9;
    updateStuInfo(s);
}

void stuSql::init()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setDatabaseName("studentmanage");
    m_db.setUserName("root");
    m_db.setPassword("root");
    bool ok = m_db.open();
    auto str=QCoreApplication::applicationDirPath();

    if (ok){
        qDebug()<<"mysql connect success";
    }
    else {

        qDebug()<<"error open database because"<<m_db.lastError().text();
    }
}

int stuSql::getStuCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from student;");
    int flag=0;
    while(sql.next())
    {
        flag=sql.value(0).toUInt();
    }
    return  flag;
}

QList<stuInfo> stuSql::getPageStu(int page, int uiCnt)
{
    QList<stuInfo> l;
    QSqlQuery sql(m_db);
    QString strSql=QString("select * from student order by id limit %1 offset %2;").arg(uiCnt).arg(page*uiCnt);
    sql.exec(strSql);
    stuInfo info;
    while (sql.next()) {
        info.id=sql.value(0).toUInt();
        info.name=sql.value(1).toString();
        info.age=sql.value(2).toUInt();
        info.grade=sql.value(3).toUInt();
        info.uiclass=sql.value(4).toUInt();
        info.studentid=sql.value(5).toUInt();
        info.phone=sql.value(6).toString();
        info.wechat=sql.value(7).toString();
        l.push_back(info);
    }
    return l;
}

bool stuSql::addStu(stuInfo info)
{
    QSqlQuery sql1;
    QString strSql=QString("insert into student (id,name,age,grade,class,studentid,phone,wechat) values (null,'%1',%2,%3,%4,%5,'%6','%7');").
                     arg(info.name).arg(info.age).arg(info.grade).
                     arg(info.uiclass).arg(info.studentid).arg(info.phone).arg(info.wechat);
    sql1.exec(strSql);
    //sql1.exec("insert into student (id,name,age,grade,class,studentid,phone,wechat) values (3,'qt创建数据2',19,4,2,2102,'1100','1200');");
    return  true;
}

bool stuSql::delStu(int id)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from student where id=%1;").arg(id));
}

bool stuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    sql.exec("delete from student;");
    return sql.exec("alter table student AUTO_INCREMENT=0;");
}

bool stuSql::updateStuInfo(stuInfo info)
{
    QSqlQuery sql1(m_db);
    QString strSql=QString("update student set name='%1',age=%2,grade=%3,class=%4,studentid=%5,phone='%6',wechat='%7' where id =%8;").
                     arg(info.name).arg(info.age).arg(info.grade).
                     arg(info.uiclass).arg(info.studentid).arg(info.phone).arg(info.wechat).arg(info.id);
    return sql1.exec(strSql);
}

QList<userInfo> stuSql::getAllUser()
{
    QList<userInfo> l;
    QSqlQuery sql(m_db);
    sql.exec("select * from username;");
    userInfo info;
    while (sql.next()) {
        info.username=sql.value(0).toString();
        info.password=sql.value(1).toString();
        info.aut=sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool stuSql::isExit(QString strUser)
{
    QSqlQuery sql(m_db);
    sql.exec(QString("select * from usernmae where username='%1';").arg(strUser));
    return sql.next();
}

bool stuSql::updateUser(userInfo info)
{
    QSqlQuery sql1(m_db);
    QString strSql=QString("update username set password='%1',auth='%2' where username='%3';").
                     arg(info.password).arg(info.aut).arg(info.username);
    return sql1.exec(strSql);
}

bool stuSql::addUser(userInfo info)
{
    QSqlQuery sql1;
    QString strSql=QString("insert into username (username,password,aut) values ('%1','%2','%3');").
                     arg(info.username).arg(info.password).arg(info.aut);
    return sql1.exec(strSql);
}

bool stuSql::delUser(QString strUsername)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from username where username='%1';").arg(strUsername));
}
