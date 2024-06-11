#include "FinanceManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>

// wyslanie do pamieci transakcji
void FinanceManager::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

// ustawienie bud�etu
void FinanceManager::setMonthlyBudget(const std::string& category, double amount) {
    monthlyBudget[category] = amount;
}

// zwr�cenie ca�kowitego dochodu
double FinanceManager::getTotalIncome() const {
	double total = 0.0; //inicjalizacja ca�kowitego dochodu
    for (const auto& t : transactions) {
		if (t.getType() == TransactionType::Income) { // sprawdzenie czy transakcja jest dochodem
			total += t.getAmount(); // dodanie kwoty do ca�kowitego dochodu
        }
    }
    return total;
}

// zwr�cenie ca�kowitych wydatk�w
double FinanceManager::getTotalExpenses() const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            total += t.getAmount();
        }
    }
    return total;
}

// zwr�cenie ca�kowitych wydatk�w w danej kategorii
double FinanceManager::getCategoryTotal(const std::string& category) const {
    double total = 0.0;
    for (const auto& t : transactions) {
        if (t.getCategory() == category) {
			total += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount()); // je�eli transakcja jest dochodem to dodajemy kwot�, je�eli wydatkiem to odejmujemy
        }
    }
    return total;
}

// zwr�cenie podsumowania miesi�cznego
std::map<std::string, double> FinanceManager::getMonthlySummary(const std::string& month) const {
	std::map<std::string, double> summary; // summary jest mapa z kluczem string i warto�ci� double
    for (const auto& t : transactions) {
		if (t.getDate().substr(0, 7) == month) { // sprawdzamy czy data transakcji jest r�wna podanemu miesi�cowi
            summary[t.getCategory()] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount());
        }
    }
    return summary;
}

// zwr�cenie podsumowania rocznego
std::map<std::string, double> FinanceManager::getYearlySummary(const std::string& year) const {
    std::map<std::string, double> summary;
    for (const auto& t : transactions) {
        if (t.getDate().substr(0, 4) == year) {
			summary[t.getCategory()] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount()); // je�eli transakcja jest dochodem to dodajemy kwot�, je�eli wydatkiem to odejmujemy
        }
    }
    return summary;
}

// zwr�cenie �rednich miesi�cznych wydatk�w
double FinanceManager::getAverageMonthlyExpense(const std::string& category) const {
    std::map<std::string, double> monthlyTotals;
    for (const auto& t : transactions) {
        if (t.getCategory() == category) {
            std::string month = t.getDate().substr(0, 7);
			monthlyTotals[month] += (t.getType() == TransactionType::Income ? t.getAmount() : -t.getAmount()); // je�eli transakcja jest dochodem to dodajemy kwot�, je�eli wydatkiem to odejmujemy
        }
    }
    double total = 0.0;
	for (const auto& [month, amount] : monthlyTotals) { // przej�cie przez ka�dy element kontenera monthlyTotals (dodawanie dochodow z miesiecy)
        total += amount;
    }
	return total / monthlyTotals.size(); // zwr�cenie �redniej
}

// generowanie raportu miesi�cznego
void FinanceManager::generateMonthlyReport(const std::string& month, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Monthly Report for " << month << "\n";
        file << "----------------------------------\n";
		// dla ka�dej transakcji w miesiacu dodajemy do pliku date, kategorie, kwot� i opis
        for (const auto& t : transactions) {
            if (t.getDate().substr(0, 7) == month) {
                file << t.getDate() << " | " << t.getCategory() << " | " << t.getAmount() << " | " << t.getDescription() << "\n";
            }
        }
        file.close();
    }
    // przypadek gdy system nie pozwala nam otworzyc pliku
    else {
        std::cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

// generowanie raportu rocznego
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

// generowanie raportu kategorii
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

// generowanie raportu por�wnawczego
// przyjecie dwoch okresow i nazwy pliku
void FinanceManager::generateComparisonReport(const std::string& period1, const std::string& period2, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Comparison Report for " << period1 << " and " << period2 << "\n";
        file << "----------------------------------\n";

		// pobieranie raport�w miesi�cznych dla podanych okres�w
        std::map<std::string, double> summary1 = getMonthlySummary(period1);
        std::map<std::string, double> summary2 = getMonthlySummary(period2);

		// �aczenie raport�w w jeden plik
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

// generowanie raportu najwi�kszych wydatk�w
void FinanceManager::generateTopExpensesReport(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Top Expenses Report\n";
        file << "----------------------------------\n";

		// kopia wektora transakcji
        std::vector<Transaction> sortedExpenses = transactions;
		// sortowanie transakcji od najwi�kszej do najmniejszej kwoty
		// begin i end oznaczaja zakres sortowania, dalej sprawdany jest warunek czy kwota transakcji a jest wieksza od kwoty transakcji b i jesli tak to zamieniane sa miejscami
        std::sort(sortedExpenses.begin(), sortedExpenses.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() > b.getAmount();
            });

		// wyswietlenie najwiekszych wydatkow
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

// sprawdzenie czy bud�et nie zosta� przekroczony
void FinanceManager::checkBudgetWarnings() const {
    for (const auto& [category, budget] : monthlyBudget) {
		// porownanie kwoty kategorii z budzetem
        double total = getCategoryTotal(category);
        if (total > budget) {
            std::cout << "Warning: Budget exceeded for category: " << category << "\n";
        }
    }
}

// generowanie danych do wykresu ko�owego
void FinanceManager::generateExpensePieChartData(const std::string& date, const std::string& filename) const {
    std::map<std::string, double> expenseSummary;
    double totalExpenses = 0.0;
	bool isYear = (date.length() == 4); // sprawdzenie czy podana data jest rokiem

	// sumowanie wydatk�w w danej kategorii w wybranej dacie
    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::Expense) {
            std::string transactionDate = t.getDate().substr(0, date.length());
            if (transactionDate == date) {
                expenseSummary[t.getCategory()] += t.getAmount();
                totalExpenses += t.getAmount();
            }
        }
    }

	// przygotowanie URL do wykresu ko�owego
    // przykladowy url https://image-charts.com/chart?cht=p3&chs=700x300&chd=t:45,25,17,15&chl=A|B|C|D&chco=FF0000|00FF00|0000FF|FFFF00
	// cht=p3 - typ wykresu ko�owego
	// chs=700x300 - rozmiar wykresu
	// chd=t:45,25,17,15 - dane do wykresu
	// chl=A|B|C|D - etykiety
	// chco=FF0000|00FF00|0000FF|FFFF00 - kolory
    std::ostringstream url;
    url << "https://image-charts.com/chart?cht=p3&chs=700x300";

	// dodanie kategorii z warto�ciami i procentami do URL
	// potrzebujemy wyliczyc warto�� ka�dej kategorii i procent ca�o�ci aby ca�y wykres mia� 360 stopni
    url << "&chl=";
	bool first = true; // pierwszy element nie ma oddzielacza
    for (const auto& [category, amount] : expenseSummary) {
		// je�eli nie jest to pierwszy element to dodajemy oddzielacz
        if (!first) {
            url << "|";
        }
        double percentage = (amount / totalExpenses) * 100.0;
		url << category << "%28" << std::fixed << std::setprecision(2) << amount << "%29"; // %28 to "("; %29 to ")" - u�ywa sie to aby unikn�� problem�w z przekazywaniem znak�w specjalnych dla przegladarki
        first = false;
    }

    // dodajemy procenty do url by wykres mia� dobre proporcje
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

	// wy�wietlenie ca�ego URL
    std::cout << "Pie Chart URL: " << url.str() << std::endl;

	// zapisywanie tych samych danych do pliku
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

// obliczenie �rednich miesi�cznych wydatk�w
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



