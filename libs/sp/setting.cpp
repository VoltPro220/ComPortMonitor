#include "setting.h"
#include <QRegularExpression>
#include <QDebug>

COMPortSettings::COMPortSettings(QObject *parent)
    : QObject(parent)
{
    initializeDefaults();
}

COMPortSettings::COMPortSettings(const QString &portName,
                                 qint32 baudRate,
                                 QSerialPort::DataBits dataBits,
                                 QSerialPort::Parity parity,
                                 QSerialPort::StopBits stopBits,
                                 QSerialPort::FlowControl flowControl,
                                 QObject *parent)
    : QObject(parent)
    , m_portName(portName)
    , m_baudRate(baudRate)
    , m_dataBits(dataBits)
    , m_parity(parity)
    , m_stopBits(stopBits)
    , m_flowControl(flowControl)
{
    m_isValid = isValidPortName(portName) &&
                isValidBaudRate(baudRate) &&
                isValidDataBits(dataBits) &&
                isValidParity(parity) &&
                isValidStopBits(stopBits) &&
                isValidFlowControl(flowControl);
}

void COMPortSettings::initializeDefaults()
{
    m_portName = "COM1";
    m_baudRate = QSerialPort::Baud9600;
    m_dataBits = QSerialPort::Data8;
    m_parity = QSerialPort::NoParity;
    m_stopBits = QSerialPort::OneStop;
    m_flowControl = QSerialPort::NoFlowControl;
    m_isValid = true;
}

QString COMPortSettings::portName() const { return m_portName; }
qint32 COMPortSettings::baudRate() const { return m_baudRate; }
QSerialPort::DataBits COMPortSettings::dataBits() const { return m_dataBits; }
QSerialPort::Parity COMPortSettings::parity() const { return m_parity; }
QSerialPort::StopBits COMPortSettings::stopBits() const { return m_stopBits; }
QSerialPort::FlowControl COMPortSettings::flowControl() const { return m_flowControl; }
bool COMPortSettings::isValid() const { return m_isValid; }

bool COMPortSettings::setPortName(const QString &portName)
{
    if (!isValidPortName(portName)) {
        emit validationError("Invalid port name: " + portName);
        return false;
    }

    if (m_portName != portName) {
        m_portName = portName;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setBaudRate(qint32 baudRate)
{
    if (!isValidBaudRate(baudRate)) {
        emit validationError("Invalid baud rate: " + QString::number(baudRate));
        return false;
    }

    if (m_baudRate != baudRate) {
        m_baudRate = baudRate;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setDataBits(QSerialPort::DataBits dataBits)
{
    if (!isValidDataBits(dataBits)) {
        emit validationError("Invalid data bits");
        return false;
    }

    if (m_dataBits != dataBits) {
        m_dataBits = dataBits;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setDataBits(int dataBits)
{
    QSerialPort::DataBits bits = static_cast<QSerialPort::DataBits>(dataBits);
    return setDataBits(bits);
}

bool COMPortSettings::setParity(QSerialPort::Parity parity)
{
    if (!isValidParity(parity)) {
        emit validationError("Invalid parity");
        return false;
    }

    if (m_parity != parity) {
        m_parity = parity;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setParity(const QString &parity)
{
    QSerialPort::Parity parityEnum = stringToParity(parity);
    return setParity(parityEnum);
}

bool COMPortSettings::setStopBits(QSerialPort::StopBits stopBits)
{
    if (!isValidStopBits(stopBits)) {
        emit validationError("Invalid stop bits");
        return false;
    }

    if (m_stopBits != stopBits) {
        m_stopBits = stopBits;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setStopBits(int stopBits)
{
    QSerialPort::StopBits bits = static_cast<QSerialPort::StopBits>(stopBits);
    return setStopBits(bits);
}

bool COMPortSettings::setFlowControl(QSerialPort::FlowControl flowControl)
{
    if (!isValidFlowControl(flowControl)) {
        emit validationError("Invalid flow control");
        return false;
    }

    if (m_flowControl != flowControl) {
        m_flowControl = flowControl;
        emit settingsChanged();
    }
    return true;
}

bool COMPortSettings::setFlowControl(const QString &flowControl)
{
    QSerialPort::FlowControl fc = stringToFlowControl(flowControl);
    return setFlowControl(fc);
}

// Валидаторы
bool COMPortSettings::isValidPortName(const QString &portName)
{
    if (portName.isEmpty()) return false;

#ifdef Q_OS_WIN
    QRegularExpression regex("^COM[1-9][0-9]?[0-9]?$");
#else
    QRegularExpression regex("^/dev/(ttyS|ttyUSB|ttyACM)[0-9]+$");
#endif

    return regex.match(portName).hasMatch();
}

bool COMPortSettings::isValidBaudRate(qint32 baudRate)
{
    return standardBaudRates().contains(baudRate);
}

bool COMPortSettings::isValidDataBits(QSerialPort::DataBits dataBits)
{
    return standardDataBits().contains(dataBits);
}

bool COMPortSettings::isValidDataBits(int dataBits)
{
    return isValidDataBits(static_cast<QSerialPort::DataBits>(dataBits));
}

bool COMPortSettings::isValidParity(QSerialPort::Parity parity)
{
    return standardParities().contains(parity);
}

bool COMPortSettings::isValidStopBits(QSerialPort::StopBits stopBits)
{
    return standardStopBits().contains(stopBits);
}

bool COMPortSettings::isValidStopBits(int stopBits)
{
    return isValidStopBits(static_cast<QSerialPort::StopBits>(stopBits));
}

bool COMPortSettings::isValidFlowControl(QSerialPort::FlowControl flowControl)
{
    return standardFlowControls().contains(flowControl);
}

// Утилиты
QString COMPortSettings::toString() const
{
    return QString("Port: %1, Baud: %2, Data: %3, Parity: %4, Stop: %5, Flow: %6")
    .arg(m_portName)
        .arg(m_baudRate)
        .arg(m_dataBits)
        .arg(parityToString(m_parity))
        .arg(stopBitsToString(m_stopBits))
        .arg(flowControlToString(m_flowControl));
}

QVector<qint32> COMPortSettings::standardBaudRates()
{
    return QVector<qint32> {
        110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200,
        28800, 38400, 57600, 115200, 230400, 460800, 921600
    };
}

QVector<QSerialPort::DataBits> COMPortSettings::standardDataBits()
{
    return QVector<QSerialPort::DataBits> {
        QSerialPort::Data5, QSerialPort::Data6,
        QSerialPort::Data7, QSerialPort::Data8
    };
}

QVector<QSerialPort::Parity> COMPortSettings::standardParities()
{
    return QVector<QSerialPort::Parity> {
        QSerialPort::NoParity, QSerialPort::EvenParity,
        QSerialPort::OddParity, QSerialPort::SpaceParity,
        QSerialPort::MarkParity
    };
}

QVector<QSerialPort::StopBits> COMPortSettings::standardStopBits()
{
    return QVector<QSerialPort::StopBits> {
        QSerialPort::OneStop, QSerialPort::OneAndHalfStop,
        QSerialPort::TwoStop
    };
}

QVector<QSerialPort::FlowControl> COMPortSettings::standardFlowControls()
{
    return QVector<QSerialPort::FlowControl> {
        QSerialPort::NoFlowControl, QSerialPort::HardwareControl,
        QSerialPort::SoftwareControl
    };
}

// Статические методы преобразования
QString COMPortSettings::parityToString(QSerialPort::Parity parity)
{
    switch (parity) {
    case QSerialPort::NoParity: return "None";
    case QSerialPort::EvenParity: return "Even";
    case QSerialPort::OddParity: return "Odd";
    case QSerialPort::SpaceParity: return "Space";
    case QSerialPort::MarkParity: return "Mark";
    default: return "Unknown";
    }
}

QString COMPortSettings::stopBitsToString(QSerialPort::StopBits stopBits)
{
    switch (stopBits) {
    case QSerialPort::OneStop: return "1";
    case QSerialPort::OneAndHalfStop: return "1.5";
    case QSerialPort::TwoStop: return "2";
    default: return "Unknown";
    }
}

QString COMPortSettings::flowControlToString(QSerialPort::FlowControl flowControl)
{
    switch (flowControl) {
    case QSerialPort::NoFlowControl: return "OFF";
    case QSerialPort::HardwareControl: return "RTS/CTS";
    case QSerialPort::SoftwareControl: return "XON/XOFF";
    default: return "Unknown";
    }
}

QSerialPort::Parity COMPortSettings::stringToParity(const QString &parity)
{
    QString parityLower = parity.toLower();
    if (parityLower == "None") return QSerialPort::NoParity;
    if (parityLower == "Even") return QSerialPort::EvenParity;
    if (parityLower == "Odd") return QSerialPort::OddParity;
    if (parityLower == "Space") return QSerialPort::SpaceParity;
    if (parityLower == "Mark") return QSerialPort::MarkParity;
    return QSerialPort::NoParity;
}

QSerialPort::StopBits COMPortSettings::stringToStopBits(const QString &stopBits)
{
    QString stopBitsLower = stopBits.toLower();
    if (stopBitsLower == "1") return QSerialPort::OneStop;
    if (stopBitsLower == "1.5") return QSerialPort::OneAndHalfStop;
    if (stopBitsLower == "2") return QSerialPort::TwoStop;
    return QSerialPort::OneStop;
}

QSerialPort::FlowControl COMPortSettings::stringToFlowControl(const QString &flowControl)
{
    QString fcLower = flowControl.toLower();
    if (fcLower == "OFF") return QSerialPort::NoFlowControl;
    if (fcLower == "RTS/CTS") return QSerialPort::HardwareControl;
    if (fcLower == "XON/XOFF") return QSerialPort::SoftwareControl;
    return QSerialPort::NoFlowControl;
}
