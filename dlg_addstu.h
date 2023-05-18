#ifndef DLG_ADDSTU_H
#define DLG_ADDSTU_H

#include <QDialog>
#include "stusql.h"
namespace Ui {
class dlg_addStu;
}

class dlg_addStu : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_addStu(QWidget *parent = nullptr);
    ~dlg_addStu();
    bool m_isAdd;
    stuInfo m_info;
    void setType(bool isAdd,stuInfo info={});
private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::dlg_addStu *ui;
};

#endif // DLG_ADDSTU_H
