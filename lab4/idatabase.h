#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>

#include <QtSql/QSqlTableModel>
#include <QtCore/Qt>

class IDatabase : public QObject
{
    Q_OBJECT
public:


    static IDatabase& getInstance()
    {
        static IDatabase  instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
        return instance;
    }

    QString userLogin(QString userName,QString password);



private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const&)               = delete;
    void operator=(IDatabase const&)  = delete;

    QSqlDatabase database;

    void ininDatabase();
public:
    bool initPatientModel();
    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    QSqlTableModel  *patientTabModel;          //数据模型
    QItemSelectionModel *thePatientSelection;	//选择模型


signals:

private:


};

#endif // IDATABASE_H
