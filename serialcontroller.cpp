#include "serialcontroller.h"
#include "ui_serialcontroller.h"
#include <QTimer>
#include <iostream>

SerialController::SerialController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialController)
{
    ui->setupUi(this);
    createBaudAndSerialPort();

    activeTimer = new QTimer(this);
    activeTimer->setInterval(100);
    activeTimer->setSingleShot(true);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updatePorts()));
    activeTimer->start();
}


void SerialController::createBaudAndSerialPort()
{
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->com_ports->addItems(stringPorts);
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baud_rates->addItems(stringBaudRates);
    ui->baud_rates->setCurrentText("115200");
    connect(ui->openPort , &QPushButton::clicked , this , &SerialController::openPort);
    serialPort.open(QIODevice::ReadWrite);
}

void SerialController::openPort()
{
    serialPort.setPortName(ui->com_ports->currentText());
    serialPort.setBaudRate(ui->baud_rates->currentText().toInt());
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    serialPort.open(QIODevice::ReadWrite);

    if(!serialPort.isOpen()){
        abort();
    }

    connect(&serialPort,&QSerialPort::readyRead,this,&SerialController::readTelemetry);
}

void SerialController::readTelemetry()
{
    if (serialPort.canReadLine())
    {
        auto bytes = serialPort.readLine();
        const char *character = bytes.constData();

        if(bytes.size() == sizeof(SendInformations) + 4)
        {
            emit emitUpdateTelemetrySignal(bytes);
        }
        else if(character[0] == 'o' && character[1] == 'k')
        {
            m_bytes.clear();
            m_bytes.append(bytes);
        }
        else
        {
            m_bytes.append(bytes);
            if(m_bytes.size() == sizeof(SendInformations) + 4)
            {
                emit emitUpdateTelemetrySignal(m_bytes);
                m_bytes.clear();
            }
            else
                m_bytes.clear();
        }
    }
}

void SerialController::updatePorts()
{
    QList<QSerialPortInfo> ports = info.availablePorts();
    for(int i = 0 ; i < ports.size() ; i++)
    {
        if(ui->com_ports->findText(ports.at(i).portName()) == -1)
        {
            ui->com_ports->addItem(ports.at(i).portName());
        }
    }

    for(int i = 0 ; i < ui->com_ports->count(); i++)
    {
        auto str = ui->com_ports->itemText(i);

        int j = 0;
        for(; j < ports.count() ; j++)
        {
            if(str == ports.at(j).portName())
                break;
        }

        if(j == ports.count())
            ui->com_ports->removeItem(i);
    }

    activeTimer->start();
}

void SerialController::sendCommandAndSettings(ReceiveInformations receiveInfo)
{
    receiveInfo.start[0] = 'o';
    receiveInfo.start[1] = 'k';

    receiveInfo.end[0] = 'o';
    receiveInfo.end[1] = 'k';

    serialPort.write(reinterpret_cast<const char*>(&receiveInfo) , sizeof(receiveInfo));
}

SerialController::~SerialController()
{
    delete ui;
}
