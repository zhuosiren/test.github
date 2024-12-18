#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include"doctorview.h"
#include"medicineview.h"
#include"medicineeditview.h"
#include"loginview.h"
#include"patientview.h"
#include"patienteditview.h"
#include"welcomeview.h"
#include"doctoreditview.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();
public slots:
    void goMedicineView();
    void goDoctorView();
    void goLoginView();
    void goPatientView();
    void goPatientEditView(int rowNo);
    void goDoctorEditView(int rowNo);
    void goMedicineEditView(int rowNo);
    void goWelcomeView();
    void goPreviousView();


private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:

    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;


    Welcome *welcomeView;
    doctorview *doctorView;
    doctorEditview *doctoreditView;
    LoginView *loginView;
    patientEditview *patienteditView;
    medicineview *medicineView;
    medicineEditview *medicineeditView;
    patientview *patientView;



};
#endif // MASTERVIEW_H
