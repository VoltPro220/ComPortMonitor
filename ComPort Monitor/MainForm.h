#pragma once
#include "src/SerialOperation/stducp.h"
#include <string>

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
		System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
		System::Windows::Forms::SplitContainer^ splitContainer1;
		System::Windows::Forms::SplitContainer^ splitContainer2;
		System::Windows::Forms::TextBox^ textBoxWriteCommand;
		System::Windows::Forms::Button^ buttonSendCommand;
		System::Windows::Forms::TextBox^ textBoxConsole;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::ComboBox^ comboBoxComPorts;
		System::Windows::Forms::Button^ buttonConnectToComPort;
		System::Windows::Forms::ToolStripMenuItem^ saveLogsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ printLogsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ baudToolStripMenuItem;
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog;
		System::Windows::Forms::PrintDialog^ printDialog;
		System::Drawing::Printing::PrintDocument^ printDocument;
		System::Windows::Forms::ToolStripMenuItem^ gitHubToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ documentationToolStripMenuItem;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ comboBox1;
		System::Windows::Forms::ToolStripMenuItem^ chartToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ connectToolStripMenuItem;
		System::Windows::Forms::Button^ buttonUpdateComPorts;
		System::Windows::Forms::Button^ buttonClearConsole;

		int info = 0;
		DateTime dateTime;
		HANDLE hPortCom;
		bool isConnectedToComPort = false;
		System::Threading::Thread^ th;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveLogsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printLogsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->connectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chooseComToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baudToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gitHubToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->documentationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->buttonClearConsole = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->buttonConnectToComPort = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxComPorts = (gcnew System::Windows::Forms::ComboBox());
			this->textBoxConsole = (gcnew System::Windows::Forms::TextBox());
			this->buttonSendCommand = (gcnew System::Windows::Forms::Button());
			this->textBoxWriteCommand = (gcnew System::Windows::Forms::TextBox());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->printDialog = (gcnew System::Windows::Forms::PrintDialog());
			this->printDocument = (gcnew System::Drawing::Printing::PrintDocument());
			this->buttonUpdateComPorts = (gcnew System::Windows::Forms::Button());
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
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4)
			{
				this->saveLogsToolStripMenuItem,
					this->printLogsToolStripMenuItem, this->settingsToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			resources->ApplyResources(this->fileToolStripMenuItem, L"fileToolStripMenuItem");
			// 
			// saveLogsToolStripMenuItem
			// 
			this->saveLogsToolStripMenuItem->Name = L"saveLogsToolStripMenuItem";
			resources->ApplyResources(this->saveLogsToolStripMenuItem, L"saveLogsToolStripMenuItem");
			this->saveLogsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveLogsToolStripMenuItem_Click);
			// 
			// printLogsToolStripMenuItem
			// 
			this->printLogsToolStripMenuItem->Name = L"printLogsToolStripMenuItem";
			resources->ApplyResources(this->printLogsToolStripMenuItem, L"printLogsToolStripMenuItem");
			this->printLogsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::printLogsToolStripMenuItem_Click);
			// 
			// settingsToolStripMenuItem
			// 
			this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
			resources->ApplyResources(this->settingsToolStripMenuItem, L"settingsToolStripMenuItem");
			this->settingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::settingsToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			resources->ApplyResources(this->exitToolStripMenuItem, L"exitToolStripMenuItem");
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4)
			{
				this->connectToolStripMenuItem,
					this->chooseComToolStripMenuItem, this->chartToolStripMenuItem, this->baudToolStripMenuItem
			});
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			resources->ApplyResources(this->toolsToolStripMenuItem, L"toolsToolStripMenuItem");
			// 
			// connectToolStripMenuItem
			// 
			this->connectToolStripMenuItem->Name = L"connectToolStripMenuItem";
			resources->ApplyResources(this->connectToolStripMenuItem, L"connectToolStripMenuItem");
			this->connectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::connectToolStripMenuItem_Click);
			// 
			// chooseComToolStripMenuItem
			// 
			this->chooseComToolStripMenuItem->Name = L"chooseComToolStripMenuItem";
			resources->ApplyResources(this->chooseComToolStripMenuItem, L"chooseComToolStripMenuItem");
			// 
			// chartToolStripMenuItem
			// 
			this->chartToolStripMenuItem->Name = L"chartToolStripMenuItem";
			resources->ApplyResources(this->chartToolStripMenuItem, L"chartToolStripMenuItem");
			this->chartToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::chartToolStripMenuItem_Click);
			// 
			// baudToolStripMenuItem
			// 
			this->baudToolStripMenuItem->Name = L"baudToolStripMenuItem";
			resources->ApplyResources(this->baudToolStripMenuItem, L"baudToolStripMenuItem");
			// 
			// aboutProgramToolStripMenuItem
			// 
			this->aboutProgramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3)
			{
				this->gitHubToolStripMenuItem,
					this->documentationToolStripMenuItem, this->aboutToolStripMenuItem
			});
			this->aboutProgramToolStripMenuItem->Name = L"aboutProgramToolStripMenuItem";
			resources->ApplyResources(this->aboutProgramToolStripMenuItem, L"aboutProgramToolStripMenuItem");
			// 
			// gitHubToolStripMenuItem
			// 
			this->gitHubToolStripMenuItem->Name = L"gitHubToolStripMenuItem";
			resources->ApplyResources(this->gitHubToolStripMenuItem, L"gitHubToolStripMenuItem");
			this->gitHubToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::gitHubToolStripMenuItem_Click);
			// 
			// documentationToolStripMenuItem
			// 
			this->documentationToolStripMenuItem->Name = L"documentationToolStripMenuItem";
			resources->ApplyResources(this->documentationToolStripMenuItem, L"documentationToolStripMenuItem");
			this->documentationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::documentationToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			resources->ApplyResources(this->aboutToolStripMenuItem, L"aboutToolStripMenuItem");
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
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
			this->splitContainer2->Panel1->Controls->Add(this->buttonUpdateComPorts);
			this->splitContainer2->Panel1->Controls->Add(this->buttonClearConsole);
			this->splitContainer2->Panel1->Controls->Add(this->label2);
			this->splitContainer2->Panel1->Controls->Add(this->comboBox1);
			this->splitContainer2->Panel1->Controls->Add(this->buttonConnectToComPort);
			this->splitContainer2->Panel1->Controls->Add(this->label1);
			this->splitContainer2->Panel1->Controls->Add(this->comboBoxComPorts);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->textBoxConsole);
			// 
			// buttonClearConsole
			// 
			resources->ApplyResources(this->buttonClearConsole, L"buttonClearConsole");
			this->buttonClearConsole->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonClearConsole->Name = L"buttonClearConsole";
			this->buttonClearConsole->UseVisualStyleBackColor = true;
			this->buttonClearConsole->Click += gcnew System::EventHandler(this, &MainForm::buttonClearConsole_Click);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			resources->ApplyResources(this->comboBox1, L"comboBox1");
			this->comboBox1->Name = L"comboBox1";
			// 
			// buttonConnectToComPort
			// 
			resources->ApplyResources(this->buttonConnectToComPort, L"buttonConnectToComPort");
			this->buttonConnectToComPort->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonConnectToComPort->Name = L"buttonConnectToComPort";
			this->buttonConnectToComPort->UseVisualStyleBackColor = true;
			this->buttonConnectToComPort->Click += gcnew System::EventHandler(this, &MainForm::buttonConnectToComPort_Click);
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
			this->buttonSendCommand->Cursor = System::Windows::Forms::Cursors::Hand;
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
			// printDialog
			// 
			this->printDialog->AllowSomePages = true;
			this->printDialog->ShowHelp = true;
			this->printDialog->UseEXDialog = true;
			// 
			// printDocument
			// 
			this->printDocument->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &MainForm::printDocument_PrintPage);
			// 
			// buttonUpdateComPorts
			// 
			resources->ApplyResources(this->buttonUpdateComPorts, L"buttonUpdateComPorts");
			this->buttonUpdateComPorts->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonUpdateComPorts->Name = L"buttonUpdateComPorts";
			this->buttonUpdateComPorts->UseVisualStyleBackColor = true;
			this->buttonUpdateComPorts->Click += gcnew System::EventHandler(this, &MainForm::buttonUpdateComPorts_Click);
			// 
			// MainForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
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
		System::Void textBoxWriteCommand_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void buttonConnectToComPort_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void saveLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void printLogsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void printDocument_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e);
		System::Void gitHubToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void documentationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void settingsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void chartToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void connectToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonClearConsole_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
		System::Void buttonUpdateComPorts_Click(System::Object^ sender, System::EventArgs^ e);
		void updateComPorts();
		void sendDataToPort();
		bool connectToPort();
		void disconnectPortCom();
		void readComPort(Object^);
	};
}
