#include "SettingsForm.h"

System::Void com_port_monitor::SettingsForm::buttonCancel_Click(System::Object^ sender, System::EventArgs^ e)
{
	Close();
}

System::Void com_port_monitor::SettingsForm::buttonSuccess_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->comboBoxLang->Text == "Русский")
	{
		System::Threading::Thread::CurrentThread->CurrentUICulture = Globalization::CultureInfo::GetCultureInfo("ru-RU");
		System::Threading::Thread::CurrentThread->CurrentCulture = Globalization::CultureInfo::GetCultureInfo("ru-RU");
	}
	else if (this->comboBoxLang->Text == "English")
	{
		System::Threading::Thread::CurrentThread->CurrentUICulture = Globalization::CultureInfo::GetCultureInfo("en");
		System::Threading::Thread::CurrentThread->CurrentCulture = Globalization::CultureInfo::GetCultureInfo("en");
	}
	Close();
}
