#include "MyForm.h"
//#include "LoadingForm.h"


void main(array<System::String^>^ args) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    std::string directory = "C:/Users/jorge/Desktop/stocks/";
    double investment = 10000.0;
    std::string risk_level = "high";
    int time_horizon = 5;
    //std::vector<std::tuple<std::string, double, double>> stocks_performance;
    CustomUnorderedMap stock_data_map = read_stock_data(directory);
    std::vector<std::string> recommended_stocks = recommend_stocks(stock_data_map, risk_level, time_horizon);
    std::cout << "Top 5 stocks for your investment:\n";
    for (const auto& stock : recommended_stocks) {
        std::cout << stock << '\n';
    }
    // Allocate investment amount proportionally based on stock performance
    std::vector<std::pair<std::string, double>> investment_allocation = allocate_investment_proportionally(stocks_performance, recommended_stocks, investment);
    // Display the investment allocation
    std::cout << "Investment allocation:" << std::endl;
    for (auto it = investment_allocation.begin(); it != investment_allocation.end() - 1; ++it) {
        std::cout << it->first << ": $" << it->second << std::endl;
    }

    while (true) {

        Project3::MyForm^ form = gcnew Project3::MyForm();  
        form->GetFormInstance();
     
        if (form->GetFormInstance()->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {

            form->Close();
            Project3::MyForm^ newForm = gcnew Project3::MyForm();
            // Show the new instance of the form.
            newForm->ShowDialog();
        }
        else {
            break;
        }
    }
	//Application::Run(gcnew Project3::MyForm());
  

 
}
