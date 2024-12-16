#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class doctorEditview;
}

class doctorEditview : public QWidget
{
    Q_OBJECT

public:
    explicit doctorEditview(QWidget *parent = nullptr,int index=0);
    ~doctorEditview();


private slots:
    void on_btSave_clicked();
    void on_btCancel_clicked();

signals:
    void goPreviousView();



private:
    Ui::doctorEditview *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // DOCTOREDITVIEW_H
