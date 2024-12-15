#include "doctorview.h"
#include "ui_doctorview.h"
#include"idatabase.h"

doctorview::doctorview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::doctorview)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initDoctorModel()){
        ui->tableView->setModel(iDatabase.DoctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);
    }

}

doctorview::~doctorview()
{
    delete ui;
}

void doctorview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchDoctor(filter);
}

void doctorview::on_btDelete_clicked()
{
     IDatabase::getInstance().deleteCurrentDoctor();
}


void doctorview::on_btEdit_clicked()
{

}


// void doctorview::on_btAdd_clicked()
// {
//     emit goDoctorEditView();
// }


void doctorview::on_btAdd_clicked()
{

}

