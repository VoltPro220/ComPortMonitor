#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtSerialPort/QSerialPort>

class SerialPort
{
    struct PortInfo {
        QString portName;
        QString description;
        QString manufacturer;
        QString systemLocation;
        QString vendorId;
        QString productId;
    };

    QList<PortInfo> all_ports;

public:
    SerialPort();
    void findAllPorts();

    const QList<PortInfo>& getPortInfo() const noexcept;

};


#endif // SERIALPORT_H
