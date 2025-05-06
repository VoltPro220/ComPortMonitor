#include "ChartForm.h"

System::Void com_port_monitor::ChartForm::buttonStart_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->buttonStart->Text == "Подключиться")
	{
		if (this->connectToPort())
		{
			this->buttonStart->Text = "Отключится";
		}
		else
		{
			MessageBox::Show("Пожалуйста, проверьте корректность данных COM порта и повторите попытку", "Ошибка",
							 MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	else
	{
		this->disconnect();
		this->buttonStart->Text = "Подключиться";
	}
}

System::Void com_port_monitor::ChartForm::buttonClose_Click(System::Object^ sender, System::EventArgs^ e)
{
	com_port_monitor::MainForm^ f = gcnew com_port_monitor::MainForm;
	f->Show();
	this->Close();
}

System::Void com_port_monitor::ChartForm::buttonClearChart_Click(System::Object^ sender, System::EventArgs^ e)
{}

System::Void com_port_monitor::ChartForm::buttonUpdateComPorts_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->isConnectedToComPort)
		this->updateComPorts();
}

void com_port_monitor::ChartForm::updateComPorts()
{
	this->comboBoxComPorts->Items->Clear();
	this->comboBoxComPorts->ResetText();
	for (int i = 1; i <= 256; i++)
	{
		if (check_com_port(i) != -1)
		{
			this->comboBoxComPorts->Items->Add("COM" + i);
		}
	}

}

bool com_port_monitor::ChartForm::connectToPort()
{
	this->hPortCom = open_com_port(this->hPortCom,
								   (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->comPort),
								   this->baudRate);
	if (this->hPortCom != INVALID_HANDLE_VALUE)
	{
		this->isConnectedToComPort = true;
		this->th = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(this, &ChartForm::readComPort));
		this->th->Start();
		return true;
	}
	return false;
}

void com_port_monitor::ChartForm::disconnect()
{
	if (this->isConnectedToComPort)
	{
		CloseHandle(this->hPortCom);
		this->isConnectedToComPort = false;
		this->th->Abort();
		this->hPortCom = nullptr;
	}
}

void com_port_monitor::ChartForm::readComPort(Object^ p)
{
	while (true)
	{
		if (this->isConnectedToComPort)
		{
			char* buf = const_cast<char*>(read_from_com_port(this->hPortCom));
			if (buf != NULL)
			{
				String^ str = gcnew String(buf);
				try
				{
					this->data = Convert::ToDouble(str);
				}
				catch (...)
				{

				}
				this->chart->Series[0]->Points->AddXY(x, data);
				x++;
			}
			free(buf);
		}
	}
}

System::Void com_port_monitor::ChartForm::ChartForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	if (this->isConnectedToComPort)
	{
		CloseHandle(this->hPortCom);
		this->isConnectedToComPort = false;
		this->th->Abort();
		this->hPortCom = nullptr;
	}
}


