#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>

namespace Ui {
class patientview;
}

class patientview : public QWidget
{
    Q_OBJECT

public:
    explicit patientview(QWidget *parent = nullptr);
    ~patientview();

private slots:
    void on_btAdd_clicked();


    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btSortAscending_clicked();

    void on_btSortAscending2_clicked();

    // 新增导出按钮点击的槽函数声明
    void on_btExport_clicked();
    // 导出数据的函数声明
    bool exportPatientData(const QString& filePath);

    // 新增导入按钮点击的槽函数声明
    void on_btImport_clicked();
    // 导入数据的函数声明
    bool importPatientData(const QString& filePath);

signals:
    void goPatientEditView(int idx);

private:
    Ui::patientview *ui;
};

#endif // PATIENTVIEW_H
