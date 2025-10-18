#include "window.h"
#include "./ui_window.h"
#include <QMessageBox>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_btn_SendCommand_clicked()
{
}


void Window::on_btn_Connect_clicked()
{
}


void Window::on_btn_Clear_clicked()
{
    ui->textEdit->clear();
}


void Window::on_menuBar_Exit_triggered()
{
    QApplication::quit();
}

