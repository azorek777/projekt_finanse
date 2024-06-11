#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"

class UserInterface {
private:
    FinanceManager manager;

	// wewnetrzne metody interfejsu
    void addTransaction();
    void setBudget();
    void displaySummary() const;
    void generateReports() const;
    void checkBudgets() const;
    void displayMonthlyAverageExpenses() const;

public:
	// zewnêtrzne metody interfejsu
    UserInterface(FinanceManager& manager);
    void start();
};

#endif // USERINTERFACE_H
