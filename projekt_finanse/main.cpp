// main.cpp
#include "Transaction.h"
#include <stdexcept>
#include <iostream>
#include <clocale>
#include <cstdlib>

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    while (1) {
        // MENU
        std::system("cls");
        std::cout<<"System zarzadzania finansami"<<std::endl;
        std::cout<<"-----------------------------"<<std::endl;
        std::cout<<"Wybierz opcje:"<<std::endl;
        std::cout<<"1. Zarządzanie przychodami i wydatkami"<<std::endl;
        std::cout<<"2. Analiza finansowa"<<std::endl;
        std::cout<<"3. Planowanie budżetu"<<std::endl;
        std::cout<<"4. Generowanie raportów"<<std::endl;
        std::cout<<"5. Wyjście"<<std::endl;
        int choice;
        std::cin>>choice;

        // Zarzadzanie przychodami i wydatkami
        if (choice == 1) {
            while (1) {
                std::system("cls");
                std::cout << "Zarządzanie przychodami i wydatkami" << std::endl;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Wybierz opcje:" << std::endl;
                std::cout << "1. Dodaj transakcje" << std::endl;
                std::cout << "2. Wyświetl transakcje" << std::endl;
                std::cout << "3. Menu główne" << std::endl;
                int choice2;
                std::cin >> choice2;
                if (choice2 == 1) {
                    // Dodawanie transakcji
                }
                else if (choice2 == 2) {
                    // Wyswietlanie transakcji
                }
                else if (choice2 == 3) {
                    break;
                }
                else {
                    std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
                }
            }
        }
        // Analiza finansowa
        if (choice == 2) {
            while (1) {
                std::system("cls");
                std::cout << "Analiza finansowa" << std::endl;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Wybierz opcje:" << std::endl;
                std::cout << "1. Wyświetl podsumowanie miesięczne" << std::endl;
                std::cout << "2. Wyświetl podsumowanie roczne" << std::endl;
                std::cout << "3. Generuj wykresy" << std::endl;
                std::cout << "4. Wyświetl średnie wydatki" << std::endl;
                std::cout << "5. Menu główne" << std::endl;
                int choice2;
                std::cin >> choice2;
                if (choice2 == 1) {
                    // Podsumowanie miesięczne
                }
                if (choice2 == 2) {
                    // Podsumowanie roczne
                }
                if (choice2 == 3) {
                    while (1) {
                        // Generowanie wykresów
                        std::system("cls");
                        std::cout << "1. Wykres miesięczny" << std::endl;
                        std::cout << "2. Wykres roczny" << std::endl;
                        std::cout << "3. Wróć" << std::endl;
                        int choice3;
                        std::cin >> choice3;
                        if (choice3 == 1) {
                            // Wykres miesieczny
                        }
                        if (choice3 == 2) {
                            // Wykres roczny
                        }
                        if (choice3 == 3) {
                            break;
                        }
                        else {
                            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
                        }
                    }
                }
                if (choice2 == 4) {
                    // Srednie wydatki
                }
                if (choice2 == 5) {
                    break;
                }
                else {
                    std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
                }
            }
        }
        // Planowanie budzetu
        if (choice == 3) {
            while (1) {
                std::system("cls");
                std::cout << "Planowanie budżetu" << std::endl;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Wybierz opcje:" << std::endl;
                std::cout << "1. Ustal budżet dla konkretnej kategorii" << std::endl;
                std::cout << "2. Monitorowanie postępów w celach budżetowych" << std::endl;
                std::cout << "3. Menu główne" << std::endl;
                int choice2;
                std::cin >> choice2;
                if (choice2 == 1) {
                    // Ustalanie budzetu
                }
                if (choice2 == 2) {
                    // Monitorowanie post�p�w
                }
                if (choice2 == 3) {
                    break;
                }
                else {
                    std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
                }
            }
        }
        if (choice == 4) {
            while (1) {
                std::system("cls");
                std::cout << "Generowanie raportow" << std::endl;
                std::cout << "------------------------------------" << std::endl;
                std::cout << "Wybierz opcje:" << std::endl;
                std::cout << "1. Generuj raport miesięczny" << std::endl;
                std::cout << "2. Generuj raport roczny" << std::endl;
                std::cout << "3. Generuj raport porównawczy" << std::endl;
                std::cout << "4. Generuj raport z największymi wydatkami w danej kategorii" << std::endl;
                std::cout << "5. Menu główne" << std::endl;
                int choice2;
                std::cin >> choice2;
                if (choice2 == 1) {
                    // Generowanie raportu miesiecznego
                }
                if (choice2 == 2) {
                    // Generowanie raportu rocznego
                }
                if (choice2 == 3) {
                    // Generowanie raportu por�wnawczego
                }
                if (choice2 == 4) {
                    // Generowanie raportu z najwiekszymi wydatkami w danej kategorii
                }
                if (choice2 == 5) {
                    break;
                }
                else {
                    std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
                }
            }
        }
        // Wyjscie
        if (choice == 5) {
			break;
		}
        else {
			std::cout<<"Nieprawidlowy wybor. Sprobuj ponownie."<<std::endl;
            continue;
		}

 

    }
    TransactionManager manager;
    try {
        manager.addTransaction("Income", "Salary", "2022-01-01", "January Salary", 5000);
        manager.addTransaction("Expense", "Rent", "2022-01-02", "January Rent", -2000);
        manager.printTransactions();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}