#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "setting.h"

struct PortInfo {
    QString portName;
    QString description;
    QString manufacturer;
    QString systemLocation;
    QString vendorId;
    QString productId;

    bool operator==(const PortInfo &other) const {
        return portName == other.portName &&
               description == other.description &&
               manufacturer == other.manufacturer &&
               systemLocation == other.systemLocation &&
               vendorId == other.vendorId &&
               productId == other.productId;
    }

    // Оператор неравенства для удобства
    bool operator!=(const PortInfo &other) const {
        return !(*this == other);
    }

};

class SerialPort : public QObject
{
    Q_OBJECT

    QList<PortInfo> all_ports;
    QTimer *m_portCheckTimer;

    QSerialPort *m_serialPort;

    quint16 period;

    COMPortSettings settings;

public:

    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void findAllPorts();
    void setSettings(COMPortSettings& settings);

    void startTimerForUpdateCP(quint16);
    void stopTimerForUpdateCP();

    bool sendString(const QString &text, bool addNewLine = true);
    void sendQStringAsync(const QString &text);
    bool sendQStringAsHex(const QString &text);

    void extracted();
    bool open();

    const QList<PortInfo>& getPortInfo() const noexcept;

    void close();

    bool isOpen() const;
public slots:
    void slotUpdateSP();

signals:
    void signalForUpdateCP(QList<PortInfo>);


};

inline bool operator==(const QList<PortInfo> &list1, const QList<PortInfo> &list2)
{
    if (list1.size() != list2.size()) {
        return false;
    }

    for (int i = 0; i < list1.size(); ++i) {
        if (list1[i] != list2[i]) {
            return false;
        }
    }

    return true;
}

inline bool operator!=(const QList<PortInfo> &list1, const QList<PortInfo> &list2)
{
    return !(list1 == list2);
}


#endif // SERIALPORT_H
