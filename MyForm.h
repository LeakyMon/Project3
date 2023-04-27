#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <filesystem>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <msclr/marshal_cppstd.h> //Library to turn String^ into std::string
#include "LoadingForm.h"
#include "nextForm.h"


namespace fs = std::filesystem;
using namespace System;
using namespace System::Windows::Forms;


namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;


	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		bool Cont = false;
		MyForm(void)
		{
			InitializeComponent();
		}
		void ResetVals() {

			this->aInvestment->Text = "";
			this->aHorizon->Text = "";

			String^ selectedItem = "Select your Level of Risk"; // get the selected item
			this->SelectRiskMenu->Text = selectedItem;
		}
		Project3::MyForm^ GetFormInstance(){ return gcnew Project3::MyForm(); }

		void CloseForm(Project3::MyForm^ form)
		{
			form->Close();
		}
		int GetInvestmentAmt() { return this->investmentAmt; }
		int GetTimeAmt() { return this->timeAmt; }
		String^ getRiskSel() { return this->riskSel; }

	protected:
	
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ line;
	protected:
	protected:
	private: System::Windows::Forms::Label^ Title;
	private: System::Windows::Forms::Label^ qInvestment;
	private: System::Windows::Forms::Label^ qTime;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ SelectRiskMenu;
	private: System::Windows::Forms::ToolStripMenuItem^ highToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ mediumToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ lowToolStripMenuItem;
	private: System::Windows::Forms::TextBox^ aInvestment;
	private: System::Windows::Forms::TextBox^ aHorizon;
	private: System::Windows::Forms::Button^ btnContinue;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::ComponentModel::Container ^components;
	private:
		LoadingForm1^ loadingForm;
		MyForm^ newForm1;
		nextForm^ nextForm;
		int investmentAmt;
		int timeAmt;
		String^ riskSel;
#pragma region 
		
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->line = (gcnew System::Windows::Forms::TextBox());
			this->Title = (gcnew System::Windows::Forms::Label());
			this->qInvestment = (gcnew System::Windows::Forms::Label());
			this->qTime = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->SelectRiskMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->highToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mediumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aInvestment = (gcnew System::Windows::Forms::TextBox());
			this->aHorizon = (gcnew System::Windows::Forms::TextBox());
			this->btnContinue = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// line
			// 
			this->line->BackColor = System::Drawing::SystemColors::MenuText;
			this->line->Location = System::Drawing::Point(12, 44);
			this->line->Name = L"line";
			this->line->Size = System::Drawing::Size(569, 22);
			this->line->TabIndex = 1;
			this->line->Text = L"---------------------------------------------------------------------------------"
				L"-----------------------------------------------------------------------------";
			// 
			// Title
			// 
			this->Title->AutoSize = true;
			this->Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Title->Location = System::Drawing::Point(89, 9);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(439, 32);
			this->Title->TabIndex = 2;
			this->Title->Text = L"Stock Recommendation Engine";
			this->Title->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// qInvestment
			// 
			this->qInvestment->AutoSize = true;
			this->qInvestment->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->qInvestment->Location = System::Drawing::Point(13, 95);
			this->qInvestment->Name = L"qInvestment";
			this->qInvestment->Size = System::Drawing::Size(319, 25);
			this->qInvestment->TabIndex = 3;
			this->qInvestment->Text = L"How much would you like to invest\?";
			this->qInvestment->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// qTime
			// 
			this->qTime->AutoSize = true;
			this->qTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->qTime->Location = System::Drawing::Point(16, 208);
			this->qTime->Name = L"qTime";
			this->qTime->Size = System::Drawing::Size(316, 25);
			this->qTime->TabIndex = 4;
			this->qTime->Text = L"What is your time horizon\? (1-5yrs)";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->SelectRiskMenu });
			this->menuStrip1->Location = System::Drawing::Point(26, 314);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(247, 33);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// SelectRiskMenu
			// 
			this->SelectRiskMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->highToolStripMenuItem,
					this->mediumToolStripMenuItem, this->lowToolStripMenuItem
			});
			this->SelectRiskMenu->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SelectRiskMenu->Name = L"SelectRiskMenu";
			this->SelectRiskMenu->Size = System::Drawing::Size(239, 29);
			this->SelectRiskMenu->Text = L"Select your Level of Risk";
			this->SelectRiskMenu->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// highToolStripMenuItem
			// 
			this->highToolStripMenuItem->Name = L"highToolStripMenuItem";
			this->highToolStripMenuItem->Size = System::Drawing::Size(168, 30);
			this->highToolStripMenuItem->Text = L"High";
			this->highToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::highToolStripMenuItem_Click);
			// 
			// mediumToolStripMenuItem
			// 
			this->mediumToolStripMenuItem->Name = L"mediumToolStripMenuItem";
			this->mediumToolStripMenuItem->Size = System::Drawing::Size(168, 30);
			this->mediumToolStripMenuItem->Text = L"Medium";
			this->mediumToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::mediumToolStripMenuItem_Click);
			// 
			// lowToolStripMenuItem
			// 
			this->lowToolStripMenuItem->Name = L"lowToolStripMenuItem";
			this->lowToolStripMenuItem->Size = System::Drawing::Size(168, 30);
			this->lowToolStripMenuItem->Text = L"Low";
			this->lowToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::lowToolStripMenuItem_Click);
			// 
			// aInvestment
			// 
			this->aInvestment->Location = System::Drawing::Point(18, 150);
			this->aInvestment->Name = L"aInvestment";
			this->aInvestment->Size = System::Drawing::Size(314, 22);
			this->aInvestment->TabIndex = 6;
			this->aInvestment->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// aHorizon
			// 
			this->aHorizon->Location = System::Drawing::Point(18, 265);
			this->aHorizon->Name = L"aHorizon";
			this->aHorizon->Size = System::Drawing::Size(314, 22);
			this->aHorizon->TabIndex = 7;
			this->aHorizon->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// btnContinue
			// 
			this->btnContinue->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnContinue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnContinue->Location = System::Drawing::Point(433, 442);
			this->btnContinue->Name = L"btnContinue";
			this->btnContinue->Size = System::Drawing::Size(137, 35);
			this->btnContinue->TabIndex = 8;
			this->btnContinue->Text = L"Continue";
			this->btnContinue->UseVisualStyleBackColor = true;
			this->btnContinue->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(379, 111);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(191, 247);
			this->pictureBox1->TabIndex = 9;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(608, 489);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnContinue);
			this->Controls->Add(this->aHorizon);
			this->Controls->Add(this->aInvestment);
			this->Controls->Add(this->qTime);
			this->Controls->Add(this->qInvestment);
			this->Controls->Add(this->Title);
			this->Controls->Add(this->line);
			this->Controls->Add(this->menuStrip1);
			this->MinimumSize = System::Drawing::Size(626, 536);
			this->Name = L"MyForm";
			this->Text = L"New Engine";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
		
#pragma endregion


	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}


private: System::Void RiskLevel_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
}
private: System::Void highToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedItem = "High"; // get the selected item
	this->SelectRiskMenu->Text = selectedItem;
	//MessageBox::Show("You selected: " + selectedItem);
}

	   //CONTINUE BUTTON IF THE USER WANTS TO GO TO THE NEXT PAGE
private: System::Void ShowLoadingScreen() {
		 
		// Create an instance of LoadingForm
		CloseForm(GetFormInstance());
		loadingForm = gcnew Project3::LoadingForm1();
		
		loadingForm->Show();
		this->investmentAmt = GetInvestmentAmt();
		this->timeAmt = GetTimeAmt();
		this->riskSel = getRiskSel();


		
		nextForm = gcnew Project3::nextForm(investmentAmt, timeAmt, riskSel);
	
		this->Close();
		//Loops until data is loaded
		for (int i = 0; i < 99; i++)
		{
			int loadingValue = loadingForm->GetProgressBarValue();
		
			loadingForm->UpdateBar();
			
			System::Threading::Thread::Sleep(5);
		}
		
		loadingForm->Close();
		nextForm->ShowDialog();
		
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	
	bool Continue = validInput();

	if (Continue){ //If continue is true, we move onto the next form
		this->Cont = true;
		ShowLoadingScreen();
	}
	else {
		this->Cont = false;
	}	
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void toolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedItem = "Select your Level of Risk"; // get the selected item
	this->SelectRiskMenu->Text = selectedItem;
}
private: System::Void mediumToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedItem = "Medium"; // get the selected item
	this->SelectRiskMenu->Text = selectedItem;
	//MessageBox::Show("You selected: " + selectedItem);
}
private: System::Void lowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedItem = "Low"; // get the selected item
	this->SelectRiskMenu->Text = selectedItem;
	//MessageBox::Show("You selected: " + selectedItem);
}

bool validInput()
{
	bool Continue = true;
	String^ moneyInput = this->aInvestment->Text;
	String^ timeInput = this->aHorizon->Text;
	String^ riskInput = this->SelectRiskMenu->Text;

	//If they left something blank
	if (String::IsNullOrEmpty(moneyInput) || String::IsNullOrEmpty(timeInput) || riskInput == "Select your Level of Risk") {
		//MessageBox::Show("Please complete all fields");
		Continue = false;
	}
	else {
		//Makes sure the user inputs whole numbers
		std::string tempString = marshal_as<std::string>(moneyInput);
		for (int i = 0; i < tempString.length(); i++) {
			if (tempString[i] >= '0' && tempString[i] <= '9') {} //Checks if its a valid integer
			else {
				//MessageBox::Show("Please use whole numbers only");
				Continue = false;
				break;
			}
		}
		tempString = marshal_as<std::string>(timeInput);

		//Makes sure the user inputs whole numbers
		for (int i = 0; i < tempString.length(); i++) {
			if (tempString[i] >= '0' && tempString[i] <= '9') {} //Checks if its a valid integer
			else {
				//MessageBox::Show("Please use whole numbers only");
				Continue = false;
				break;
			}
		}
		int moneyVal = Convert::ToInt32(moneyInput);
		int timeVal = Convert::ToInt32(timeInput);

		this->investmentAmt = moneyVal;
		this->timeAmt = timeVal;
		this->riskSel = riskInput;

		if (timeVal < 0 || timeVal > 5) { //If the number of years arent in range
			Continue = false;

		}
	}
	return Continue;
}
public:
bool getCont() {
	 
	if (this->Cont == false) { //Trying to make it reset all the input
		this->aInvestment->Text = "";
		this->aHorizon->Text = "";
		this->SelectRiskMenu->Text = "Select your Level of Risk";
	}
	return this->Cont;
}
private:

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}
};




}
