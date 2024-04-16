// Transaction.h
#include <string>
#include <vector>

class Transaction {
private:
    std::string type;
    std::string category;
    std::string date;
    std::string description;
    double amount;

public:
    Transaction(std::string type, std::string category, std::string date, std::string description, double amount);
    void print() const;
};

class TransactionManager {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(std::string type, std::string category, std::string date, std::string description, double amount);
    void printTransactions();
};