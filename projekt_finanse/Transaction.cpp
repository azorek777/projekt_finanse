#include "Transaction.h"

// podzielenie trasakcji na typ, kategorie, date, opis i kwote
Transaction::Transaction(TransactionType type, const std::string& category, const std::string& date, const std::string& description, double amount)
    : type(type), category(category), date(date), description(description), amount(amount) {}

// metody zwracaj¹ce konkrente wartoœci
TransactionType Transaction::getType() const { return type; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }
std::string Transaction::getDescription() const { return description; }
double Transaction::getAmount() const { return amount; }