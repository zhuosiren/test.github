#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>

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

    void on_pushButton_clicked();

    void on_btSortAscending_clicked();


    void on_btSortAscending2_clicked();

    // 新增导出按钮点击的槽函数声明
    void on_btExport_clicked();
    // 导出数据的函数声明
    bool exportDoctorData(const QString& filePath);

    // 新增导入按钮点击的槽函数声明
    void on_btImport_clicked();
    // 导入数据的函数声明
    bool importDoctorData(const QString& filePath);

signals:
    void goDoctorEditView(int idx);


private:
    Ui::doctorview *ui;

};

#endif // DOCTORVIEW_H
