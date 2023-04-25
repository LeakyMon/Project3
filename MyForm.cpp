#include "MyForm.h"
//#include "LoadingForm.h"

using namespace System;
using namespace System::Windows::Forms;
namespace fs = std::filesystem;




struct StockData {
    std::string ticker;
    std::string date;
    double open;
    double high;
    double low;
    double close;
    long volume;

};

void main(array<System::String^>^ args) {

	/*
	std::string directory = "C:/Users/hecto/source/Programming/Projects/Project3/Project3/all_stocks/Stocks";
	std::map<std::string, std::vector<StockData>> stock_data_map;
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.path().extension() == ".csv") {
			std::string file_name = entry.path().filename().string();
			std::string ticker = file_name.substr(0, file_name.find("_"));
			std::ifstream file(entry.path().string());
			if (!file.is_open()) {
				std::cerr << "File Not Found??? " << file_name << std::endl;
				//return 1;
			}
			std::string line;
			std::getline(file, line);
			std::vector<StockData>& stock_data = stock_data_map[ticker];
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
				stock_data.push_back(data);
			}
			// Close the file
			file.close();
		}
	}
	std::cout << "AAPL stock data:" << std::endl;
	const auto& aapl_data = stock_data_map["AAPL"];
	for (const auto& data : aapl_data) {
		std::cout << data.ticker << ", " << data.date << ", " << data.open << ", " << data.high
			<< ", " << data.low << ", " << data.close << ", " << data.volume << std::endl;
	}
	std::cout << "MSFT stock data:" << std::endl;
	const auto& msft_data = stock_data_map["MSFT"];
	for (const auto& data : msft_data) {
		std::cout << data.ticker << ", " << data.date << ", " << data.open << ", " << data.high
			<< ", " << data.low << ", " << data.close << ", " << data.volume << std::endl;
	}

	*/
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
	//ShowLoadingScreen();
    Application::Run(gcnew Project3::MyForm());

 
}

