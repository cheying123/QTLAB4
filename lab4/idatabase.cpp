#include "idatabase.h"

void IDatabase::ininDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");  //添加 SQLITE数据库驱动
    QString aFile="D:/QT-git/lab4a.db";
    database.setDatabaseName(aFile);   //设置数据库文件


    if(!database.open()){
        qDebug() << "打开数据库失败";
    }else{
        qDebug() << "打开数据库成功";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);	//数据保存方式，OnManualSubmit , OnRowChange
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder); //排序

    if (!(patientTabModel->select()))	//查询数据失败
    {
        return false;
    }

    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;


}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),
                               QModelIndex());
    QModelIndex curIndex=patientTabModel->index(patientTabModel->rowCount()-1,
                                           1); //创建最后一行的ModelIndex
    return curIndex.row();

}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();

}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{

    QSqlQuery query;    //查询用户数据
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    if(query.first() && query.value("username").isValid()){
        QString passwd = query.value("password").toString();
        if( passwd == password ){
            return "loginOK";
        }else{
            qDebug() << "密码错误";
            return "wrongPassword";
        }
    }else{
        qDebug()<<"用户名输入不正确";
        return "loginFailed";
    }

}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
