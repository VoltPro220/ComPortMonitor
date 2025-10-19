#include "serialport.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>



void SerialPort::findAllPorts()
{
    const auto ports = QSerialPortInfo::availablePorts();

    QList<PortInfo> newPorts;

    for (const QSerialPortInfo &port : ports) {
        PortInfo info;
        info.portName = port.portName();
        info.description = port.description();
        info.manufacturer = port.manufacturer();
        info.systemLocation = port.systemLocation();
        info.vendorId = port.hasVendorIdentifier() ? QString::number(port.vendorIdentifier(), 16) : "N/A";
        info.productId = port.hasProductIdentifier() ? QString::number(port.productIdentifier(), 16) : "N/A";

        newPorts.append(info);
    }

    if (all_ports != newPorts) {

        all_ports.clear();

        for (const QSerialPortInfo &port : ports) {
            qDebug() << "Port:" << port.portName();
            qDebug() << "Description:" << port.description();
            qDebug() << "Manufacturer:" << port.manufacturer();
            qDebug() << "System Location:" << port.systemLocation();
            qDebug() << "Vendor ID:" << port.vendorIdentifier();
            qDebug() << "Product ID:" << port.productIdentifier();
            qDebug() << "-----------------------------------";

            PortInfo info;
            info.portName = port.portName();
            info.description = port.description();
            info.manufacturer = port.manufacturer();
            info.systemLocation = port.systemLocation();
            info.vendorId = port.hasVendorIdentifier() ? QString::number(port.vendorIdentifier(), 16) : "N/A";
            info.productId = port.hasProductIdentifier() ? QString::number(port.productIdentifier(), 16) : "N/A";

            all_ports.append(info);
        }

        // Вызываем сигнал
        emit signalForUpdateCP(all_ports);

        qDebug() << "Список портов изменился, сигнал отправлен";
    } else {
        qDebug() << "Список портов не изменился";
    }

}

SerialPort::SerialPort()
{

};

SerialPort::~SerialPort()
{
    close();
}

void SerialPort::setSettings(COMPortSettings &settings)
{
    this->settings.setPortName(settings.portName());
    this->settings.setBaudRate(settings.baudRate());
    this->settings.setStopBits(settings.stopBits());
    this->settings.setDataBits(settings.dataBits());
    this->settings.setParity(settings.parity());
    this->settings.setFlowControl(settings.flowControl());
}

void SerialPort::startTimerForUpdateCP(quint16 period = 2000)
{
    this->period = period;
    m_portCheckTimer = new QTimer(this);

    connect(m_portCheckTimer, SIGNAL(timeout()), this, SLOT(slotUpdateSP()));

    m_portCheckTimer->start(this->period);

}

void SerialPort::stopTimerForIpdateCP()
{
    m_portCheckTimer->stop();
    disconnect(m_portCheckTimer, &QTimer::timeout, nullptr, nullptr);
}

bool SerialPort::open()
{

    m_serialPort = new QSerialPort;

    m_serialPort->setPortName(settings.portName());
    m_serialPort->setBaudRate(settings.baudRate());
    m_serialPort->setDataBits(settings.dataBits());
    m_serialPort->setParity(settings.parity());
    m_serialPort->setStopBits(settings.stopBits());
    m_serialPort->setFlowControl(settings.flowControl());

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Port opened successfully:" << settings.toString();
        return true;
    }

    else {
        delete m_serialPort;
        m_serialPort = nullptr;
        return false;
    }

}

void SerialPort::close()
{
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
        qDebug() << "Port closed";
    }

    if (m_serialPort) {
        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

bool SerialPort::isOpen() const
{
    return m_serialPort && m_serialPort->isOpen();
}

const QList<PortInfo>& SerialPort::getPortInfo() const noexcept
{
    return this->all_ports;
}

void SerialPort::slotUpdateSP()
{
    this->findAllPorts();
}

















