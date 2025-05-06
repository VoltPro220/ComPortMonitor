#pragma once

namespace com_port_monitor
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class SettingsForm : public System::Windows::Forms::Form
	{
	public:
		SettingsForm(void)
		{
			InitializeComponent();
		}

	protected:
		~SettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::SplitContainer^ splitContainer1;
		System::Windows::Forms::Button^ buttonSuccess;
		System::Windows::Forms::Button^ buttonCancel;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::ComboBox^ comboBoxLang;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxLang = (gcnew System::Windows::Forms::ComboBox());
			this->buttonSuccess = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->label1);
			this->splitContainer1->Panel1->Controls->Add(this->comboBoxLang);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->buttonSuccess);
			this->splitContainer1->Panel2->Controls->Add(this->buttonCancel);
			this->splitContainer1->Size = System::Drawing::Size(486, 465);
			this->splitContainer1->SplitterDistance = 386;
			this->splitContainer1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
								  static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(49, 59);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Язык";
			// 
			// comboBoxLang
			// 
			this->comboBoxLang->FormattingEnabled = true;
			this->comboBoxLang->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Русский", L"English" });
			this->comboBoxLang->Location = System::Drawing::Point(26, 86);
			this->comboBoxLang->Name = L"comboBoxLang";
			this->comboBoxLang->Size = System::Drawing::Size(121, 21);
			this->comboBoxLang->TabIndex = 0;
			this->comboBoxLang->Text = L"Русский";
			// 
			// buttonSuccess
			// 
			this->buttonSuccess->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonSuccess->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
										 static_cast<System::Byte>(204)));
			this->buttonSuccess->Location = System::Drawing::Point(207, 17);
			this->buttonSuccess->Name = L"buttonSuccess";
			this->buttonSuccess->Size = System::Drawing::Size(141, 46);
			this->buttonSuccess->TabIndex = 1;
			this->buttonSuccess->Text = L"Применить";
			this->buttonSuccess->UseVisualStyleBackColor = true;
			this->buttonSuccess->Click += gcnew System::EventHandler(this, &SettingsForm::buttonSuccess_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
										static_cast<System::Byte>(204)));
			this->buttonCancel->Location = System::Drawing::Point(354, 17);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(120, 46);
			this->buttonCancel->TabIndex = 0;
			this->buttonCancel->Text = L"Отмена";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &SettingsForm::buttonCancel_Click);
			// 
			// SettingsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(486, 465);
			this->Controls->Add(this->splitContainer1);
			this->MinimumSize = System::Drawing::Size(310, 381);
			this->Name = L"SettingsForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonSuccess_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
