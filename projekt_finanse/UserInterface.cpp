﻿#include "UserInterface.h"
#include <iostream>
#include <limits>

// Metoda dodająca transakcję
void UserInterface::addTransaction() {
    try {
        std::string typeStr, category, date, description; // typy tekstowe
		double amount; // double bo liczba może być zmienno przeciskowa
        std::cout << "Enter transaction type (income/expense): ";
        std::cin >> typeStr;
		// sprawdzamy czy wprowadzony tekst jest poprawny
        if (typeStr != "income" && typeStr != "expense") {
            throw TransactionException("Invalid transaction type. Must be 'income' or 'expense'.");
        }

		TransactionType type = (typeStr == "income") ? TransactionType::Income : TransactionType::Expense; // sprawdzamy czy podany jest income czy expense

        // zbieranie danych
        std::cout << "Enter category: ";
        std::cin >> category;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
		// sprawdzamy czy data ma odpowiedni format
        if (date.length() != 10) {
            throw TransactionException("Invalid date format. Must be YYYY-MM-DD.");
        }

        std::cout << "Enter description: ";
        std::cin.ignore(); // usuwa znak nowej linii
		std::getline(std::cin, description); // wczytywanie linii do despription
        std::cout << "Enter amount: ";
        std::cin >> amount;
        if (amount <= 0) {
            throw TransactionException("Amount must be positive."); // kwota nie może byc minusowa
        }
        if (std::cin.fail() || std::cin.peek() != '\n') {
            // Wyczyść stan błędu std::cin
            std::cin.clear();
            // Wyczyść bufor wejścia, aby usunąć pozostałości po nieprawidłowym wprowadzeniu
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw TransactionException("Invalid input. Should be a number.");
        }

		Transaction transaction(type, category, date, description, amount); // tworzenie transakcji
		manager.addTransaction(transaction); // dodanie transakcji
    }
    catch (const TransactionException& e) {
		std::cerr << "Error: " << e.what() << "\n"; // wyświetlenie napisu error + co jest w błędzie
    }
}
// metoda ustawiająca budżet
void UserInterface::setBudget() {
    std::string category;
    double amount;
    std::cout << "Enter category: ";
    std::cin >> category;
    std::cout << "Enter budget amount: ";
    std::cin >> amount;
	// sprawdzanie czy wprowadzony typ danych jest niepoprawny lub czy kolejnym znakiem nie jest znak nowej linii
    if (std::cin.fail() || std::cin.peek() != '\n') {
        // Wyczyść stan błędu std::cin
        std::cin.clear();
		// czyszczenie strumienia wejściowego aż do znaku nowej linii lub maksymalnej liczby znaków
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw TransactionException("Invalid input. Should be a number.");
    }

    manager.setMonthlyBudget(category, amount);
}
 
// metoda pokazująca podsumowanie
void UserInterface::displaySummary() const {
    std::cout << "Enter period (YYYY-MM for month, YYYY for year): ";
    std::string period;
    std::cin >> period;

	// jeżeli długość to 7 to jest to miesiąc a jeżeli 4 to rok
    if (period.length() == 7) {
        auto summary = manager.getMonthlySummary(period);
        std::cout << "Monthly Summary for " << period << "\n";
		// przejscie przez każdy element kontenera summary
        // const %auto używa sie żeby przejść po każdym elemencie bez kopiowania elementów i zmieniania ich wartosci
        for (const auto& [category, amount] : summary) {
            std::cout << "Category: " << category << ", Total: " << amount << "\n";
        }
    }
    else if (period.length() == 4) {
		auto summary = manager.getYearlySummary(period); // automatyczne określenie typu zmiennej
        std::cout << "Yearly Summary for " << period << "\n";
        for (const auto& [category, amount] : summary) {
            std::cout << "Category: " << category << ", Total: " << amount << "\n";
        }
    }
    else {
        std::cout << "Invalid period format.\n";
    }
}
// generowanie raportów
void UserInterface::generateReports() const {
    std::string choice;
    std::cout << "Generate report (monthly/yearly/category/comparison/top/piechart): ";
    std::cin >> choice;

	// wybor rodzaju raportu
    if (choice == "monthly") {
        std::string month, filename;
        std::cout << "Enter month (YYYY-MM): ";
        std::cin >> month;
        std::cout << "Enter filename for monthly report: ";
        std::cin >> filename;
		// sprawdzanie czy plik ma rozszerzenie txt i ewentualne dodanie go
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateMonthlyReport(month, filename);
    }
    else if (choice == "yearly") {
        std::string year, filename;
        std::cout << "Enter year (YYYY): ";
        std::cin >> year;
        std::cout << "Enter filename for yearly report: ";
        std::cin >> filename;
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateYearlyReport(year, filename);
    }
    else if (choice == "category") {
        std::string category, filename;
        std::cout << "Enter category: ";
        std::cin >> category;
        std::cout << "Enter filename for category report: ";
        std::cin >> filename;
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateCategoryReport(category, filename);
    }
    else if (choice == "comparison") {
        std::string period1, period2, filename;
        std::cout << "Enter first period (YYYY-MM): ";
        std::cin >> period1;
        std::cout << "Enter second period (YYYY-MM): ";
        std::cin >> period2;
        std::cout << "Enter filename for comparison report: ";
        std::cin >> filename;
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateComparisonReport(period1, period2, filename);
    }
    else if (choice == "top") {
        std::string filename;
        std::cout << "Enter filename for top expenses report: ";
        std::cin >> filename;
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateTopExpensesReport(filename);
    }
    else if (choice == "piechart") {
        std::string date, filename;
        std::cout << "Enter date (YYYY or YYYY-MM): ";
        std::cin >> date;
        std::cout << "Enter filename for pie chart data: ";
        std::cin >> filename;
        if (filename.find('.') == std::string::npos) {
            filename += ".txt";
        }
        manager.generateExpensePieChartData(date, filename);
    }
    else {
        std::cout << "Invalid choice.\n";
    }
}


// metoda sprawdzająca limit budzetu
void UserInterface::checkBudgets() const {
    manager.checkBudgetWarnings();
}

// wyswietlanie średnich miesięcznych wydatków
void UserInterface::displayMonthlyAverageExpenses() const {
    std::cout << "Enter month (YYYY-MM): ";
    std::string month;
    std::cin >> month;

    auto averages = manager.calculateMonthlyAverageExpenses(month);
    std::cout << "Average Monthly Expenses by Category for " << month << ":\n";
    for (const auto& [category, average] : averages) {
        std::cout << "Category: " << category << ", Average: " << average << "\n";
    }
}

UserInterface::UserInterface(FinanceManager& manager) : manager(manager) {}

// menu użytkownika
void UserInterface::start() {
    while (true) {
        std::cout << "1. Add transaction\n";
        std::cout << "2. Set budget\n";
        std::cout << "3. Display summary\n";
        std::cout << "4. Generate reports\n";
        std::cout << "5. Check budget warnings\n";
        std::cout << "6. Display monthly average expenses\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose an option: ";
        int choice;
        std::cin >> choice;

        try {
            // sprawdzanie czy wprowadzony typ danych jest niepoprawny lub czy kolejnym znakiem nie jest znak nowej linii
            if (std::cin.fail() || std::cin.peek() != '\n') {
                // Wyczyść stan błędu std::cin
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw TransactionException("Invalid input. Should be a number.");
            }

            switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                setBudget();
                break;
            case 3:
                displaySummary();
                break;
            case 4:
                generateReports();
                break;
            case 5:
                checkBudgets();
                break;
            case 6:
                displayMonthlyAverageExpenses();
                break;
            case 7:
                return;
            default:
                throw TransactionException("Invalid option. Please try again.");
            }
        }
        catch (const TransactionException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }

    }
}