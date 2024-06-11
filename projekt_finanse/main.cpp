#include "UserInterface.h"
#include "FinanceManager.h"
#include "Transaction.h"

int main() {
    FinanceManager manager;

    // Dodanie przyk³adowych transakcji
    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2020-01-15", "Monthly salary", 5000));
    manager.addTransaction(Transaction(TransactionType::Expense, "Rent", "2020-01-01", "Monthly rent", 1200));
    manager.addTransaction(Transaction(TransactionType::Expense, "Groceries", "2020-01-05", "Weekly groceries", 150));
    manager.addTransaction(Transaction(TransactionType::Income, "Freelance", "2020-02-20", "Freelance work", 800));
    manager.addTransaction(Transaction(TransactionType::Expense, "Entertainment", "2020-02-25", "Concert tickets", 100));

    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2020-03-15", "Monthly salary", 5000));
    manager.addTransaction(Transaction(TransactionType::Expense, "Utilities", "2020-03-01", "Electricity bill", 100));
    manager.addTransaction(Transaction(TransactionType::Expense, "Dining", "2020-03-05", "Dinner at restaurant", 70));
    manager.addTransaction(Transaction(TransactionType::Income, "Bonus", "2020-04-15", "Performance bonus", 1000));
    manager.addTransaction(Transaction(TransactionType::Expense, "Travel", "2020-04-20", "Train tickets", 200));

    // Transactions for 2021
    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2021-01-15", "Monthly salary", 5100));
    manager.addTransaction(Transaction(TransactionType::Expense, "Rent", "2021-01-01", "Monthly rent", 1250));
    manager.addTransaction(Transaction(TransactionType::Expense, "Groceries", "2021-01-05", "Weekly groceries", 160));
    manager.addTransaction(Transaction(TransactionType::Income, "Freelance", "2021-02-20", "Freelance work", 850));
    manager.addTransaction(Transaction(TransactionType::Expense, "Entertainment", "2021-02-25", "Theater tickets", 110));

    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2021-03-15", "Monthly salary", 5100));
    manager.addTransaction(Transaction(TransactionType::Expense, "Utilities", "2021-03-01", "Water bill", 90));
    manager.addTransaction(Transaction(TransactionType::Expense, "Dining", "2021-03-05", "Lunch at cafe", 50));
    manager.addTransaction(Transaction(TransactionType::Income, "Bonus", "2021-04-15", "Performance bonus", 1050));
    manager.addTransaction(Transaction(TransactionType::Expense, "Travel", "2021-04-20", "Flight tickets", 250));

    // Transactions for 2022
    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2022-01-15", "Monthly salary", 5200));
    manager.addTransaction(Transaction(TransactionType::Expense, "Rent", "2022-01-01", "Monthly rent", 1300));
    manager.addTransaction(Transaction(TransactionType::Expense, "Groceries", "2022-01-05", "Weekly groceries", 170));
    manager.addTransaction(Transaction(TransactionType::Income, "Freelance", "2022-02-20", "Freelance work", 900));
    manager.addTransaction(Transaction(TransactionType::Expense, "Entertainment", "2022-02-25", "Movie tickets", 120));

    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2022-03-15", "Monthly salary", 5200));
    manager.addTransaction(Transaction(TransactionType::Expense, "Utilities", "2022-03-01", "Internet bill", 80));
    manager.addTransaction(Transaction(TransactionType::Expense, "Dining", "2022-03-05", "Brunch at diner", 60));
    manager.addTransaction(Transaction(TransactionType::Income, "Bonus", "2022-04-15", "Performance bonus", 1100));
    manager.addTransaction(Transaction(TransactionType::Expense, "Travel", "2022-04-20", "Hotel stay", 300));

    // Transactions for 2023
    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2023-01-15", "Monthly salary", 5300));
    manager.addTransaction(Transaction(TransactionType::Expense, "Rent", "2023-01-01", "Monthly rent", 1350));
    manager.addTransaction(Transaction(TransactionType::Expense, "Groceries", "2023-01-05", "Weekly groceries", 180));
    manager.addTransaction(Transaction(TransactionType::Income, "Freelance", "2023-02-20", "Freelance work", 950));
    manager.addTransaction(Transaction(TransactionType::Expense, "Entertainment", "2023-02-25", "Concert tickets", 130));

    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2023-03-15", "Monthly salary", 5300));
    manager.addTransaction(Transaction(TransactionType::Expense, "Utilities", "2023-03-01", "Gas bill", 110));
    manager.addTransaction(Transaction(TransactionType::Expense, "Dining", "2023-03-05", "Dinner at pub", 70));
    manager.addTransaction(Transaction(TransactionType::Income, "Bonus", "2023-04-15", "Performance bonus", 1150));
    manager.addTransaction(Transaction(TransactionType::Expense, "Travel", "2023-04-20", "Bus tickets", 100));

    // Transactions for 2024
    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2024-01-15", "Monthly salary", 5400));
    manager.addTransaction(Transaction(TransactionType::Expense, "Rent", "2024-01-01", "Monthly rent", 1400));
    manager.addTransaction(Transaction(TransactionType::Expense, "Groceries", "2024-01-05", "Weekly groceries", 190));
    manager.addTransaction(Transaction(TransactionType::Income, "Freelance", "2024-02-20", "Freelance work", 1000));
    manager.addTransaction(Transaction(TransactionType::Expense, "Entertainment", "2024-02-25", "Theater tickets", 140));

    manager.addTransaction(Transaction(TransactionType::Income, "Salary", "2024-03-15", "Monthly salary", 5400));
    manager.addTransaction(Transaction(TransactionType::Expense, "Utilities", "2024-03-01", "Electricity bill", 120));
    manager.addTransaction(Transaction(TransactionType::Expense, "Dining", "2024-03-05", "Lunch at bakery", 40));
    manager.addTransaction(Transaction(TransactionType::Income, "Bonus", "2024-04-15", "Performance bonus", 1200));
    manager.addTransaction(Transaction(TransactionType::Expense, "Travel", "2024-04-20", "Train tickets", 150));

    UserInterface ui(manager);
    ui.start(); // Uruchomienie interfejsu u¿ytkownika

    return 0;
}