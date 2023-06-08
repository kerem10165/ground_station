#include "SetQuadParams.h"
#include "ui_SetQuadParams.h"

SetQuadParams::SetQuadParams(SerialController* serialController , QWidget *parent) :
    QWidget(parent), ui(new Ui::SetQuadParams) , m_serialController{serialController}
{
    ui->setupUi(this);
    connect(ui->sendAltitudePid , &QPushButton::clicked , this , &SetQuadParams::sendAltitudePid);
    connect(ui->sendRollAndPitchPid , &QPushButton::clicked , this , &SetQuadParams::sendRollAndPitchPid);
    connect(this , &SetQuadParams::sendCommand , m_serialController , &SerialController::sendCommandAndSettings);
}

SetQuadParams::~SetQuadParams()
{
    delete ui;
}

void SetQuadParams::settingCameSlot(SendInformations info)
{
    auto& setting = info.data.settings;

    ui->altitude_P->setValue(setting.altitudeP);
    ui->altitude_I->setValue(setting.altitudeI);
    ui->altitude_D->setValue(setting.altitudeD);

    ui->rollPitch_P->setValue(setting.rollAndPitchP);
    ui->rollPitch_I->setValue(setting.rollAndPitchI);
    ui->rollPitch_D->setValue(setting.rollAndPitchD);
}

void SetQuadParams::sendAltitudePid()
{
    ReceiveInformations receiveInfo;
    ReceiveInformation quadCommand;

    memset(&quadCommand , 0 , sizeof(quadCommand));

    quadCommand.altitudePid.altitudeP = ui->altitude_P_set->value();
    quadCommand.altitudePid.altitudeI = ui->altitude_I_set->value();
    quadCommand.altitudePid.altitudeD = ui->altitude_D_set->value();

    receiveInfo.data = quadCommand;
    receiveInfo.type = ReceiveType::ReceiveAltitudePidSetting;

    emit sendCommand(receiveInfo);
}

void SetQuadParams::sendRollAndPitchPid()
{
    ReceiveInformations receiveInfo;
    ReceiveInformation quadCommand;

    memset(&quadCommand , 0 , sizeof(quadCommand));

    quadCommand.attitudePid.rollAndPitchP = ui->rollAndPitch_P_set->value();
    quadCommand.attitudePid.rollAndPitchI = ui->rollAndPitch_I_set->value();
    quadCommand.attitudePid.rollAndPitchD = ui->rollAndPitch_D_set->value();

    receiveInfo.data = quadCommand;
    receiveInfo.type = ReceiveType::ReceiveAttitudePidSetting;

    emit sendCommand(receiveInfo);
}
