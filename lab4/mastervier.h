#ifndef MASTERVIER_H
#define MASTERVIER_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "welcomeview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterVier;
}
QT_END_NAMESPACE

class MasterVier : public QWidget
{
    Q_OBJECT

public:
    MasterVier(QWidget *parent = nullptr);
    ~MasterVier();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView();
    void goPatientView();
    void goPreviousView();


private slots:
    void on_btnBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:

    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterVier *ui;

    WelcomeView *welcomeview;
    DoctorView *doctorView;
    PatientView *patientView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientEditView *patientEditView;





};
#endif // MASTERVIER_H
