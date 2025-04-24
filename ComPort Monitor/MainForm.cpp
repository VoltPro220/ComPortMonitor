#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

com_port_monitor::MainForm::MainForm(void)
{
	this->InitializeComponent();
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
	MessageBox::Show("TEST", "TEST");
}





int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	com_port_monitor::MainForm form;
	Application::Run(% form);
	return 0;
}

