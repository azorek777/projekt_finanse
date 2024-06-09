#include "FinanceManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>

void FinanceManager::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

void FinanceManager::setMonthlyBudget(const std::string& category, double amount) {
    monthlyBudget[category] = amount;
}

double FinanceManager::getTotalIncome() const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Income) {
            total += t.getAmount();
        }
    }
    return total;
}

double FinanceManager::getTotalExpenses() const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            total += t.getAmount();
        }
    }
    return total;
}

double FinanceManager::getCategoryTotal(const std::string& category) const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t.getCategory() == category) {
            total += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount());
        }
    }
    return total;
}

std::map<std::string, double> FinanceManager::getMonthlySummary(const std::string& month) const {
    std::map<std::string, double> summary;
    for (const auto& t : transactions) {
        if (t.getDate().substr(0, 7) == month) {
            summary[t.getCategory()] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount());
        }
    }
    return summary;
}

std::map<std::string, double> FinanceManager::getYearlySummary(const std::string& year) const {
    std::map<std::string, double> summary;
    for (const auto& t : transactions) {
        if (t.getDate().substr(0, 4) == year) {
            summary[t.getCategory()] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount());
        }
    }
    return summary;
}

double FinanceManager::getAverageMonthlyExpense(const std::string& category) const {
    std::map<std::string, double> monthlyTotals;
    for (const auto& t : transactions) {
        if (t.getCategory() == category) {
            std::string month = t.getDate().substr(0, 7);
            monthlyTotals[month] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount());
        }
    }
    double total = 0.0;
    for (const auto& [month, amount] : monthlyTotals) {
        total += amount;
    }
    return total / monthlyTotals.size();
}

void FinanceManager::generateMonthlyReport(const std::string& month, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Monthly Report for " << month << "\n";
        file << "----------------------------------\n";
        for (const auto& t : transactions) {
            if (t.getDate().substr(0, 7) == month) {
                file << t.getDate() << " | " << t.getCategory() << " | " << t.getAmount() << " | " << t.getDescription() << "\n";
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void FinanceManager::generateYearlyReport(const std::string& year, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Yearly Report for " << year << "\n";
        file << "----------------------------------\n";
        for (const auto& t : transactions) {
            if (t.getDate().substr(0, 4) == year) {
                file << t.getDate() << " | " << t.getCategory() << " | " << t.getAmount() << " | " << t.getDescription() << "\n";
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void FinanceManager::generateCategoryReport(const std::string& category, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Category Report for " << category << "\n";
        file << "----------------------------------\n";
        for (const auto& t : transactions) {
            if (t.getCategory() == category) {
                file << t.getDate() << " | " << t.getAmount() << " | " << t.getDescription() << "\n";
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void FinanceManager::generateComparisonReport(const std::string& period1, const std::string& period2, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Comparison Report for " << period1 << " and " << period2 << "\n";
        file << "----------------------------------\n";

        std::map<std::string, double> summary1 = getMonthlySummary(period1);
        std::map<std::string, double> summary2 = getMonthlySummary(period2);

        file << "Category | " << period1 << " | " << period2 << "\n";
        for (const auto& [category, amount1] : summary1) {
            double amount2 = summary2[category];
            file << category << " | " << amount1 << " | " << amount2 << "\n";
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void FinanceManager::generateTopExpensesReport(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Top Expenses Report\n";
        file << "----------------------------------\n";

        std::vector<Transaction> sortedExpenses = transactions;
        std::sort(sortedExpenses.begin(), sortedExpenses.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() > b.getAmount();
            });

        for (const auto& t : sortedExpenses) {
            if (t.getType() == TransactionType::Expense) {
                file << t.getDate() << " | " << t.getCategory() << " | " << t.getAmount() << " | " << t.getDescription() << "\n";
            }
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void FinanceManager::checkBudgetWarnings() const {
    for (const auto& [category, budget] : monthlyBudget) {
        double total = getCategoryTotal(category);
        if (total > budget) {
            std::cout << "Warning: Budget exceeded for category: " << category << "\n";
        }
    }
}

void FinanceManager::generateExpensePieChartData(const std::string& date, const std::string& filename) const {
    std::map<std::string, double> expenseSummary;
    double totalExpenses = 0.0;
    bool isYear = (date.length() == 4); // Check if input is a year or month

    // Summarize expenses by category for the specified date
    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            std::string transactionDate = t.getDate().substr(0, date.length());
            if (transactionDate == date) {
                expenseSummary[t.getCategory()] += t.getAmount();
                totalExpenses += t.getAmount();
            }
        }
    }

    // Prepare data for URL
    std::ostringstream url;
    url << "https://image-charts.com/chart?cht=p3&chs=700x300";

    // Add categories with values and percentages to the URL
    url << "&chl=";
    bool first = true;
    for (const auto& [category, amount] : expenseSummary) {
        if (!first) {
            url << "|";
        }
        double percentage = (amount / totalExpenses) * 100.0;
        url << category << " (" << std::fixed << std::setprecision(2) << amount << " = " << percentage << "%)";
        first = false;
    }

    // Add amounts as percentages to the URL
    url << "&chd=t:";
    first = true;
    for (const auto& [category, amount] : expenseSummary) {
        if (!first) {
            url << ",";
        }
        double percentage = (amount / totalExpenses) * 100.0;
        url << std::fixed << std::setprecision(2) << percentage;
        first = false;
    }

    // Print the generated URL
    std::cout << "Pie Chart URL: " << url.str() << std::endl;

    // Save data to file
    std::ofstream file(filename + ".txt");
    if (file.is_open()) {
        file << "Category,Amount,Percentage\n";
        for (const auto& [category, amount] : expenseSummary) {
            double percentage = (amount / totalExpenses) * 100.0;
            file << category << "," << amount << "," << std::fixed << std::setprecision(2) << percentage << "%\n";
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << ".txt\n";
    }
}

std::map<std::string, double> FinanceManager::calculateMonthlyAverageExpenses(const std::string& month) const {
    std::map<std::string, std::map<std::string, double>> monthlyExpenses;
    std::map<std::string, int> monthCounts;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense && t.getDate().substr(0, 7) == month) {
            std::string category = t.getCategory();
            monthlyExpenses[category][month] += t.getAmount();
            monthCounts[category]++;
        }
    }

    std::map<std::string, double> averageExpenses;
    for (const auto& [category, months] : monthlyExpenses) {
        double total = 0.0;
        for (const auto& [month, amount] : months) {
            total += amount;
        }
        averageExpenses[category] = total / monthCounts[category];
    }

    return averageExpenses;
}




