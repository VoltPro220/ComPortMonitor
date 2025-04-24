#pragma once

namespace com_port_monitor
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);

	protected:
		~MainForm();

	private:
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ settingsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ toolsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ chooseComToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ aboutProgramToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ referentsToolStripMenuItem;
		System::Windows::Forms::SplitContainer^ splitContainer1;
		System::Windows::Forms::SplitContainer^ splitContainer2;
		System::Windows::Forms::TextBox^ textBoxWriteCommand;
		System::Windows::Forms::Button^ buttonSendCommand;
		System::Windows::Forms::TextBox^ textBoxConsole;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::ComboBox^ comboBoxComPorts;
	private: System::Windows::Forms::Button^ buttonConnectToComPort;


		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->chooseComToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->aboutProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->referentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			   this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->comboBoxComPorts = (gcnew System::Windows::Forms::ComboBox());
			   this->textBoxConsole = (gcnew System::Windows::Forms::TextBox());
			   this->buttonSendCommand = (gcnew System::Windows::Forms::Button());
			   this->textBoxWriteCommand = (gcnew System::Windows::Forms::TextBox());
			   this->buttonConnectToComPort = (gcnew System::Windows::Forms::Button());
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			   this->splitContainer1->Panel1->SuspendLayout();
			   this->splitContainer1->Panel2->SuspendLayout();
			   this->splitContainer1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			   this->splitContainer2->Panel1->SuspendLayout();
			   this->splitContainer2->Panel2->SuspendLayout();
			   this->splitContainer2->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3)
			   {
				   this->fileToolStripMenuItem,
					   this->toolsToolStripMenuItem, this->aboutProgramToolStripMenuItem
			   });
			   resources->ApplyResources(this->menuStrip1, L"menuStrip1");
			   this->menuStrip1->Name = L"menuStrip1";
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
			   {
				   this->settingsToolStripMenuItem,
					   this->exitToolStripMenuItem
			   });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   resources->ApplyResources(this->fileToolStripMenuItem, L"fileToolStripMenuItem");
			   // 
			   // settingsToolStripMenuItem
			   // 
			   this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
			   resources->ApplyResources(this->settingsToolStripMenuItem, L"settingsToolStripMenuItem");
			   // 
			   // exitToolStripMenuItem
			   // 
			   this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			   resources->ApplyResources(this->exitToolStripMenuItem, L"exitToolStripMenuItem");
			   // 
			   // toolsToolStripMenuItem
			   // 
			   this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->chooseComToolStripMenuItem });
			   this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			   resources->ApplyResources(this->toolsToolStripMenuItem, L"toolsToolStripMenuItem");
			   // 
			   // chooseComToolStripMenuItem
			   // 
			   this->chooseComToolStripMenuItem->Name = L"chooseComToolStripMenuItem";
			   resources->ApplyResources(this->chooseComToolStripMenuItem, L"chooseComToolStripMenuItem");
			   // 
			   // aboutProgramToolStripMenuItem
			   // 
			   this->aboutProgramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->referentsToolStripMenuItem });
			   this->aboutProgramToolStripMenuItem->Name = L"aboutProgramToolStripMenuItem";
			   resources->ApplyResources(this->aboutProgramToolStripMenuItem, L"aboutProgramToolStripMenuItem");
			   // 
			   // referentsToolStripMenuItem
			   // 
			   this->referentsToolStripMenuItem->Name = L"referentsToolStripMenuItem";
			   resources->ApplyResources(this->referentsToolStripMenuItem, L"referentsToolStripMenuItem");
			   // 
			   // splitContainer1
			   // 
			   this->splitContainer1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			   resources->ApplyResources(this->splitContainer1, L"splitContainer1");
			   this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			   this->splitContainer1->Name = L"splitContainer1";
			   // 
			   // splitContainer1.Panel1
			   // 
			   this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			   // 
			   // splitContainer1.Panel2
			   // 
			   this->splitContainer1->Panel2->Controls->Add(this->buttonSendCommand);
			   this->splitContainer1->Panel2->Controls->Add(this->textBoxWriteCommand);
			   // 
			   // splitContainer2
			   // 
			   this->splitContainer2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			   resources->ApplyResources(this->splitContainer2, L"splitContainer2");
			   this->splitContainer2->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			   this->splitContainer2->Name = L"splitContainer2";
			   // 
			   // splitContainer2.Panel1
			   // 
			   this->splitContainer2->Panel1->Controls->Add(this->buttonConnectToComPort);
			   this->splitContainer2->Panel1->Controls->Add(this->label1);
			   this->splitContainer2->Panel1->Controls->Add(this->comboBoxComPorts);
			   // 
			   // splitContainer2.Panel2
			   // 
			   this->splitContainer2->Panel2->Controls->Add(this->textBoxConsole);
			   // 
			   // label1
			   // 
			   resources->ApplyResources(this->label1, L"label1");
			   this->label1->Name = L"label1";
			   // 
			   // comboBoxComPorts
			   // 
			   this->comboBoxComPorts->FormattingEnabled = true;
			   resources->ApplyResources(this->comboBoxComPorts, L"comboBoxComPorts");
			   this->comboBoxComPorts->Name = L"comboBoxComPorts";
			   // 
			   // textBoxConsole
			   // 
			   resources->ApplyResources(this->textBoxConsole, L"textBoxConsole");
			   this->textBoxConsole->Name = L"textBoxConsole";
			   this->textBoxConsole->ReadOnly = true;
			   this->textBoxConsole->TabStop = false;
			   // 
			   // buttonSendCommand
			   // 
			   resources->ApplyResources(this->buttonSendCommand, L"buttonSendCommand");
			   this->buttonSendCommand->Name = L"buttonSendCommand";
			   this->buttonSendCommand->UseVisualStyleBackColor = true;
			   this->buttonSendCommand->Click += gcnew System::EventHandler(this, &MainForm::buttonSendCommand_Click);
			   // 
			   // textBoxWriteCommand
			   // 
			   resources->ApplyResources(this->textBoxWriteCommand, L"textBoxWriteCommand");
			   this->textBoxWriteCommand->Name = L"textBoxWriteCommand";
			   this->textBoxWriteCommand->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxWriteCommand_KeyDown);
			   // 
			   // buttonConnectToComPort
			   // 
			   resources->ApplyResources(this->buttonConnectToComPort, L"buttonConnectToComPort");
			   this->buttonConnectToComPort->Name = L"buttonConnectToComPort";
			   this->buttonConnectToComPort->UseVisualStyleBackColor = true;
			   this->buttonConnectToComPort->Click += gcnew System::EventHandler(this, &MainForm::buttonConnectToComPort_Click);
			   // 
			   // MainForm
			   // 
			   resources->ApplyResources(this, L"$this");
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->Controls->Add(this->splitContainer1);
			   this->Controls->Add(this->menuStrip1);
			   this->Name = L"MainForm";
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::mainForm_KeyDown);
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->splitContainer1->Panel1->ResumeLayout(false);
			   this->splitContainer1->Panel2->ResumeLayout(false);
			   this->splitContainer1->Panel2->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			   this->splitContainer1->ResumeLayout(false);
			   this->splitContainer2->Panel1->ResumeLayout(false);
			   this->splitContainer2->Panel1->PerformLayout();
			   this->splitContainer2->Panel2->ResumeLayout(false);
			   this->splitContainer2->Panel2->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			   this->splitContainer2->ResumeLayout(false);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion

		   System::Void buttonSendCommand_Click(System::Object^ sender, System::EventArgs^ e);
		   System::Void mainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		   void SendDataToPort();

		   System::Void textBoxWriteCommand_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		   System::Void buttonConnectToComPort_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
