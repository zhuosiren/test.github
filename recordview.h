#ifndef RECORDVIEW_H
#define RECORDVIEW_H

#include <QWidget>

namespace Ui {
class recordview;
}

class recordview : public QWidget
{
    Q_OBJECT

public:
    explicit recordview(QWidget *parent = nullptr);
    ~recordview();

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
    bool exportRecordData(const QString& filePath);

    // 新增导入按钮点击的槽函数声明
    void on_btImport_clicked();
    // 导入数据的函数声明
    bool importRecordData(const QString& filePath);




signals:
    void goRecordEditView(int idx);


private:
    Ui::recordview *ui;


};

#endif // RECORDVIEW_H
