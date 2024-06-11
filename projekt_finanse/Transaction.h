#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// typ wyliczeniowy dla typu transakcji
enum class TransactionType { Income, Expense };

class Transaction {
private:
    TransactionType type;
    std::string category;
    std::string date;
    std::string description;
    double amount;

public:
    Transaction(TransactionType type, const std::string& category, const std::string& date, const std::string& description, double amount);

    TransactionType getType() const;
    std::string getCategory() const;
    std::string getDate() const;
    std::string getDescription() const;
    double getAmount() const;
};

#endif // TRANSACTION_H