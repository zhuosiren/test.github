#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class doctorview;
}

class doctorview : public QWidget
{
    Q_OBJECT

public:
    explicit doctorview(QWidget *parent = nullptr);
    ~doctorview();

private slots:
    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btAdd_clicked();

private:
    Ui::doctorview *ui;
    QDataWidgetMapper *dataMapper;

};

#endif // DOCTORVIEW_H
