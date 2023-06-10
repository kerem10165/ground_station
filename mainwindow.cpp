#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickItem>
#include <QGeoCoordinate>
#include <iostream>
#include <QPushButton>
#include <SetQuadParams.h>
const std::unordered_map<Command , QString> MainWindow::enumToName
{
        {Command::fly_joyistick , "Fly With Joyistic"},
        {Command::set_altitude , "Set Altitude"},
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , debugWidget{nullptr}
{
    ui->setupUi(this);
    serialController = ui->serial_control;

#if DEBUG_ == 1
    debugWidget = new DebugWidget;
    ui->DebugWidget->layout()->addWidget(debugWidget);
    connect(this , &MainWindow::debugValuesChangeSignal , debugWidget , &DebugWidget::debugValuesChange);
#endif
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    connectSignalsAndEmit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalsAndEmit()
{
    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(changeMarkerLocation(QVariant, QVariant)), obj, SLOT(changeMarkerLocation(QVariant, QVariant)));
    connect(obj, SIGNAL(locationChangeSignal(QVariant)), this, SLOT(locationChageFromMap(QVariant)));
    connect(serialController , &SerialController::emitUpdateTelemetrySignal , this , &MainWindow::updateTelemetryData);
    connect(ui->setQuadParams, &QPushButton::clicked , this , &MainWindow::openParamSetMenu);
    connect(ui->setQuadAlt , &QPushButton::clicked , this , &MainWindow::setQuadAltitudeButton);
    connect(this , &MainWindow::sendCommand , serialController , &SerialController::sendCommandAndSettings);
    emit changeMarkerLocation(0, 0);
}

void MainWindow::locationChageFromMap(QVariant coordinate)
{
    auto loc = coordinate.value<QGeoCoordinate>();

    std::cout << loc.latitude() << " - " << loc.longitude() << std::endl;
}

void MainWindow::updateTelemetryData(QByteArray data)
{
    memcpy(&cameFromQuad , data.constData() + 2 , sizeof(cameFromQuad));

    if(cameFromQuad.sendType == SendType::Info)
    {
        ui->alt_info->setValue(cameFromQuad.data.status.altitude);
        ui->roll_info->setValue(cameFromQuad.data.status.roll);
        ui->pitch_info->setValue(cameFromQuad.data.status.pitch);
        ui->yaw_info->setValue(cameFromQuad.data.status.yaw);
        ui->satellite_info->setValue(cameFromQuad.data.status.satelliteCount);
        ui->lat_info->setValue(cameFromQuad.data.status.latitude);
        ui->lon_info->setValue(cameFromQuad.data.status.longtitude);

        if(static_cast<int>(cameFromQuad.data.status.latitude) != 0)
        {
            emit changeMarkerLocation(cameFromQuad.data.status.latitude, cameFromQuad.data.status.longtitude);
        }
#if DEBUG_ == 1
        auto diff = cameFromQuad.data.status.debug.altitude - cameFromQuad.data.status.altitude;
        cameFromQuad.data.status.debug.altitude-=diff;
        cameFromQuad.data.status.debug.desired_altitude-=diff;
        emit debugValuesChangeSignal(cameFromQuad.data.status.debug);
#endif

        ui->status_info->setText("Status : " + enumToName.at(cameFromQuad.data.status.status));
    }

    else if(cameFromQuad.sendType == SendType::Settings)
    {
        emit settingInfoCameSignal(cameFromQuad);
    }
}

void MainWindow::openParamSetMenu()
{
    auto ptr = new SetQuadParams(serialController);
    connect(this , &MainWindow::settingInfoCameSignal , ptr , &SetQuadParams::settingCameSlot);
    ptr->show();
}

void MainWindow::setQuadAltitudeButton()
{
    ReceiveInformations receiveInfo;
    ReceiveInformation quadCommand;

    memset(&quadCommand , 0 , sizeof(quadCommand));


    quadCommand.receiveCommand.command = Command::set_altitude;
    quadCommand.receiveCommand.altitude = ui->altSet->value();

    receiveInfo.data = quadCommand;
    receiveInfo.type = ReceiveType::ReceiveData;

    emit sendCommand(receiveInfo);
}



