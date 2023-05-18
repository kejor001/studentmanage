#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page_login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);
    m_dlgLogin.show();
    //    connect(m_dlgLogin,&page_login::sendLoginSuccess,[=](){
    //        this->show();
    //    });
    connect(&m_dlgLogin,&page_login::sendLoginSuccess,[=](){
        this->show();
    });
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    QStringList l;
    l<<"学生管理信息系统";
    QTreeWidgetItem *pf= new QTreeWidgetItem(ui->treeWidget,l);
    l.clear();
    l<<"学生管理";
    QTreeWidgetItem *p1= new QTreeWidgetItem(pf,l);
    l.clear();
    l<<"管理员管理";
    QTreeWidgetItem *p2= new QTreeWidgetItem(pf,l);
    ui->treeWidget->addTopLevelItem(pf);
    pf->addChild(p1);
    pf->addChild(p2);
    ui->treeWidget->expandAll();
    ui->stackedWidget->setCurrentIndex(0);
    m_ptrStuSql =stuSql::getinstance();
    m_ptrStuSql->init();
    updateInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_moni_clicked()
{
    for(int i=0;i<100;i++)
    {
        stuInfo info;
        if(i%3)
        {
            info.name=QString("张%1").arg(i);
            info.age=13;
        }
        if(i%2)
        {
            info.name=QString("王%1").arg(i);
            info.age=12;
        }
        if(i%7)
        {
            info.name=QString("李%1").arg(i);
            info.age=17;
        }
        info.grade=1;
        info.uiclass=2;
        info.studentid=2109;
        info.phone="1100";
        info.wechat="foobarbaz";
        m_ptrStuSql->addStu(info);
    }
    updateInfo();
}

void MainWindow::on_btn_add_clicked()
{
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();
    updateInfo();
}

void MainWindow::on_btn_clear_clicked()
{
    m_ptrStuSql->clearStuTable();
    updateInfo();
}

void MainWindow::updateInfo()
{
    auto cnt=m_ptrStuSql->getStuCnt();

    QList<stuInfo> lStudents=m_ptrStuSql->getPageStu(0,cnt);
    ui->lb_cnt->setText(QString("数量%1").arg(cnt));
    ui->tableWidget->setRowCount(cnt);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<lStudents.size();i++)
    {
        //ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].wechat));

    }
}

void MainWindow::on_btn_exit_clicked()
{
//    this->hide();
    exit(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    int i =ui->tableWidget->currentRow();
    if(i>=0)
    {
        int id=ui->tableWidget->item(i,0)->text().toUInt();
        m_ptrStuSql->delStu(id);
        updateInfo();
        QMessageBox::information(this,"信息","删除成功");
    }
}

void MainWindow::on_btn_update_clicked()
{
    stuInfo info;
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
        info.id=ui->tableWidget->item(i,1)->text().toUInt();
        info.name=ui->tableWidget->item(i,2)->text();
        info.age=ui->tableWidget->item(i,3)->text().toUInt();
        info.grade=ui->tableWidget->item(i,4)->text().toUInt();
        info.uiclass=ui->tableWidget->item(i,5)->text().toUInt();
        info.studentid=ui->tableWidget->item(i,6)->text().toUInt();
        info.phone=ui->tableWidget->item(i,7)->text();
        info.wechat=ui->tableWidget->item(i,8)->text();
        m_dlgAddStu.setType(false,info);
        m_dlgAddStu.exec();
    }
    updateInfo();
}

void MainWindow::on_btn_search_clicked()
{
    auto cnt=m_ptrStuSql->getStuCnt();
    QList<stuInfo> lStudents=m_ptrStuSql->getPageStu(0,cnt);
    ui->lb_cnt->setText(QString("数量%1").arg(cnt));
    QString strFilter=ui->le_search->text();
    ui->tableWidget->setRowCount(cnt);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int index=1;
    for(int i=0;i<lStudents.size();i++)
    {
        if(!lStudents[i].name.contains(strFilter))
        {
            continue;
        }
        index++;
        //ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(index)));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].wechat));

    }
}
