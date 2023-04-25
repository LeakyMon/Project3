#pragma once
//#include "MyForm.h"


namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoadingForm1
	/// </summary>
	public ref class LoadingForm1 : public System::Windows::Forms::Form
	{
	//private: System::Windows::Forms::Timer^ timer1;

	public:
		
		LoadingForm1(void)
		{
			InitializeComponent();
			//timer1->Enabled = true;
			//
			//TODO: Add the constructor code here
			//
			//this->Load += gcnew System::EventHandler(this, &LoadingForm1::LoadingForm1_Load);
		}
		LoadingForm1(int x) {
			InitializeComponent();


		}
		int GetProgressBarValue() { return progressBar1->Value; }
		void UpdateBar() { progressBar1->Value += 1; }
		//void LoadingForm1_Load(System::Object^ sender, System::EventArgs^ e)
		//{
			// Start the timer when the form loads
		//	timer1->Enabled = true;
		//}
		
	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoadingForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ LoadingBox;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Timer^ timer1;

	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->LoadingBox = (gcnew System::Windows::Forms::TextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// LoadingBox
			// 
			this->LoadingBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LoadingBox->Location = System::Drawing::Point(176, 113);
			this->LoadingBox->Name = L"LoadingBox";
			this->LoadingBox->Size = System::Drawing::Size(264, 38);
			this->LoadingBox->TabIndex = 0;
			this->LoadingBox->Text = L"Retrieving Results...";
			this->LoadingBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->LoadingBox->TextChanged += gcnew System::EventHandler(this, &LoadingForm1::textBox1_TextChanged);
			// 
			// progressBar1
			// 
			this->progressBar1->BackColor = System::Drawing::Color::Lime;
			this->progressBar1->Location = System::Drawing::Point(117, 198);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(369, 23);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 1;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			// 
			// LoadingForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(608, 489);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->LoadingBox);
			this->MinimumSize = System::Drawing::Size(626, 536);
			this->Name = L"LoadingForm1";
			this->Text = L"Loading...";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e){}

};
}
