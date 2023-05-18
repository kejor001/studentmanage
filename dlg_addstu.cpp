#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include "stusql.h"
#include <QMessageBox>
dlg_addStu::dlg_addStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlg_addStu)
{
    ui->setupUi(this);
}

dlg_addStu::~dlg_addStu()
{
    delete ui;
}
void dlg_addStu::setType(bool isAdd,stuInfo info)
{
    m_isAdd=isAdd;
    m_info=info;
    ui->le_name->setText(info.name);
    ui->sb_age->setValue(info.age);
    ui->le_class->setText(QString::number(info.uiclass));
    ui->le_grade->setText(QString::number(info.grade));
    ui->le_phone->setText(info.phone);
    ui->le_wechat->setText(info.wechat);
}

void dlg_addStu::on_btn_save_clicked()
{
    stuInfo info;
    auto ptr=stuSql::getinstance();
    info.name=ui->le_name->text();
    info.age=ui->sb_age->text().toUInt();
    info.uiclass=ui->le_class->text().toUInt();
    info.grade=ui->le_grade->text().toUInt();
    info.phone=ui->le_phone->text();
    info.wechat=ui->le_wechat->text();
    ptr->addStu(info);
    QMessageBox::information(this,"信息","存储成功");
    this->hide();
}

void dlg_addStu::on_btn_cancel_clicked()
{
    this->hide();
}
