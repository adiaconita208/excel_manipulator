#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

struct Transaction{
    string date;
    double quantity;
    double value;
    double price;
};

int main()
{
    ifstream inputFile;
    inputFile.open("/Users/adriandiaconita/Desktop/confirmare_tranz_eng_2.csv");
    
    map<string, vector<Transaction> > transactions;

    ofstream outputFile("results_2.csv");
    outputFile << "Date, No of FP Shares Repurchased, Average Price, Total Amount in RON, Max Price, Min Price" << endl;

    string line = "";

    while (getline(inputFile, line))
    {
        //cout << line << endl;
        istringstream iss(line);
        string date, quantityStr, valueStr, priceStr;

        if (std::getline(iss, date, ',') &&
            std::getline(iss, quantityStr, ',') &&
            std::getline(iss, valueStr, ',') &&
            std::getline(iss, priceStr, ','))
            {
                Transaction transaction;
                transaction.date = date;
                transaction.quantity = atof(quantityStr.c_str());
                transaction.value = atof(valueStr.c_str());
                transaction.price = atof(priceStr.c_str());

                transactions[date].push_back(transaction);
            }
    }

    for (const auto& entry : transactions)
    {
        const string& date = entry.first;
        const vector<Transaction>& dailyTransactions = entry.second;

        double maxPrice = 0.0;
        double minPrice = numeric_limits<double>::max();
        double sumPrices = 0.0;
        double totalValue = 0.0;
        double totalShares = 0.0;
        for (const Transaction& transaction : dailyTransactions)
        {
            totalValue += transaction.value;
            maxPrice = max(maxPrice, transaction.price);
            minPrice = min(minPrice, transaction.price);
            sumPrices += transaction.price;
            totalShares += transaction.quantity;
        }
        double averagePrice = sumPrices / dailyTransactions.size();

        //Output
        outputFile << date << "," << totalShares << "," << averagePrice << "," << totalValue << "," << maxPrice << "," << minPrice << "," << fixed << setprecision(4)  << endl;
    }
    cout << "Results written to results.csv." << std::endl;
}
        