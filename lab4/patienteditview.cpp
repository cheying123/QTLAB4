#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>
#include "idatabase.h"


PatientEditView::PatientEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper= new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);		//设置数据模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); //数据更新方式
    //界面组件与数据模型的具体字段之间的联系
    dataMapper->addMapping(ui->dbEditId,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDataEditDOB,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreateTimeStamp,tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().submitPatientEdit();
    emit goPreviousView();

}


void PatientEditView::on_pushButton_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();

}

