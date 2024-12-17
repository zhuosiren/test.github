#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class patientEditview;
}

class patientEditview : public QWidget
{
    Q_OBJECT

public:
    explicit patientEditview(QWidget *parent = nullptr,int index=0);
    ~patientEditview();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::patientEditview *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // PATIENTEDITVIEW_H
