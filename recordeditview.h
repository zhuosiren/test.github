#ifndef RECORDEDITVIEW_H
#define RECORDEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
namespace Ui {
class recordEditview;
}

class recordEditview : public QWidget
{
    Q_OBJECT

public:
    explicit recordEditview(QWidget *parent = nullptr, int index = 0);
    ~recordEditview();

private slots:
    void on_btSave_clicked();
    void on_btCancel_clicked();

private:
    Ui::recordEditview *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // RECORDEDITVIEW_H
