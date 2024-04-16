// Transaction.cpp
#include <iostream>
#include "Transaction.h"

Transaction::Transaction(std::string type, std::string category, std::string date, std::string description, double amount)
    : type(type), category(category), date(date), description(description), amount(amount) {}

void Transaction::print() const {
    std::cout << "Typ: " << type << ", Kategoria: " << category << ", Data: " << date << ", Opis: " << description << ", Wartosc: " << amount << std::endl;
}

void TransactionManager::addTransaction(std::string type, std::string category, std::string date, std::string description, double amount) {
    if (amount == 0) {
        throw std::invalid_argument("Wartosc transakcji nie moze wynosic 0.");
    }
    transactions.push_back(Transaction(type, category, date, description, amount));
}

void TransactionManager::printTransactions() {
    std::cout << "Lista transakcji: " << std::endl;
    for (const Transaction& transaction : transactions) {
        transaction.print();
    }
}