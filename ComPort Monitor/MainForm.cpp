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
		this->sendDataToPort();
	}
}



void com_port_monitor::MainForm::updateComPorts()
{
	this->comboBoxComPorts->Items->Clear();
	this->comboBoxComPorts->ResetText();
	for (int i = 1; i <= 256; i++)
	{
		if(check_com_port(i) != -1)
			this->comboBoxComPorts->Items->Add("COM" + i);
	}

}

//
// SEND DATA TO COM PORT
//
void com_port_monitor::MainForm::sendDataToPort()
{
	MessageBox::Show("TEST", "TEST");
}

//
// Exit
//
System::Void com_port_monitor::MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->th)
		this->th->Abort();
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

System::Void com_port_monitor::MainForm::printDocument_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
{
	e->Graphics->DrawString(this->textBoxConsole->Text, gcnew System::Drawing::Font("Arial", 12), Brushes::Black, 10, 10);
}

System::Void com_port_monitor::MainForm::gitHubToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Diagnostics::Process::Start("https://github.com/VoltPro220/ComPortMonitor");
}

System::Void com_port_monitor::MainForm::documentationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Diagnostics::Process::Start("https://github.com/VoltPro220/ComPortMonitor/blob/master/README.md");
}

System::Void com_port_monitor::MainForm::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Com Port monitor. Программа для считывания и записи данные в последовательный com port\nBy Volt 2025\nMIT LICENSE",
					 "О программе",
					 MessageBoxButtons::OK,
					 MessageBoxIcon::Information);
}

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
	}
	else
	{
		this->disconnectPortCom();
		this->buttonConnectToComPort->Text = "Подключиться";
		this->connectToolStripMenuItem->Text = "Подключиться";
	}
}

System::Void com_port_monitor::MainForm::buttonClearConsole_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->textBoxConsole->Text = "";
}

bool com_port_monitor::MainForm::connectToPort()
{
	
	this->hPortCom = open_com_port(this->hPortCom, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->comboBoxComPorts->Text));
	if (this->hPortCom != INVALID_HANDLE_VALUE)
	{
		this->textBoxConsole->Text += "[" + this->dateTime.Now + "] INFO:\tConnect" + Environment::NewLine;
		this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
		this->textBoxConsole->ScrollToCaret();
		this->isConnectedToComPort = true;
		this->th = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(this, &MainForm::readComPort));
		this->th->Start();
		return true;
	}
	return false;
}

void com_port_monitor::MainForm::disconnectPortCom()
{
	CloseHandle(this->hPortCom);
	this->textBoxConsole->Text += "[" + this->dateTime.Now + "] INFO:\tDisconnect" + Environment::NewLine;
	this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
	this->textBoxConsole->ScrollToCaret();
	this->isConnectedToComPort = false;
	this->th->Abort();
	this->hPortCom = nullptr;
}

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
					this->textBoxConsole->Text += "[" + this->dateTime.Now + "] INFO:\t" + str + Environment::NewLine;
				else if (str->EndsWith("\n"))
					this->textBoxConsole->Text += "[" + this->dateTime.Now + "] INFO:\t" + str;
				this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
				this->textBoxConsole->ScrollToCaret();
			}
			free(buf);
		}
	}
}

System::Void com_port_monitor::MainForm::MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	if (this->th)
		this->th->Abort();
	Application::Exit();
}

System::Void com_port_monitor::MainForm::buttonUpdateComPorts_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->updateComPorts();
}



[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	com_port_monitor::MainForm form;
	Application::Run(% form);
	return 0;
}

