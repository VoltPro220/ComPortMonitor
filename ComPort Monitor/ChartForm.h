#pragma once
#include "src/SerialOperation/stducp.h"
#include "MainForm.h"

namespace com_port_monitor
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ChartForm
	/// </summary>
	public ref class ChartForm : public System::Windows::Forms::Form
	{
	public:
		ChartForm(void)
		{
			InitializeComponent();
			this->updateComPorts();
		}

	protected:
		~ChartForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::SplitContainer^ splitContainer1;
		System::Windows::Forms::DataVisualization::Charting::Chart^ chart;
		System::Windows::Forms::Button^ buttonStart;
		System::Windows::Forms::Button^ buttonClose;
		System::Windows::Forms::Button^ buttonClearChart;
		System::ComponentModel::Container^ components;

		System::Threading::Thread^ th;
		HANDLE hPortCom;
		double x = 0, data;
		bool isConnectedToComPort = false;
		int baudRate;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ comboBoxBaudRate;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::ComboBox^ comboBoxComPorts;
		System::Windows::Forms::Button^ buttonUpdateComPorts;
		String^ comPort;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->buttonUpdateComPorts = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBoxBaudRate = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBoxComPorts = (gcnew System::Windows::Forms::ComboBox());
			this->buttonClearChart = (gcnew System::Windows::Forms::Button());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->buttonClose = (gcnew System::Windows::Forms::Button());
			this->chart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->buttonUpdateComPorts);
			this->splitContainer1->Panel1->Controls->Add(this->label2);
			this->splitContainer1->Panel1->Controls->Add(this->comboBoxBaudRate);
			this->splitContainer1->Panel1->Controls->Add(this->label3);
			this->splitContainer1->Panel1->Controls->Add(this->comboBoxComPorts);
			this->splitContainer1->Panel1->Controls->Add(this->buttonClearChart);
			this->splitContainer1->Panel1->Controls->Add(this->buttonStart);
			this->splitContainer1->Panel1->Controls->Add(this->buttonClose);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->chart);
			this->splitContainer1->Size = System::Drawing::Size(935, 670);
			this->splitContainer1->SplitterDistance = 176;
			this->splitContainer1->TabIndex = 0;
			// 
			// buttonUpdateComPorts
			// 
			this->buttonUpdateComPorts->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonUpdateComPorts->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonUpdateComPorts->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold));
			this->buttonUpdateComPorts->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->buttonUpdateComPorts->Location = System::Drawing::Point(26, 440);
			this->buttonUpdateComPorts->Name = L"buttonUpdateComPorts";
			this->buttonUpdateComPorts->Size = System::Drawing::Size(128, 39);
			this->buttonUpdateComPorts->TabIndex = 9;
			this->buttonUpdateComPorts->Text = L"Обновить";
			this->buttonUpdateComPorts->UseVisualStyleBackColor = true;
			this->buttonUpdateComPorts->Click += gcnew System::EventHandler(this, &ChartForm::buttonUpdateComPorts_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label2->Location = System::Drawing::Point(22, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(43, 20);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Бод";
			// 
			// comboBoxBaudRate
			// 
			this->comboBoxBaudRate->FormattingEnabled = true;
			this->comboBoxBaudRate->Items->AddRange(gcnew cli::array< System::Object^  >(14)
			{
				L"300", L"600", L"750", L"1200", L"2400",
					L"4800", L"9600", L"19200", L"31250", L"38400", L"57600", L"74880", L"115200", L"250000"
			});
			this->comboBoxBaudRate->Location = System::Drawing::Point(26, 156);
			this->comboBoxBaudRate->Name = L"comboBoxBaudRate";
			this->comboBoxBaudRate->Size = System::Drawing::Size(77, 21);
			this->comboBoxBaudRate->TabIndex = 6;
			this->comboBoxBaudRate->Text = L"9600";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->label3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label3->Location = System::Drawing::Point(22, 34);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(48, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"COM";
			// 
			// comboBoxComPorts
			// 
			this->comboBoxComPorts->FormattingEnabled = true;
			this->comboBoxComPorts->Location = System::Drawing::Point(26, 71);
			this->comboBoxComPorts->Name = L"comboBoxComPorts";
			this->comboBoxComPorts->Size = System::Drawing::Size(77, 21);
			this->comboBoxComPorts->TabIndex = 7;
			// 
			// buttonClearChart
			// 
			this->buttonClearChart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
											static_cast<System::Byte>(204)));
			this->buttonClearChart->Location = System::Drawing::Point(26, 502);
			this->buttonClearChart->Name = L"buttonClearChart";
			this->buttonClearChart->Size = System::Drawing::Size(128, 38);
			this->buttonClearChart->TabIndex = 2;
			this->buttonClearChart->Text = L"Очистить";
			this->buttonClearChart->UseVisualStyleBackColor = true;
			this->buttonClearChart->Click += gcnew System::EventHandler(this, &ChartForm::buttonClearChart_Click);
			// 
			// buttonStart
			// 
			this->buttonStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
									   static_cast<System::Byte>(204)));
			this->buttonStart->Location = System::Drawing::Point(26, 563);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(128, 38);
			this->buttonStart->TabIndex = 1;
			this->buttonStart->Text = L"Подключиться";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &ChartForm::buttonStart_Click);
			// 
			// buttonClose
			// 
			this->buttonClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
									   static_cast<System::Byte>(204)));
			this->buttonClose->Location = System::Drawing::Point(26, 620);
			this->buttonClose->Name = L"buttonClose";
			this->buttonClose->Size = System::Drawing::Size(128, 38);
			this->buttonClose->TabIndex = 0;
			this->buttonClose->Text = L"Закрыть";
			this->buttonClose->UseVisualStyleBackColor = true;
			this->buttonClose->Click += gcnew System::EventHandler(this, &ChartForm::buttonClose_Click);
			// 
			// chart
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart->ChartAreas->Add(chartArea1);
			this->chart->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Name = L"Legend1";
			this->chart->Legends->Add(legend1);
			this->chart->Location = System::Drawing::Point(0, 0);
			this->chart->Name = L"chart";
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Color = System::Drawing::Color::Red;
			series1->Legend = L"Legend1";
			series1->LegendText = L"Chart1";
			series1->Name = L"Series1";
			this->chart->Series->Add(series1);
			this->chart->Size = System::Drawing::Size(755, 670);
			this->chart->TabIndex = 0;
			this->chart->Text = L"chart1";
			// 
			// ChartForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(935, 670);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"ChartForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Chart Monitor";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ChartForm::ChartForm_FormClosed);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonClearChart_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonUpdateComPorts_Click(System::Object^ sender, System::EventArgs^ e);
		void updateComPorts();
		bool connectToPort();
		void disconnect();
		void readComPort(Object^);
		System::Void ChartForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	};
}
