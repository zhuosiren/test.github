#include "patienteditview.h"
#include "ui_patienteditview.h"
#include"idatabase.h"

patientEditview::patientEditview(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::patientEditview)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().PatientTabModel;
    dataMapper->setModel(IDatabase::getInstance().PatientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->editID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->editName,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->comboBox,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->editIDcard,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->editPhone,tabModel->fieldIndex("PHONE"));
    dataMapper->addMapping(ui->spinHeight,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->spinWeight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->EditCreateTime,tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);
}

patientEditview::~patientEditview()
{
    delete ui;
}

void patientEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitPatientEdit();
    emit goPreviousView();
}


void patientEditview::on_btCancel_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}

