#include "serialport.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent)
    , m_serialPort(nullptr)
    , m_portCheckTimer(nullptr)
    , period(2000)
{
}

SerialPort::~SerialPort()
{
    close();
}

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

    // Сравниваем содержимое списков, а не сами объекты
    bool listsAreEqual = (all_ports.size() == newPorts.size());
    if (listsAreEqual) {
        for (int i = 0; i < all_ports.size(); ++i) {
            if (all_ports[i].portName != newPorts[i].portName ||
                all_ports[i].description != newPorts[i].description) {
                listsAreEqual = false;
                break;
            }
        }
    }

    if (!listsAreEqual) {
        all_ports = newPorts;

        for (const PortInfo &info : all_ports) {
            qDebug() << "Port:" << info.portName;
            qDebug() << "Description:" << info.description;
            qDebug() << "Manufacturer:" << info.manufacturer;
            qDebug() << "System Location:" << info.systemLocation;
            qDebug() << "Vendor ID:" << info.vendorId;
            qDebug() << "Product ID:" << info.productId;
            qDebug() << "-----------------------------------";
        }

        emit signalForUpdateCP(all_ports);
        qDebug() << "Список портов изменился, сигнал отправлен";
    } else {
        qDebug() << "Список портов не изменился";
    }
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

void SerialPort::startTimerForUpdateCP(quint16 period)
{
    this->period = period;

    if (!m_portCheckTimer) {
        m_portCheckTimer = new QTimer(this);
        connect(m_portCheckTimer, &QTimer::timeout, this, &SerialPort::slotUpdateSP);
    }

    m_portCheckTimer->start(this->period);
}

void SerialPort::stopTimerForUpdateCP() // Исправлено имя функции
{
    if (m_portCheckTimer) {
        m_portCheckTimer->stop();
    }
}

bool SerialPort::sendString(const QString &text, bool addNewLine)
{
    if (!m_serialPort || !m_serialPort->isOpen() || !m_serialPort->isWritable()) {
        qDebug() << "Port is not open or not writable";
        return false;
    }

    QByteArray data;
    if (addNewLine) {
        data = (text + "\r\n").toUtf8();
    } else {
        data = text.toUtf8();
    }

    qint64 bytesWritten = m_serialPort->write(data);

    if (bytesWritten == -1) {
        qDebug() << "Write failed:" << m_serialPort->errorString();
        return false;
    } else {
        qDebug() << "Sent:" << bytesWritten << "bytes";
        return m_serialPort->waitForBytesWritten(1000);
    }
}

void SerialPort::sendQStringAsync(const QString &text)
{
    if (!m_serialPort || !m_serialPort->isOpen() || !m_serialPort->isWritable()) {
        return;
    }

    QByteArray data = text.toUtf8();
    m_serialPort->write(data);
}

bool SerialPort::sendQStringAsHex(const QString &text)
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        return false;
    }

    QByteArray data = text.toUtf8().toHex();
    qint64 bytesWritten = m_serialPort->write(data);

    return (bytesWritten != -1);
}

bool SerialPort::open()
{
    // Закрываем предыдущее соединение, если есть
    if (m_serialPort && m_serialPort->isOpen()) {
        close();
    }

    m_serialPort = new QSerialPort(this); // Указываем родителя для автоматического удаления

    m_serialPort->setPortName(settings.portName());
    m_serialPort->setBaudRate(settings.baudRate());
    m_serialPort->setDataBits(settings.dataBits());
    m_serialPort->setParity(settings.parity());
    m_serialPort->setStopBits(settings.stopBits());
    m_serialPort->setFlowControl(settings.flowControl());

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Port opened successfully:" << settings.portName();
        return true;
    } else {
        qDebug() << "Failed to open port:" << settings.portName() << "Error:" << m_serialPort->errorString();
        delete m_serialPort;
        m_serialPort = nullptr;
        return false;
    }
}

void SerialPort::close()
{
    if (m_serialPort) {
        if (m_serialPort->isOpen()) {
            m_serialPort->close();
            qDebug() << "Port closed";
        }
        // Не нужно удалять вручную, т.к. установлен родитель
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
