#ifndef STUSQL_H
#define STUSQL_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
//定义学生结构体
struct stuInfo{
    int id;
    QString name;
    int age;
    int grade;
    int uiclass;
    int studentid;
    QString phone;
    QString wechat;
};
//定义用户结构体
struct userInfo{
    QString username;
    QString password;
    QString aut;
};

class stuSql : public QObject
{
    Q_OBJECT
public:
    static stuSql *ptrstuSql;
    static stuSql *getinstance()
    {
        if(nullptr==ptrstuSql)
        {
            ptrstuSql=new stuSql;
        }
        return  ptrstuSql;
    }
    explicit stuSql(QObject *parent = nullptr);
    void init();
    //查询所有学生数量
    int getStuCnt();
    //查询第几页学生数据
    QList<stuInfo> getPageStu(int page,int uiCnt);
    //增加学生
    bool addStu(stuInfo info);
    //删除学生
    bool delStu(int id);
    //清空学生表
    bool clearStuTable();
    //修改学生信息
    bool updateStuInfo(stuInfo info);
    //查询所有用户
    QList<userInfo> getAllUser();
    //查询用户名是否存在
    bool isExit(QString strUser);
    //更新用户信息
    bool updateUser(userInfo info);
    //添加单个用户
    bool addUser(userInfo info);
    //删除单个用户
    bool delUser(QString strUsername);
signals:
private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H
