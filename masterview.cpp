#include "masterview.h"
#include "ui_masterview.h"
#include<QDebug>
#include"idatabase.h"
#include "medicineeditview.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    goLoginView();
    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}





void MasterView::goLoginView()
{
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);
    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));

}




void MasterView::goMedicineView()
{
    medicineView = new medicineview(this);
    pushWidgetToStackView(medicineView);
    connect(medicineView,SIGNAL(goMedicineEditView(int)),this,SLOT(goMedicineEditView(int)));


}


void MasterView::goMedicineEditView(int rowNo)
{
    medicineeditView = new medicineEditview(this,rowNo);
    pushWidgetToStackView(medicineeditView);
    connect(medicineeditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));

}


void MasterView::goPatientView()
{
    patientView = new patientview(this);
    pushWidgetToStackView(patientView);

    connect(patientView,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));

}

void MasterView::goPatientEditView(int rowNo)
{
    patienteditView = new patientEditview(this,rowNo);
    pushWidgetToStackView(patienteditView);
    connect(patienteditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));

}



void MasterView::goDoctorView()
{
    doctorView = new doctorview(this);
    pushWidgetToStackView(doctorView);
    connect(doctorView,SIGNAL(goDoctorEditView(int)),this,SLOT(goDoctorEditView(int)));

}

void MasterView::goDoctorEditView(int rowNo)
{
    doctoreditView = new doctorEditview(this,rowNo);
    pushWidgetToStackView(doctoreditView);
    connect(doctoreditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));

}

void MasterView::goWelcomeView()
{
    welcomeView = new Welcome(this);
    pushWidgetToStackView(welcomeView);

    connect(welcomeView,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeView,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeView,SIGNAL(goMedicineView()),this,SLOT(goMedicineView()));
}

void MasterView::goPreviousView()
{
    int count=ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-1);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count=ui->stackedWidget->count();
    if(count>1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);

    QString title=ui->stackedWidget->currentWidget()->windowTitle();
    if(title=="欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    }
    else{
        ui->btLogout->setEnabled(false);
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

