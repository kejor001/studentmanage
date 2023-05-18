#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page_login.h"
#include "stusql.h"
#include "dlg_addstu.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    page_login m_dlgLogin;
    stuSql *m_ptrStuSql;
    dlg_addStu m_dlgAddStu;
private slots:
    void on_btn_moni_clicked();

    void on_btn_add_clicked();

    void on_btn_clear_clicked();
    void on_btn_exit_clicked();

    void on_pushButton_4_clicked();

    void on_btn_update_clicked();

    void on_btn_search_clicked();

private:
    void updateInfo();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
