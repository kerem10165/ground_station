
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <SendCommand.h>
#include <serialcontroller.h>
#include <unordered_map>
#include <string_view>
#include "DebugWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void locationChageFromMap(QVariant coordinate);
    void updateTelemetryData(QByteArray data);
    void openParamSetMenu();
    void setQuadAltitudeButton();
signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
    void settingInfoCameSignal(SendInformations info);
    void sendCommand(ReceiveInformations quadCommand);
#if DEBUG_ == 1
    void debugValuesChangeSignal(DebugValues value);
#endif
private:
    void connectSignalsAndEmit();
    void createBaudAndSerialPort();
private:
    Ui::MainWindow *ui;
    DebugWidget* debugWidget;
    SerialController* serialController;
    SendInformations cameFromQuad;
    static const std::unordered_map<Command , QString> enumToName;
};

#endif // MAINWINDOW_H
