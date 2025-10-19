#ifndef COMPORTSETTINGS_H
#define COMPORTSETTINGS_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QVector>
#include <QMetaType>

class COMPortSettings : public QObject
{
    Q_OBJECT

public:
    explicit COMPortSettings(QObject *parent = nullptr);
    COMPortSettings(const QString &portName,
                    qint32 baudRate = QSerialPort::Baud9600,
                    QSerialPort::DataBits dataBits = QSerialPort::Data8,
                    QSerialPort::Parity parity = QSerialPort::NoParity,
                    QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl,
                    QObject *parent = nullptr);

    QString portName() const;
    qint32 baudRate() const;
    QSerialPort::DataBits dataBits() const;
    QSerialPort::Parity parity() const;
    QSerialPort::StopBits stopBits() const;
    QSerialPort::FlowControl flowControl() const;
    bool isValid() const;

    bool setPortName(const QString &portName);
    bool setBaudRate(qint32 baudRate);
    bool setDataBits(QSerialPort::DataBits dataBits);
    bool setDataBits(int dataBits);
    bool setParity(QSerialPort::Parity parity);
    bool setParity(const QString &parity);
    bool setStopBits(QSerialPort::StopBits stopBits);
    bool setStopBits(int stopBits);
    bool setFlowControl(QSerialPort::FlowControl flowControl);
    bool setFlowControl(const QString &flowControl);

    static bool isValidPortName(const QString &portName);
    static bool isValidBaudRate(qint32 baudRate);
    static bool isValidDataBits(QSerialPort::DataBits dataBits);
    static bool isValidDataBits(int dataBits);
    static bool isValidParity(QSerialPort::Parity parity);
    static bool isValidStopBits(QSerialPort::StopBits stopBits);
    static bool isValidStopBits(int stopBits);
    static bool isValidFlowControl(QSerialPort::FlowControl flowControl);
    
    QString extracted() const;
    QString toString() const;
    static QVector<qint32> standardBaudRates();
    static QVector<QSerialPort::DataBits> standardDataBits();
    static QVector<QSerialPort::Parity> standardParities();
    static QVector<QSerialPort::StopBits> standardStopBits();
    static QVector<QSerialPort::FlowControl> standardFlowControls();

    static QString parityToString(QSerialPort::Parity parity);
    static QString stopBitsToString(QSerialPort::StopBits stopBits);
    static QString flowControlToString(QSerialPort::FlowControl flowControl);
    static QSerialPort::Parity stringToParity(const QString &parity);
    static QSerialPort::StopBits stringToStopBits(const QString &stopBits);
    static QSerialPort::FlowControl stringToFlowControl(const QString &flowControl);

signals:
    void settingsChanged();
    void validationError(const QString &error);

private:
    QString m_portName;
    qint32 m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::Parity m_parity;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::FlowControl m_flowControl;
    bool m_isValid;

    void initializeDefaults();
};

Q_DECLARE_METATYPE(COMPortSettings)

#endif // COMPORTSETTINGS_H
