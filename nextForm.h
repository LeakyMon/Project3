#pragma once
#include "MyForm.h"
namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	public ref class nextForm : public System::Windows::Forms::Form
	{
	public:
		nextForm(void)
		{
			InitializeComponent();
			
		}
		nextForm(int amount, int time, String^ riskLevel, std::vector<std::string> temp, std::vector<std::pair<std::string, double>> investmentAll)
		{
			// Initialize the form's components.
			InitializeComponent();

			this->textBox2->Text = "Investment Amount: " + amount;
			this->textBox3->Text = "Time Horizon: " + time;
			this->textBox4->Text +=  riskLevel;
			ClearLabels();
			for (int i = 0; i < temp.size(); i++) {
				
				UpdateLabel(temp.at(i), i);
				

			}
			int cnt = 6;
			for (auto it = investmentAll.begin(); it != investmentAll.end(); ++it) {
				UpdateLabel(std::to_string(it->second), cnt);
				cnt++;
			}
			

		}
		
		void ClearLabels() {
			this->label1->Text = "";
			this->label2->Text = "";
			this->label3->Text = "";
			this->label4->Text = "";
			this->label5->Text = "";
			this->label6->Text = "";
			this->label7->Text = "";
			this->label8->Text = "";
			this->label9->Text = "";
			this->label10->Text = "";
			this->label11->Text = "";
			this->label12->Text = "";
		}
		void FindResults(){}
		void setBackButton() { this->returnBack = true; }
		bool BackButton() { return this->returnBack; }
		void InvAmt(int x) {
			Inv = x;
		}
		void TimeSpan(int x) {
			TimeS = x;
		}
		void RiskSel(String^ s) {
			riskSel = s;
		}
		void UpdateLabel(std::string s, int labelNum) {
			int index = 0;
			int count = 0;
			for (auto x : s) {
				if (x == '.') {
					index = count;
				}
				count++;
			}
			index += 3;
			s.resize(index);
			
			String^ newString = msclr::interop::marshal_as<String^>(s);
			String^ dollar = "$ ";
			if (labelNum == 0) {
				this->label1->Text = newString;
			}
			else if (labelNum == 1) {
				this->label2->Text = newString;
			}
			else if (labelNum == 2) {
				this->label3->Text = newString;
			}
			else if (labelNum == 3) {
				this->label4->Text = newString;
			}
			else if (labelNum == 4) {
				this->label5->Text = newString;
			}
			else if (labelNum == 5) {
				//this->label6->Text;
			}
			else if (labelNum == 6) {
				this->label7->Text =  dollar + newString;
			}
			else if (labelNum == 7) {
				this->label8->Text = dollar + newString;
			}
			else if (labelNum == 8) {
				this->label9->Text = dollar + newString;
			}
			else if (labelNum == 9) {
				this->label10->Text = dollar + newString;
			}
			else if (labelNum == 10) {
				this->label11->Text = dollar + newString;
			}
			else if (labelNum == 11) {
				//this->label12->Text = dollar + newString;
			}

		}

	protected:
		
		~nextForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	protected:

		System::ComponentModel::Container ^components;
		int Inv;
		int TimeS;
		bool returnBack;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::Label^ label12;




		   String^ riskSel;

		   

	
#pragma region 
	
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(195, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(229, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Results Displayed Below";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(13, 85);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(225, 22);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"Investment Amount: $";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(13, 152);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(225, 22);
			this->textBox3->TabIndex = 2;
			this->textBox3->Text = L"Time Frame: ";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(13, 221);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(225, 22);
			this->textBox4->TabIndex = 3;
			this->textBox4->Text = L"Risk Level: ";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->label5, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label6, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->label7, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label8, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->label9, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->label10, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->label11, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->label12, 1, 5);
			this->tableLayoutPanel1->Location = System::Drawing::Point(343, 85);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 6;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 44.34783F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 55.65217F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 78)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 81)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 67)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 45)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(202, 392);
			this->tableLayoutPanel1->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 1);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(4, 116);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 16);
			this->label3->TabIndex = 2;
			this->label3->Text = L"label3";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(4, 195);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 16);
			this->label4->TabIndex = 3;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(4, 277);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(44, 16);
			this->label5->TabIndex = 4;
			this->label5->Text = L"label5";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(4, 345);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 16);
			this->label6->TabIndex = 5;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(104, 1);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(44, 16);
			this->label7->TabIndex = 6;
			this->label7->Text = L"label7";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(104, 52);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(44, 16);
			this->label8->TabIndex = 7;
			this->label8->Text = L"label8";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(104, 116);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(44, 16);
			this->label9->TabIndex = 8;
			this->label9->Text = L"label9";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(104, 195);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(51, 16);
			this->label10->TabIndex = 9;
			this->label10->Text = L"label10";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(104, 277);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(51, 16);
			this->label11->TabIndex = 10;
			this->label11->Text = L"label11";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(104, 345);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(0, 16);
			this->label12->TabIndex = 11;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Red;
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(12, 360);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(152, 89);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Return Home";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &nextForm::button1_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(343, 57);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 22);
			this->textBox5->TabIndex = 6;
			this->textBox5->Text = L"Stock Ticker";
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(449, 57);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(96, 22);
			this->textBox6->TabIndex = 7;
			this->textBox6->Text = L"Amt by Stock";
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// nextForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(608, 489);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->MinimumSize = System::Drawing::Size(626, 536);
			this->Name = L"nextForm";
			this->Text = L"Results Page";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();

	

}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
