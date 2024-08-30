#include "nextform.h"
#include "ui_nextform.h"

NextForm::NextForm(QWidget *parent):
    QWidget(parent),
    ui(new Ui::NextForm)
{
    ui->setupUi(this);
}

NextForm::~NextForm()
{
    delete ui;
}
