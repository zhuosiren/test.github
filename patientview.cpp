#include "patientview.h"
#include "ui_patientview.h"
#include"idatabase.h"
#include <QDebug>
#include <QFileDialog>


patientview::patientview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientview)
{
    ui->setupUi(this);


    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.PatientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }



    // 连接升序排序按钮的点击信号到对应的槽函数（假设界面上有一个名为btSortAscending的按钮）
    connect(ui->btSortAscending, &QPushButton::clicked, this, &patientview::on_btSortAscending_clicked);
    connect(ui->btSortAscending2, &QPushButton::clicked, this, &patientview::on_btSortAscending2_clicked);
}



patientview::~patientview()
{
    delete ui;
}

void patientview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


void patientview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchPatient(filter);
}


void patientview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void patientview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().thePatientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());

}




// 实现升序排序的槽函数
void patientview::on_btSortAscending_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    // 获取数据模型（这里假设名为DoctorTabModel，根据实际情况调整）
    QAbstractItemModel *model = iDatabase.PatientTabModel;
    if (model)
    {
        // 假设按照名为name的列进行升序排序，通过表头查找列名对应的索引
        int nameColumnIndex = -1;
        for (int i = 0; i < model->columnCount(); ++i)
        {
            if (model->headerData(i, Qt::Horizontal).toString() == "ID")
            {
                nameColumnIndex = i;
                break;
            }
        }
        if (nameColumnIndex >= 0)
        {
            // 对模型启用排序，按照指定列索引，升序（Qt::AscendingOrder）排序
            model->sort(nameColumnIndex, Qt::AscendingOrder);
            // 刷新视图显示排序后的结果（有些情况下可能不需要这一步，取决于模型和视图的关联机制，但加上更保险）
            ui->tableView->viewport()->update();
        }
        else
        {
            qDebug() << "找不到对应的列进行排序";
        }
    }
    else
    {
        qDebug() << "获取不到有效的数据模型进行排序操作";
    }
}



// 实现降序排序的槽函数，并添加同步数据库逻辑
void patientview::on_btSortAscending2_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    // 获取数据模型（这里假设名为DoctorTabModel，根据实际情况调整）
    QAbstractItemModel *model = iDatabase.PatientTabModel;
    if (model)
    {
        // 进行类型转换，假设实际为QSqlTableModel类型（根据实际模型类型调整）
        QSqlTableModel *sqlModel = qobject_cast<QSqlTableModel *>(model);
        if (sqlModel)
        {
            // 假设按照名为name的列进行降序排序，获取该列的索引（需根据实际表结构和列名来准确获取）
            int nameColumnIndex = sqlModel->record().indexOf("ID");
            if (nameColumnIndex >= 0)
            {
                // 对模型启用排序，按照指定列索引，降序（Qt::DescendingOrder）排序
                model->sort(nameColumnIndex, Qt::DescendingOrder);
                // 刷新视图显示排序后的结果（有些情况下可能不需要这一步，取决于模型和视图的关联机制，但加上更保险）
                ui->tableView->viewport()->update();

                // 尝试将排序后的结果同步回数据库
                if (sqlModel->submitAll())
                {
                    qDebug() << "排序结果已成功同步到数据库";
                }
                else
                {
                    qDebug() << "同步排序结果到数据库失败: " << sqlModel->lastError();
                }
            }
            else
            {
                qDebug() << "找不到对应的列进行排序";
            }
        }
        else
        {
            qDebug() << "实际模型类型不是预期的支持record函数的类型";
        }
    }
    else
    {
        qDebug() << "获取不到有效的数据模型进行排序操作";
    }
}



void patientview::on_btExport_clicked()
{
    // 弹出文件保存对话框，获取要导出的文件路径
    QString filePath = QFileDialog::getSaveFileName(this, tr("保存病人数据文件"), "", tr("文本文件 (*.txt);;CSV 文件 (*.csv)"));
    if (!filePath.isEmpty())
    {
        // 调用导出数据函数
        if (exportPatientData(filePath))
        {
            qDebug() << "医生数据导出成功";
        }
        else
        {
            qDebug() << "医生数据导出失败";
        }
    }
}

bool patientview::exportPatientData(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件: " << file.errorString();
        return false;
    }

    QTextStream out(&file);
    IDatabase &iDatabase = IDatabase::getInstance();
    // 获取数据模型（这里假设名为DoctorTabModel，根据实际情况调整）
    QAbstractItemModel *model = iDatabase.PatientTabModel;
    if (!model)
    {
        qDebug() << "获取不到有效的数据模型进行导出操作";
        file.close();
        return false;
    }

    // 假设模型是QSqlTableModel类型，获取表头数据作为文件的第一行
    QSqlTableModel *sqlModel = qobject_cast<QSqlTableModel *>(model);
    if (!sqlModel)
    {
        qDebug() << "实际模型类型不是预期的支持导出操作的类型";
        file.close();
        return false;
    }

    QSqlRecord record = sqlModel->record();
    QStringList fieldNames;
    for (int i = 0; i < record.count(); ++i)
    {
        fieldNames.append(record.fieldName(i));
    }
    out << fieldNames.join(',') << "\n";  // 将表头字段名写入文件，以逗号分隔

    // 遍历模型数据并写入文件
    for (int row = 0; row < sqlModel->rowCount(); ++row)
    {
        QStringList rowData;
        for (int col = 0; col < sqlModel->columnCount(); ++col)
        {
            QModelIndex index = sqlModel->index(row, col);
            rowData.append(index.data().toString());
        }
        out << rowData.join(',') << "\n";  // 将每行数据写入文件，以逗号分隔
    }

    file.close();
    return true;
}


// 导入按钮点击的槽函数实现，修改此处以支持选择.txt文件
void patientview::on_btImport_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择病人数据文件"), "", tr("文本文件 (*.txt);;CSV文件 (*.csv)"));
    if (!filePath.isEmpty())
    {
        if (importPatientData(filePath))
        {
            qDebug() << "医生数据导入成功";
        }
        else
        {
            qDebug() << "医生数据导入失败";
        }
    }
}

// 导入数据的具体函数实现，修改此处以适配.txt文件格式解析
bool patientview::importPatientData(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件: " << file.errorString();
        return false;
    }

    QTextStream in(&file);
    QStringList fieldNames;
    // 对于.txt文件，这里假设第一行是字段名，同样读取获取字段名（可根据实际情况调整是否有字段名行等）
    QString line = in.readLine();
    if (line.isEmpty())
    {
        qDebug() << "文件为空或格式错误";
        file.close();
        return false;
    }
    fieldNames = line.split(',');  // 假设.txt文件中数据以空格分隔，根据实际情况修改分隔符

    // 检查字段名是否符合要求
 QStringList requiredFields = QStringList() << "ID" << "ID_CARD" << "SEX" << "NAME" << "BOB" << "HEIGHT" << "WEIGHT" << "AGE" << "CREATEDTIMESTAMP" << "PHONE";
    foreach (const QString& requiredField, requiredFields)
    {
        if (!fieldNames.contains(requiredField))
        {
            qDebug() << "文件字段名不匹配，缺少 " << requiredField;
            file.close();
            return false;
        }
    }

    IDatabase &iDatabase = IDatabase::getInstance();
    // 获取数据模型
    QAbstractItemModel *model = iDatabase.PatientTabModel;
    if (!model)
    {
        qDebug() << "获取不到有效的数据模型进行导入操作";
        file.close();
        return false;
    }

    // 转换为QSqlTableModel类型
    QSqlTableModel *sqlModel = qobject_cast<QSqlTableModel *>(model);
    if (!sqlModel)
    {
        qDebug() << "实际模型类型不是预期的支持导入操作的类型";
        file.close();
        return false;
    }

    // 逐行读取数据并插入到数据库模型中
    while (!in.atEnd())
    {
        line = in.readLine();
        QStringList fields = line.split(',');  // 按照.txt文件的分隔符拆分每行数据，可按需修改
        if (fields.size()!= fieldNames.size())
        {
            qDebug() << "数据行格式错误";
            continue;
        }

        // 创建一个记录对象
        QSqlRecord record = sqlModel->record();
        for (int i = 0; i < fieldNames.size(); ++i)
        {
            QString fieldName = fieldNames[i];
            QString value = fields[i];
            // 根据不同字段进行数据类型处理和赋值，和之前类似，可根据实际数据库表字段类型完善
            if (fieldName == "ID")
            {
                bool ok;
                int id = value.toInt(&ok);
                if (ok)
                {
                    record.setValue(fieldName, id);
                }
                else
                {
                    qDebug() << "ID字段数据类型转换错误";
                    continue;
                }
            }
            else if (fieldName == "AGE")
            {
                bool ok;
                int age = value.toInt(&ok);
                if (ok)
                {
                    record.setValue(fieldName, age);
                }
                else
                {
                    qDebug() << "AGE字段数据类型转换错误";
                    continue;
                }
            }
            else if (fieldName == "NAME")
            {
                record.setValue(fieldName, value);
            }
            else if (fieldName == "SEX")
            {
                record.setValue(fieldName, value);
            }
            else if (fieldName == "DEPARTMENT_ID")
            {
                bool ok;
                int departmentId = value.toInt(&ok);
                if (ok)
                {
                    record.setValue(fieldName, departmentId);
                }
                else
                {
                    qDebug() << "DEPARTMENT_ID字段数据类型转换错误";
                    continue;
                }
            }
        }

        // 将记录插入到模型中
        if (!sqlModel->insertRecord(-1, record))
        {
            qDebug() << "插入数据失败: " << sqlModel->lastError();
        }
    }

    // 尝试将所有更改提交到数据库
    if (sqlModel->submitAll())
    {
        file.close();
        return true;
    }
    else
    {
        qDebug() << "提交数据到数据库失败: " << sqlModel->lastError();
        file.close();
        return false;
    }
}
