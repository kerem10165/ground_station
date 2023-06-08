#include <iostream>
#include "DebugWidget.h"
#include "ui_DebugWidget.h"


DebugWidget::DebugWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugWidget)
{
    ui->setupUi(this);
}

DebugWidget::~DebugWidget()
{
    delete ui;
}

void DebugWidget::debugValuesChange(DebugValues value)
{
    ui->countOfLopp->setValue(value.countOfLoop);
    ui->altitude->setValue(value.altitude);
    ui->desiredAltitude->setValue(value.desired_altitude);
    ui->pGain->setValue(value.p_gain_alt);
    ui->P->setValue(value.P_alt);
    ui->I->setValue(value.I_alt);
    ui->D->setValue(value.D_alt);
}
