#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "../libs/popup/popup.h"
#include "../libs/sp/serialport.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

    void openFileDialogToSave();
    Ui::Window *ui;
    PopUp *popUp;
    SerialPort *serialPort;

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:

    void scrollDown();

private slots:
    void on_btn_SendCommand_clicked();

    void on_btn_Connect_clicked();

    void on_btn_Clear_clicked();

    void on_menuBar_Exit_triggered();

    void on_menuBar_Save_triggered();

    void on_menuBar_SaveAs_triggered();

    void on_menuBar_GitHub_triggered();

    void on_menuBar_Print_triggered();

    void on_lineEdit_Command_returnPressed();

    void on_menuBar_Settings_triggered();

    void getPorts(QList<PortInfo>);

    void on_checkBox_AutoScroll_checkStateChanged(const Qt::CheckState &arg1);
};
#endif // WINDOW_H
