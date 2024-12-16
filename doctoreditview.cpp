#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include"idatabase.h"

doctorEditview::doctorEditview(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::doctorEditview)
{
    ui->setupUi(this);


    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().DoctorTabModel;
    dataMapper->setModel(IDatabase::getInstance().DoctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->ID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->NAME,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->SEX,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->AGE,tabModel->fieldIndex("AGE"));
    dataMapper->addMapping(ui->PHONE,tabModel->fieldIndex("PHONE"));
    dataMapper->addMapping(ui->DEPARTMENT_ID,tabModel->fieldIndex("DEPARTMENT_ID"));
    dataMapper->setCurrentIndex(index);
}

doctorEditview::~doctorEditview()
{
    delete ui;
}


void doctorEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitDoctorEdit();
    emit goPreviousView();
}


void doctorEditview::on_btCancel_clicked()
{
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}
