#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QWidget>
#include <SendCommand.h>

namespace Ui {
class SerialController;
}

class SerialController : public QWidget
{
    Q_OBJECT
public:
    explicit SerialController(QWidget *parent = nullptr);
    ~SerialController();

    void createBaudAndSerialPort();

public slots:
    void openPort();
    void readTelemetry();
    void updatePorts();
    void sendCommandAndSettings(ReceiveInformations receiveInfo);
signals:
    void emitUpdateTelemetrySignal(QByteArray data);
private:
    Ui::SerialController *ui;
    QSerialPort serialPort;
    QSerialPortInfo info;
    QTimer* activeTimer{nullptr};
    QByteArray m_bytes;
};

#endif // SERIALCONTROLLER_H
