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

void com_port_monitor::MainForm::InitializeComponent(void)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
	this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
	this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->íàéñòðîéêèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->âûõîäToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->èíñòðóìåíòûToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->cOMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->îÏðîãðàììåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->ñïðàâêàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
	this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->label3 = (gcnew System::Windows::Forms::Label());
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
		this->ôàéëToolStripMenuItem,
			this->èíñòðóìåíòûToolStripMenuItem, this->îÏðîãðàììåToolStripMenuItem
	});
	resources->ApplyResources(this->menuStrip1, L"menuStrip1");
	this->menuStrip1->Name = L"menuStrip1";
	// 
	// ôàéëToolStripMenuItem
	// 
	this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2)
	{
		this->íàéñòðîéêèToolStripMenuItem,
			this->âûõîäToolStripMenuItem
	});
	this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
	resources->ApplyResources(this->ôàéëToolStripMenuItem, L"ôàéëToolStripMenuItem");
	// 
	// íàéñòðîéêèToolStripMenuItem
	// 
	this->íàéñòðîéêèToolStripMenuItem->Name = L"íàéñòðîéêèToolStripMenuItem";
	resources->ApplyResources(this->íàéñòðîéêèToolStripMenuItem, L"íàéñòðîéêèToolStripMenuItem");
	// 
	// âûõîäToolStripMenuItem
	// 
	this->âûõîäToolStripMenuItem->Name = L"âûõîäToolStripMenuItem";
	resources->ApplyResources(this->âûõîäToolStripMenuItem, L"âûõîäToolStripMenuItem");
	// 
	// èíñòðóìåíòûToolStripMenuItem
	// 
	this->èíñòðóìåíòûToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->cOMToolStripMenuItem });
	this->èíñòðóìåíòûToolStripMenuItem->Name = L"èíñòðóìåíòûToolStripMenuItem";
	resources->ApplyResources(this->èíñòðóìåíòûToolStripMenuItem, L"èíñòðóìåíòûToolStripMenuItem");
	// 
	// cOMToolStripMenuItem
	// 
	this->cOMToolStripMenuItem->Name = L"cOMToolStripMenuItem";
	resources->ApplyResources(this->cOMToolStripMenuItem, L"cOMToolStripMenuItem");
	// 
	// îÏðîãðàììåToolStripMenuItem
	// 
	this->îÏðîãðàììåToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ñïðàâêàToolStripMenuItem });
	this->îÏðîãðàììåToolStripMenuItem->Name = L"îÏðîãðàììåToolStripMenuItem";
	resources->ApplyResources(this->îÏðîãðàììåToolStripMenuItem, L"îÏðîãðàììåToolStripMenuItem");
	// 
	// ñïðàâêàToolStripMenuItem
	// 
	this->ñïðàâêàToolStripMenuItem->Name = L"ñïðàâêàToolStripMenuItem";
	resources->ApplyResources(this->ñïðàâêàToolStripMenuItem, L"ñïðàâêàToolStripMenuItem");
	// 
	// splitContainer1
	// 
	this->splitContainer1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
	resources->ApplyResources(this->splitContainer1, L"splitContainer1");
	this->splitContainer1->Name = L"splitContainer1";
	// 
	// splitContainer1.Panel1
	// 
	this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
	// 
	// splitContainer1.Panel2
	// 
	this->splitContainer1->Panel2->Controls->Add(this->label1);
	// 
	// splitContainer2
	// 
	this->splitContainer2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
	resources->ApplyResources(this->splitContainer2, L"splitContainer2");
	this->splitContainer2->Name = L"splitContainer2";
	// 
	// splitContainer2.Panel1
	// 
	this->splitContainer2->Panel1->Controls->Add(this->label3);
	// 
	// splitContainer2.Panel2
	// 
	this->splitContainer2->Panel2->Controls->Add(this->label2);
	// 
	// label1
	// 
	resources->ApplyResources(this->label1, L"label1");
	this->label1->Name = L"label1";
	// 
	// label2
	// 
	resources->ApplyResources(this->label2, L"label2");
	this->label2->Name = L"label2";
	// 
	// label3
	// 
	resources->ApplyResources(this->label3, L"label3");
	this->label3->Name = L"label3";
	// 
	// MainForm
	// 
	resources->ApplyResources(this, L"$this");
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->Controls->Add(this->splitContainer1);
	this->Controls->Add(this->menuStrip1);
	this->Name = L"MainForm";
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







int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	com_port_monitor::MainForm form;
	Application::Run(% form);
	return 0;
}

