#include "window/window.h"

#include <QApplication>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;

    a.setApplicationVersion("0.0.0");
    a.setApplicationName("Com Port Monitor");
    a.setOrganizationName("Volt");

    w.show();
    return a.exec();
}
