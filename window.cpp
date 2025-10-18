#include "window.h"
#include "./ui_window.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QPrinter>
#include <QPrintDialog>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    popUp = new PopUp();
}

Window::~Window()
{
    delete ui;
}

void Window::on_btn_SendCommand_clicked()
{
    ui->textEdit->insertPlainText(ui->lineEdit_Command->text() + '\n');
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

void Window::on_menuBar_Save_triggered()
{
    this->openFileDialogToSave();
}

void Window::openFileDialogToSave()
{
    // Получаем текст из QTextEdit
    QString text = ui->textEdit->toPlainText();


    // Открываем диалог выбора файла для сохранения
    QString fileName = QFileDialog::getSaveFileName(
        this,                       // родительское окно
        "Сохранить файл",           // заголовок диалога
        "",                         // начальная директория
        "Текстовые файлы (*.txt);;Все файлы (*)" // фильтры файлов
        );

    // Если пользователь отменил диалог
    if (fileName.isEmpty()) {
        return;
    }

    // Создаем объект файла
    QFile file(fileName);

    // Пытаемся открыть файл для записи
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл для записи: " + file.errorString());
        return;
    }

    // Создаем текстовый поток для записи
    QTextStream out(&file);

    // Записываем текст в файл
    out << text;

    // Закрываем файл
    file.close();

    // Сообщаем об успешном сохранении
    QMessageBox::information(this, "Успех", "Файл успешно сохранен!");
}

void Window::on_menuBar_SaveAs_triggered()
{
    this->openFileDialogToSave();
}

void Window::on_menuBar_GitHub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/VoltPro220/ComPortMonitor", QUrl::TolerantMode));
}


void Window::on_menuBar_Print_triggered()
{
    QString text = ui->textEdit->toPlainText();

    if (text.isEmpty()) {
        popUp->setPopupText("ПРЕДУПРЕЖДЕНИЕ:\nВ логах нету информации, не получится напечатать");
        popUp->show();
        return;
    }

    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    printDialog.setWindowTitle("Печать документа");

    if (printDialog.exec() == QDialog::Accepted) {
        QTextDocument document;
        document.setPlainText(text);

        QFont font = ui->textEdit->font();
        document.setDefaultFont(font);

        document.print(&printer);
        popUp->setPopupText("УСПЕШНО");
        popUp->show();
    }
}


void Window::on_lineEdit_Command_returnPressed()
{
    if(!ui->lineEdit_Command->text().trimmed().isEmpty())
    {
        ui->btn_SendCommand->click();
        ui->lineEdit_Command->clear();
    }
}

