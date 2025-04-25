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
}

//
// SEND TO COM PORT (BUTTON)
//
System::Void com_port_monitor::MainForm::buttonSendCommand_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->SendDataToPort();
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
		this->SendDataToPort();
	}
}


//
// CONNECT TO COM PORT (BUTTON)
//
System::Void com_port_monitor::MainForm::buttonConnectToComPort_Click(System::Object^ sender, System::EventArgs^ e)
{
	// TODO: CONNECT TO COM PORT
	return System::Void();
}

//
// SEND DATA TO COM PORT
//
void com_port_monitor::MainForm::SendDataToPort()
{
	this->timer1->Start();
	MessageBox::Show("TEST", "TEST");
}


//
// Exit
//
System::Void com_port_monitor::MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

//
// SAVE LOGS
//
System::Void com_port_monitor::MainForm::saveLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->timer1->Stop();
	this->saveFileDialog->ShowDialog();
	String^ fileName = this->saveFileDialog->FileName;
	if (fileName != "")
	{
		System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(fileName);
		sw->WriteLine(this->textBoxConsole->Text);
		sw->Close();
	}
	this->timer1->Start();
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
}

System::Void com_port_monitor::MainForm::chartToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void com_port_monitor::MainForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	this->textBoxConsole->Text += "[" + dateTime.Now + "] INFO:\t" + info++ + Environment::NewLine;
	this->textBoxConsole->SelectionStart = this->textBoxConsole->Text->Length;
	this->textBoxConsole->ScrollToCaret();
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

