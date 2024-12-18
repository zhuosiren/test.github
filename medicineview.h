#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QWidget>

namespace Ui {
class medicineview;
}

class medicineview : public QWidget
{
    Q_OBJECT

public:
    explicit medicineview(QWidget *parent = nullptr);
    ~medicineview();


private slots:
    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btAdd_clicked();

    void on_pushButton_clicked();

    void on_btSortAscending_clicked();

    void on_btSortAscending2_clicked();

    // 新增导出按钮点击的槽函数声明
    void on_btExport_clicked();
    // 导出数据的函数声明
    bool exportMedicineData(const QString& filePath);

    // 新增导入按钮点击的槽函数声明
    void on_btImport_clicked();
    // 导入数据的函数声明
    bool importMedicineData(const QString& filePath);

signals:
    void goMedicineEditView(int idx);









private:
    Ui::medicineview *ui;
};

#endif // MEDICINEVIEW_H
