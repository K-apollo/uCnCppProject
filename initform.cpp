#include "initform.h"
#include "ui_initform.h"

InitForm::InitForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InitForm)
{
    ui->setupUi(this);
}

InitForm::~InitForm()
{
    delete ui;
}
