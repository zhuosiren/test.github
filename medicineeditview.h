#ifndef MEDICINEEDITVIEW_H
#define MEDICINEEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>

namespace Ui {
class medicineEditview;
}

class medicineEditview : public QWidget
{
    Q_OBJECT

public:
    explicit medicineEditview(QWidget *parent = nullptr, int index=0);
    ~medicineEditview();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();




private:
    Ui::medicineEditview *ui;
    QDataWidgetMapper *dataMapper;


signals:
    void goPreviousView();

};




#endif // MEDICINEEDITVIEW_H
