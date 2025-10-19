#include "serialport.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

SerialPort::SerialPort() {}

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

const QList<PortInfo>& SerialPort::getPortInfo() const noexcept
{
    return this->all_ports;
}

void SerialPort::slotUpdateSP()
{
    this->findAllPorts();
}

















