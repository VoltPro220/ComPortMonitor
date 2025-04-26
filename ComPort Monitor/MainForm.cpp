#include "MainForm.h"
#include "SettingsForm.h"

using namespace System;
using namespace System::Windows::Forms;

com_port_monitor::MainForm::MainForm(void)
{
	this->InitializeComponent();
	this->saveFileDialog->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы|*.*";
}

com_port_monitor::MainForm::~MainForm()
{
	if (this->components)
	{
		delete this->components;
	}
	if (this->th)
		this->th->Abort();
	this->disconnectPortCom();
}

//
// SEND TO COM PORT (BUTTON)
//
System::Void com_port_monitor::MainForm::buttonSendCommand_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->sendDataToPort();
}

// KEY DOWN (FORM)
System::Void com_port_monitor::MainForm::mainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{}

//
// KEY DOWN (EDIT COMMAND)
//
System::Void com_port_monitor::MainForm::textBoxWriteCommand_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter)
	{
		e->SuppressKeyPress = true;
		this->sendDataToPort();
	}
}

//
// UPDATE COM PORTS
//
void com_port_monitor::MainForm::updateComPorts()
{
	this->comboBoxComPorts->Items->Clear();
	this->chooseComToolStripMenuItem->DropDownItems->Clear();
	this->comboBoxComPorts->ResetText();
	for (int i = 1; i <= 256; i++)
	{
		if (check_com_port(i) != -1)
		{
			this->comboBoxComPorts->Items->Add("COM" + i);
			ToolStripMenuItem^ p = gcnew ToolStripMenuItem();
			p->Text = "COM" + i;
			p->Click += gcnew System::EventHandler(this, &MainForm::chooseComPort);
			this->chooseComToolStripMenuItem->DropDownItems->Add(p);
		}
	}

}

//
// SEND DATA TO COM PORT
//
void com_port_monitor::MainForm::sendDataToPort()
{
	if (this->isConnectedToComPort)
	{
		if (this->textBoxWriteCommand->Text != "")
		{
			this->textBoxConsole->Text += "[" + this->dateTime.Now + "] INFO:\tSending" + Environment::NewLine;
			write_to_com_port(this->hPortCom, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBoxWriteCommand->Text));
			this->textBoxWriteCommand->Text = "";
		}
	}
	else
	{
		MessageBox::Show("Пожалуйста, подключитесь к устройству", "Внимание!");
	}
}

//
// Exit
//
System::Void com_port_monitor::MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->th)
		this->th->Abort();
	this->disconnectPortCom();
	Application::Exit();
}

//
// SAVE LOGS
//
System::Void com_port_monitor::MainForm::saveLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->saveFileDialog->ShowDialog();
	String^ fileName = this->saveFileDialog->FileName;
	if (fileName != "")
	{
		System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(fileName);
		sw->WriteLine(this->textBoxConsole->Text);
		sw->Close();
	}
}

//
// PRINT LOGS
//
System::Void com_port_monitor::MainForm::printLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->printDialog->Document = this->printDocument;
	if (this->printDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		this->printDocument->Print();
	}

}

//
// EVENT PRINT DOC
//
System::Void com_port_monitor::MainForm::printDocument_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
{
	e->Graphics->DrawString(this->textBoxConsole->Text, gcnew System::Drawing::Font("Arial", 12), Brushes::Black, 10, 10);
}

//
// OPEN GITHUB
//
System::Void com_port_monitor::MainForm::gitHubToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Diagnostics::Process::Start("https://github.com/VoltPro220/ComPortMonitor");
}

//
// OPEN DOCUMENTATION
//
System::Void com_port_monitor::MainForm::documentationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Diagnostics::Process::Start("https://github.com/VoltPro220/ComPortMonitor/blob/master/README.md");
}

//
// ABOUT PROGRAM
//
System::Void com_port_monitor::MainForm::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Com Port monitor. Программа для считывания и записи данные в последовательный com port\nBy Volt 2025\nMIT LICENSE",
					 "О программе",
					 MessageBoxButtons::OK,
					 MessageBoxIcon::Information);
}

//
// OPEN SETTINGS
//
System::Void com_port_monitor::MainForm::settingsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	com_port_monitor::SettingsForm form;
	form.ShowDialog();
}

//
// FORM LOAD
//
System::Void com_port_monitor::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	this->textBoxWriteCommand->Select();
	this->comboBoxBaudRate->Text = Convert::ToString(this->baudRate);
	this->baudToolStripMenuItem->Text = "Бод: " + Convert::ToString(this->baudRate);
	this->updateComPorts();
}

//
// FORM WITH CHART
//
System::Void com_port_monitor::MainForm::chartToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

//
// CONNECT TO COM PORT (BUTTON)
//
System::Void com_port_monitor::MainForm::buttonConnectToComPort_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->buttonConnectToComPort->Text == "Подключиться")
	{
		if (this->connectToPort())
		{
			this->buttonConnectToComPort->Text = "Отключится";
			this->connectToolStripMenuItem->Text = "Отключится";
		}
		else
		{
			MessageBox::Show("Пожалуйста, проверьте корректность данных COM порта и повторите попытку", "Ошибка",
							 MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	else
	{
		this->disconnectPortCom();
		this->buttonConnectToComPort->Text = "Подключиться";
		this->connectToolStripMenuItem->Text = "Подключиться";
	}
}
System::Void com_port_monitor::MainForm::connectToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->connectToolStripMenuItem->Text == "Подключиться")
	{
		if (this->connectToPort())
		{
			this->buttonConnectToComPort->Text = "Отключится";
			this->connectToolStripMenuItem->Text = "Отключится";
		}
		else
		{
			MessageBox::Show("Пожалуйста, проверьте корректность данных COM порта и повторите попытку", "Ошибка",
							 MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	else
	{
		this->disconnectPortCom();
		this->buttonConnectToComPort->Text = "Подключиться";
		this->connectToolStripMenuItem->Text = "Подключиться";
	}
}

//
// BUTTON CLEAR LOGS
//
System::Void com_port_monitor::MainForm::buttonClearConsole_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->textBoxConsole->Text = "";
}

//
// CONNECT TO COM PORT
//
bool com_port_monitor::MainForm::connectToPort()
{

	this->hPortCom = open_com_port(this->hPortCom,
								   (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->comPort),
								   this->baudRate);
	if (this->hPortCom != INVALID_HANDLE_VALUE)
	{
		this->textBoxConsole->Text += "[" + this->dateTime.Now + "] Connect to " + this->comboBoxComPorts->Text + Environment::NewLine;
		this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
		this->textBoxConsole->ScrollToCaret();
		this->isConnectedToComPort = true;
		this->th = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(this, &MainForm::readComPort));
		this->th->Start();
		return true;
	}
	return false;
}

//
// DISCONNECT FROM COM PORT
//
void com_port_monitor::MainForm::disconnectPortCom()
{
	if (this->isConnectedToComPort)
	{
		CloseHandle(this->hPortCom);
		this->textBoxConsole->Text += "[" + this->dateTime.Now + "] Disconnect" + Environment::NewLine;
		this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
		this->textBoxConsole->ScrollToCaret();
		this->isConnectedToComPort = false;
		this->th->Abort();
		this->hPortCom = nullptr;
	}
}

//
// READ COM PORT 
//
void com_port_monitor::MainForm::readComPort(Object^ p)
{
	while (true)
	{
		if (this->isConnectedToComPort)
		{
			char* buf = const_cast<char*>(read_from_com_port(this->hPortCom));
			if (buf != NULL)
			{
				String^ str = gcnew String(buf);
				if (!str->EndsWith("\n"))
					this->textBoxConsole->Text += str + Environment::NewLine;
				else if (str->EndsWith("\n"))
					this->textBoxConsole->Text += str;
				this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
				this->textBoxConsole->ScrollToCaret();
			}
			free(buf);
		}
	}
}

//
// SET BAUD RATE
//
void com_port_monitor::MainForm::setBaudRate(System::Object^ sender, System::EventArgs^ e)
{
	ToolStripMenuItem^ b = static_cast<ToolStripMenuItem^>(sender);
	this->baudRate = Convert::ToInt32(b->Text);
	this->baudToolStripMenuItem->Text = "Бод: " + b->Text;
	this->comboBoxBaudRate->Text = b->Text;
}
void com_port_monitor::MainForm::setBaudRateComboBox(System::Object^ sender, System::EventArgs^ e)
{
	this->baudRate = Convert::ToInt32(this->comboBoxBaudRate->Text);
	this->baudToolStripMenuItem->Text = "Бод: " + this->comboBoxBaudRate->Text;
}

//
// Choose and set COM PORT
//
void com_port_monitor::MainForm::chooseComPort(System::Object^ sender, System::EventArgs^ e)
{
	ToolStripMenuItem^ b = static_cast<ToolStripMenuItem^>(sender);
	this->comboBoxComPorts->Text =  b->Text;
	this->comPort = b->Text;
}
void com_port_monitor::MainForm::chooseComPortComboBox(System::Object^ sender, System::EventArgs^ e)
{
	this->chooseComToolStripMenuItem->Text = this->comboBoxComPorts->Text;
	this->comPort = this->comboBoxComPorts->Text;
}

//
// FORM CLOSED
//
System::Void com_port_monitor::MainForm::MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	if (this->th)
		this->th->Abort();
	this->disconnectPortCom();
	Application::Exit();
}

//
// UPDATE COM PORT (BUTTON)
//
System::Void com_port_monitor::MainForm::buttonUpdateComPorts_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->isConnectedToComPort)
		this->updateComPorts();
}
System::Void com_port_monitor::MainForm::updateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->isConnectedToComPort)
		this->updateComPorts();
}


//
// MAIN
//
[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	com_port_monitor::MainForm form;
	Application::Run(% form);
	return 0;
}

