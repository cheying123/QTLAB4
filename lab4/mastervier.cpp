#include "mastervier.h"
#include "ui_mastervier.h"
#include <QDebug>

MasterVier::MasterVier(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterVier)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();
}

MasterVier::~MasterVier()
{
    delete ui;
}

void MasterVier::goLoginView()
{
    qDebug() << "MY GO";
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);

    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));

}

void MasterVier::goWelcomeView()
{
    welcomeview = new WelcomeView(this);
    pushWidgetToStackView(welcomeview);

    connect(welcomeview,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeview,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeview,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));

}

void MasterVier::goDoctorView()
{
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);

}

void MasterVier::goDepartmentView()
{
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);

}

void MasterVier::goPatientEditView()
{
    patientEditView = new PatientEditView(this);
    pushWidgetToStackView(patientEditView);
}



void MasterVier::goPatientView()
{
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);

    connect(patientView,SIGNAL(goPatientEditView()),this,SLOT(goPatientEditView()));
}



void MasterVier::goPreviousView()
{
    int count = ui -> stackedWidget->count();

    if( count > 1 ){
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterVier::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui -> stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); //总是显示最新的页面
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterVier::on_btnBack_clicked()
{
    goPreviousView();
}


void MasterVier::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui ->stackedWidget->count();
    if( count > 1 ){
        ui->btnBack->setEnabled(true);
    }else{
        ui->btnBack->setEnabled(false);
    }

    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    if( title == "登录窗口" ){
        ui->btLogout->setEnabled(false);
        ui->btnBack->setEnabled(false);
    }

    if( title == "欢迎" ){
        ui->btLogout->setEnabled(true);
        ui->btnBack->setEnabled(false);
    }else{
        ui->btLogout->setEnabled(false);
    }


}


void MasterVier::on_btLogout_clicked()
{
    goPreviousView();
}

