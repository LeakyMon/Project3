#pragma once
#define NOMINMAX
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
#include <cmath>
#include <msclr\marshal_cppstd.h>
#include <msclr/marshal_cppstd.h> //Library to turn String^ into std::string
#include "LoadingForm.h"
#include "nextForm.h"

namespace fs = std::filesystem;
using namespace System;
using namespace System::Windows::Forms;




struct StockData {
	std::string ticker;
	std::string date;
	double open;
	double high;
	double low;
	double close;
	long volume;
};
class CustomUnorderedMap {
public:
	//CustomUnorderedMap();

	CustomUnorderedMap read_stock_data(const std::string& directory);

	CustomUnorderedMap getMap() {
		CustomUnorderedMap stock_data_map;
		std::string directory = "C:/Users/hecto/source/Programming/Projects/Project3/Project3/all_stocks/Stocks";
		double investment = 10000.0;
		std::string risk_level = "high";
		int time_horizon = 5;
		return stock_data_map = read_stock_data(directory);
	}
	void insert(const std::string& key, const StockData& value) {
		root = insert_helper(root, key, value);
	}
	std::vector<StockData>& get(const std::string& key) {
		TreeNode* node = search(root, key);
		if (node) {
			return node->values;
		}
		throw std::runtime_error("Key not found");
	}
	std::vector<std::pair<std::string, std::vector<StockData>>> get_all() const {
		std::vector<std::pair<std::string, std::vector<StockData>>> all_data;
		in_order_traversal(root, all_data);
		return all_data;
	}
private:
	
	struct TreeNode {
		std::string key;
		std::vector<StockData> values;
		TreeNode* left;
		TreeNode* right;
		TreeNode(const std::string& k, const StockData& v) : key(k), values({ v }), left(nullptr), right(nullptr) {}
	};
	TreeNode* root = nullptr;
	TreeNode* insert_helper(TreeNode* node, const std::string& key, const StockData& value) {
		if (node == nullptr) {
			return new TreeNode(key, value);
		}
		if (key == node->key) {
			node->values.push_back(value);
		}
		else if (key < node->key) {
			node->left = insert_helper(node->left, key, value);
		}
		else {
			node->right = insert_helper(node->right, key, value);
		}
		return node;
	}
	TreeNode* search(TreeNode* node, const std::string& key) {
		if (node == nullptr || key == node->key) {
			return node;
		}
		if (key < node->key) {
			return search(node->left, key);
		}
		return search(node->right, key);
	}
	void in_order_traversal(TreeNode* node, std::vector<std::pair<std::string, std::vector<StockData>>>& all_data) const {
		if (node != nullptr) {
			in_order_traversal(node->left, all_data);
			all_data.push_back({ node->key, node->values });
			in_order_traversal(node->right, all_data);
		}
	}
};

CustomUnorderedMap CustomUnorderedMap::read_stock_data(const std::string& directory)
{
	CustomUnorderedMap stock_data_map;
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.path().extension() == ".csv") {
			std::string file_name = entry.path().filename().string();
			std::string ticker = file_name.substr(0, file_name.find("_"));
			std::ifstream file(entry.path().string());
			if (!file.is_open()) {
				std::cerr << "File Not Found??? " << file_name << std::endl;
				throw std::runtime_error("Error: Unable to open file " + file_name);
			}
			std::string line;
			std::getline(file, line); // Skip header
			while (std::getline(file, line)) {
				std::istringstream iss(line);
				std::string date_str, open_str, high_str, low_str, close_str, volume_str;
				std::getline(iss, date_str, ',');
				std::getline(iss, open_str, ',');
				std::getline(iss, high_str, ',');
				std::getline(iss, low_str, ',');
				std::getline(iss, close_str, ',');
				std::getline(iss, volume_str);
				StockData data;
				data.ticker = ticker;
				data.date = date_str;
				data.open = std::stod(open_str);
				data.high = std::stod(high_str);
				data.low = std::stod(low_str);
				data.close = std::stod(close_str);
				data.volume = std::stol(volume_str);
				stock_data_map.insert(ticker, data);
			}
			// Close the file
			file.close();
		}
	}
	return stock_data_map;
}

std::vector<std::tuple<std::string, double, double>> stocks_performance;
double calculate_volatility(const std::vector<StockData>& data) {
	if (data.size() < 2) {
		return 0.0;
	}
	double sum_of_squared_returns = 0.0;
	double previous_close = data[0].close;
	for (std::size_t i = 1; i < data.size(); ++i) {
		double daily_return = (data[i].close - previous_close) / previous_close;
		sum_of_squared_returns += daily_return * daily_return;
		previous_close = data[i].close;
	}
	double mean_of_squared_returns = sum_of_squared_returns / (data.size() - 1);
	double daily_volatility = std::sqrt(mean_of_squared_returns);
	// Annualize the daily volatility
	double annualized_volatility = daily_volatility * std::sqrt(252);
	return annualized_volatility;
}
double calculate_performance(const std::vector<StockData>& data, int time_horizon) {
	if (data.size() < 2) {
		return 0.0;
	}
	// Find the earliest date within the time horizon
	std::string target_date = data.back().date;
	int target_year = std::stoi(target_date.substr(0, 4)) - time_horizon;
	target_date.replace(0, 4, std::to_string(target_year));
	// Find the stock data at the start of the time horizon
	auto start_data = std::find_if(data.rbegin(), data.rend(), [&](const StockData& stock_data) {
		return stock_data.date <= target_date;
		});
	if (start_data == data.rend()) {
		return 0.0;
	}
	double start_price = start_data->close;
	double end_price = data.back().close;
	// Calculate the Compound Annual Growth Rate (CAGR)
	double cagr = std::pow((end_price / start_price), (1.0 / time_horizon)) - 1;
	return cagr;
}
std::vector<std::string> filter_stocks_by_risk(const std::vector<std::tuple<std::string, double, double>>& stocks_performance, const std::string& risk_level) {
	std::vector<std::string> filtered_stocks;
	// Define risk level thresholds
	double low_risk_threshold = 0.15;
	double medium_risk_threshold = 0.35;
	for (const auto& stock_performance : stocks_performance) {
		const std::string& stock_symbol = std::get<0>(stock_performance);
		double volatility = std::get<2>(stock_performance);
		if (risk_level == "low" && volatility <= low_risk_threshold) {
			filtered_stocks.push_back(stock_symbol);
		}
		else if (risk_level == "medium" && volatility > low_risk_threshold && volatility <= medium_risk_threshold) {
			filtered_stocks.push_back(stock_symbol);
		}
		else if (risk_level == "high" && volatility > medium_risk_threshold) {
			filtered_stocks.push_back(stock_symbol);
		}
	}
	return filtered_stocks;
}
std::vector<std::string> recommend_stocks(const CustomUnorderedMap& stock_data, std::string risk_level, int time_horizon) {

	//std::vector<std::tuple<std::string, double, double>> stocks_performance;
	for (const auto& stock : stock_data.get_all()) {
		double performance = calculate_performance(stock.second, time_horizon);
		double volatility = calculate_volatility(stock.second);
		stocks_performance.push_back(std::make_tuple(stock.first, performance, volatility));
	}
	// Filter stocks based on the risk level
	std::vector<std::string> filtered_stocks = filter_stocks_by_risk(stocks_performance, risk_level);
	// Sort filtered stocks based on performance
	std::sort(filtered_stocks.begin(), filtered_stocks.end(), [&](const std::string& a, const std::string& b) {
		double performance_a = std::get<1>(*std::find_if(stocks_performance.begin(), stocks_performance.end(), [&](const std::tuple<std::string, double, double>& stock_performance) {
			return std::get<0>(stock_performance) == a;
			}));
	double performance_b = std::get<1>(*std::find_if(stocks_performance.begin(), stocks_performance.end(), [&](const std::tuple<std::string, double, double>& stock_performance) {
		return std::get<0>(stock_performance) == b;
		}));
	return performance_a > performance_b;
		});
	// Select the top 5 stocks
	std::vector<std::string> recommended_stocks;
	for (std::size_t i = 0; i <= 5 && i < filtered_stocks.size(); ++i) {
		recommended_stocks.push_back(filtered_stocks[i]);
	}
	return recommended_stocks;
}
std::vector<std::pair<std::string, double>> allocate_investment_proportionally(const std::vector<std::tuple<std::string, double, double>>& stocks_performance, const std::vector<std::string>& stock_picks, double investment) {
	// 1. Calculate the total performance of the top 5 stocks and the minimum performance
	double total_performance = 0.0;
	double min_performance = std::numeric_limits<double>::max();
	for (const auto& stock : stocks_performance) {
		if (std::find(stock_picks.begin(), stock_picks.end(), std::get<0>(stock)) != stock_picks.end()) {
			total_performance += std::get<1>(stock);
			min_performance = std::min(min_performance, std::get<1>(stock));
		}
	}
	// 2. Shift the performance values to be positive
	total_performance += (-min_performance) * stock_picks.size();
	// 3. Create an empty vector to store the stock tickers and their corresponding investment amounts
	std::vector<std::pair<std::string, double>> investment_allocation;
	// 4. Iterate through the stock_picks vector and create a pair of stock ticker and investment amount
	for (const auto& stock_ticker : stock_picks) {
		// Find the stock's performance in the stocks_performance vector
		auto it = std::find_if(stocks_performance.begin(), stocks_performance.end(), [&](const auto& stock) {
			return std::get<0>(stock) == stock_ticker;
			});
		if (it != stocks_performance.end()) {
			// Calculate the investment amount for this stock based on its shifted performance relative to the total performance
			double stock_performance = std::get<1>(*it) + (-min_performance);
			double investment_for_stock = investment * (stock_performance / total_performance);
			// Add the stock ticker and investment amount to the investment_allocation vector
			investment_allocation.push_back(std::make_pair(stock_ticker, investment_for_stock));
		}
	}
	// 5. Return the investment_allocation vector containing the stock tickers and their corresponding investment amounts
	return investment_allocation;
}




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
		CustomUnorderedMap& tempObj;

		MyForm(CustomUnorderedMap& obj) : tempObj(obj) {
		
			InitializeComponent();
		}
		
		void ResetVals() {

			this->aInvestment->Text = "";
			this->aHorizon->Text = "";

			String^ selectedItem = "Select your Level of Risk"; // get the selected item
			this->SelectRiskMenu->Text = selectedItem;
		}
		Project3::MyForm^ GetFormInstance(){ return gcnew Project3::MyForm(tempObj); }

		
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
	String^ selectedItem = "high"; // get the selected item
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

		std::string tempRiskSel = msclr::interop::marshal_as<std::string>(getRiskSel());
		//Before the nextForm is made we gotta figure out how to find the recommend stocks in 
		//This area
		std::vector<std::string> recommended_stocks = recommend_stocks(tempObj, tempRiskSel, timeAmt);

		//std::vector<std::pair<std::string, double>> temp;
		
		std::vector<std::pair<std::string, double>> investment_allocation = allocate_investment_proportionally(stocks_performance, recommended_stocks, investmentAmt);

	
		nextForm = gcnew Project3::nextForm(investmentAmt, timeAmt, riskSel, recommended_stocks, investment_allocation);
	
		stocks_performance.clear();
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
		//nextForm->Close();
		
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
	String^ selectedItem = "medium"; // get the selected item
	this->SelectRiskMenu->Text = selectedItem;
	//MessageBox::Show("You selected: " + selectedItem);
}
private: System::Void lowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ selectedItem = "low"; // get the selected item
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
