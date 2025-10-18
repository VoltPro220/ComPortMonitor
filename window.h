#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void on_btn_SendCommand_clicked();

    void on_btn_Connect_clicked();

    void on_btn_Clear_clicked();

    void on_menuBar_Exit_triggered();

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
