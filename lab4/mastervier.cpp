#include "mastervier.h"
#include "ui_mastervier.h"

MasterVier::MasterVier(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterVier)
{
    ui->setupUi(this);
}

MasterVier::~MasterVier()
{
    delete ui;
}
