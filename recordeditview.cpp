#include "recordeditview.h"
#include "ui_recordeditview.h"
#include "idatabase.h"

recordEditview::recordEditview(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::recordEditview)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().RecordTabModel;
    dataMapper->setModel(IDatabase::getInstance().RecordTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->patient_name, tabModel->fieldIndex("patient_name"));
    dataMapper->addMapping(ui->doctor_name, tabModel->fieldIndex("doctor_name"));
    dataMapper->addMapping(ui->editdate, tabModel->fieldIndex("date"));
    dataMapper->addMapping(ui->result, tabModel->fieldIndex("result"));
    dataMapper->addMapping(ui->medicine_name, tabModel->fieldIndex("medicine_name"));
    dataMapper->setCurrentIndex(index);
}

recordEditview::~recordEditview()
{
    delete ui;
}

void recordEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitRecordEdit();
    emit goPreviousView();
}


void recordEditview::on_btCancel_clicked()
{
    IDatabase::getInstance().revertRecordEdit();
    emit goPreviousView();
}
