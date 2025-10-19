#include "serialport.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

SerialPort::SerialPort() {}

void SerialPort::findAllPorts()
{
    const auto ports = QSerialPortInfo::availablePorts();
    all_ports.clear();

    for (const QSerialPortInfo &port : ports)
    {
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

}

const QList<SerialPort::PortInfo>& SerialPort::getPortInfo() const noexcept
{
    return this->all_ports;
}

















