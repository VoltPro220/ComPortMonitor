#include "./window.h"
#include <./ui_window.h>
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
    popUp = new PopUp(this);
    serialPort = new SerialPort(this);

    connect(serialPort, &SerialPort::signalForUpdateCP, this, &Window::getPorts);
    serialPort->startTimerForUpdateCP(2000);

}

Window::~Window()
{
    delete ui;
    delete popUp;
}

void Window::scrollDown()
{
    if(ui->checkBox_AutoScroll->isChecked()){
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
}

void Window::on_btn_SendCommand_clicked()
{
    if(!ui->lineEdit_Command->text().trimmed().isEmpty()) return;

    if(serialPort->sendString(ui->lineEdit_Command->text()))
    {
        ui->textEdit->insertPlainText(ui->lineEdit_Command->text() + '\n');
        ui->lineEdit_Command->clear();
    }
    else
    {
        popUp->setPopupText("Произошла ошибка!\nПопробуйте снова");
        popUp->show();
    }
}

void Window::on_btn_Connect_clicked()
{
    connectPort();
}

void Window::connectPort()
{
    COMPortSettings set;
    set.setPortName(ui->comboBox_ComPort->currentText());
    set.setBaudRate(ui->comboBox_BaudRate->currentText().toInt());
    set.setStopBits(ui->comboBox_StopBit->currentText().toInt());
    set.setDataBits(ui->comboBox_DataBit->currentText().toInt());
    set.setParity(ui->comboBox_Parity->currentText());
    set.setFlowControl(ui->comboBox_FlowControl->currentText());

    serialPort->setSettings(set);

    bool isOpening = (ui->btn_Connect->text() == "Открыть");

    ui->btn_Connect->setText(isOpening ? "Закрыть" : "Открыть");
    ui->menuBar_connect->setText(isOpening ? "Закрыть" : "Открыть");

    if (isOpening) {
        if (serialPort->open()) {
            ui->textEdit->insertPlainText("PORT " + set.portName() + " успешно открыт\n");
        }
    } else {
        serialPort->close();
        ui->textEdit->insertPlainText("PORT " + set.portName() + " успешно закрыт\n");
    }
    scrollDown();

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
    QString text = ui->textEdit->toPlainText();


    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        "",
        "Текстовые файлы (*.txt);;Все файлы (*)"
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

    QTextStream out(&file);

    out << text;

    file.close();

    popUp->setPopupText("Успешно!");
    popUp->show();
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


void Window::on_menuBar_Settings_triggered()
{
    // TODO: OPEN SETTINGS
    popUp->setPopupText("Извините!\nНастройки ещё не готовы");
    popUp->show();
}

void Window::getPorts(QList<PortInfo> ports)
{

    if (ports.isEmpty()) {
        popUp->setPopupText("Порты не найдены");
        popUp->show();
        return;
    }
    QString current = ui->comboBox_ComPort->itemData(ui->comboBox_ComPort->currentIndex()).toString();
    ui->comboBox_ComPort->clear();
    for (const auto &port : ports)
    {
        ui->textEdit->insertPlainText("Port: " + port.portName + '\n');
        ui->textEdit->insertPlainText("Description: " + port.description + '\n');
        ui->textEdit->insertPlainText("Manufacturer: " + port.manufacturer + '\n');
        ui->textEdit->insertPlainText("System Location: " + port.systemLocation + '\n');
        ui->textEdit->insertPlainText("Vendor ID: " + (!port.vendorId.isEmpty() ? port.vendorId : "N/A") + '\n');
        ui->textEdit->insertPlainText("Product ID: " + (!port.productId.isEmpty() ? port.productId : "N/A") + '\n');
        ui->textEdit->insertPlainText("-----------------------------------\n");
        scrollDown();

        ui->comboBox_ComPort->addItem(port.portName);
    }
    ui->comboBox_ComPort->setCurrentText(current);

}




void Window::on_checkBox_AutoScroll_checkStateChanged(const Qt::CheckState &arg1)
{
    scrollDown();
}


void Window::on_menuBar_Find_triggered()
{
    QTextEdit* textEdit = ui->textEdit;
    QTextCursor cursor(textEdit->document());

    QList<QTextEdit::ExtraSelection> selections;

    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = textEdit->document()->find(ui->lineEdit_Command->text(), cursor);

        if (!cursor.isNull()) {
            QTextEdit::ExtraSelection selection;
            selection.cursor = cursor;
            selection.format.setBackground(Qt::yellow); // Подсветка желтым цветом

            selections.append(selection);
        }
    }

    textEdit->setExtraSelections(selections);

    if (!selections.isEmpty()) {
        // Создаем соединение для сброса подсветки при клике
        auto resetHighlight = [textEdit]() {
            textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());

            // Устанавливаем курсор в конец
            QTextCursor cursor = textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            textEdit->setTextCursor(cursor);

            // Отключаем обработчик после использования
            textEdit->disconnect(); // Отключаем все соединения, связанные с textEdit
        };

        // Подключаем обработчик клика
        connect(textEdit, &QTextEdit::cursorPositionChanged, this, resetHighlight);

        popUp->setPopupText("Найдено: " + QString::number(selections.size()));
        popUp->show();
    }
    else {
        popUp->setPopupText("Не найдено");
        popUp->show();
    }
}


void Window::on_menuBar_Docs_triggered()
{
    popUp->setPopupText("В разработке");
    popUp->show();
}


void Window::on_menuBar_AboutPro_triggered()
{
    popUp->setPopupText("В разработке");
    popUp->show();
}


void Window::on_menuBar_Undo_triggered()
{
    popUp->setPopupText("В разработке");
    popUp->show();
}


void Window::on_menuBar_Redo_triggered()
{
    popUp->setPopupText("В разработке");
    popUp->show();
}


void Window::on_menuBar_connect_triggered()
{
    connectPort();
}

