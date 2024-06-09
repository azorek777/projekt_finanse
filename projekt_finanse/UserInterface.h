#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"

class UserInterface {
private:
    FinanceManager manager;

    void addTransaction();
    void setBudget();
    void displaySummary() const;
    void generateReports() const;
    void checkBudgets() const;
    void displayMonthlyAverageExpenses() const;

public:
    void start();
};

#endif // USERINTERFACE_H