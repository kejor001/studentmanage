#include "page_login.h"
#include "ui_page_login.h"

page_login::page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_login)
{
    ui->setupUi(this);
}

page_login::~page_login()
{
    delete ui;
}

void page_login::on_btn_login_clicked()
{
    //数据库查找用户名和密码
    //失败就提示
    //成功进入主界面
    emit sendLoginSuccess();
    this->hide();
}

void page_login::on_btn_exit_clicked()
{
    //退出登录
    exit(0);
}
