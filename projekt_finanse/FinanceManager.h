#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include "Transaction.h"
#include <vector>
#include <map>
#include <string>
#include <exception>

class FinanceManager {
private:
    std::vector<Transaction> transactions;
    std::map<std::string, double> monthlyBudget;

public:
    void addTransaction(const Transaction& transaction);
    void setMonthlyBudget(const std::string& category, double amount);

    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getCategoryTotal(const std::string& category) const;

    std::map<std::string, double> getMonthlySummary(const std::string& month) const;
    std::map<std::string, double> getYearlySummary(const std::string& year) const;
    double getAverageMonthlyExpense(const std::string& category) const;

    void generateMonthlyReport(const std::string& month, const std::string& filename) const;
    void generateYearlyReport(const std::string& year, const std::string& filename) const;
    void generateCategoryReport(const std::string& category, const std::string& filename) const;
    void generateComparisonReport(const std::string& period1, const std::string& period2, const std::string& filename) const;
    void generateTopExpensesReport(const std::string& filename) const;
    void generateExpensePieChartData(const std::string& date, const std::string& filename) const;

    void checkBudgetWarnings() const;
    std::map<std::string, double> calculateMonthlyAverageExpenses(const std::string& month) const;
};

// klasa wyj¹tku dla b³êdów transakcji
class TransactionException : public std::exception {
public:
    explicit TransactionException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

#endif // FINANCEMANAGER_H