#include "medicineeditview.h"
#include "ui_medicineeditview.h"
#include"idatabase.h"

medicineEditview::medicineEditview(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::medicineEditview)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().MedicineTabModel;
    dataMapper->setModel(IDatabase::getInstance().MedicineTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->ID,tabModel->fieldIndex("medicine_name"));
    dataMapper->addMapping(ui->NAME,tabModel->fieldIndex("dosage"));
    dataMapper->addMapping(ui->DEPARTMENT_ID,tabModel->fieldIndex("inventory"));
    dataMapper->setCurrentIndex(index);
}

medicineEditview::~medicineEditview()
{
    delete ui;
}

void medicineEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitMedicineEdit();
    emit goPreviousView();
}


void medicineEditview::on_btCancel_clicked()
{
    IDatabase::getInstance().revertMedicineEdit();
    emit goPreviousView();
}
