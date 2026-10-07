#include <iostream>
#include <cstring>   // для работы со строками (если понадобится)

using namespace std;


struct Meter {
    int consumerNumber;     
    int previousReading;     
    int currentReading;   
    double tariff;         
    double debt;            
};


const int CONSUMERS_COUNT = 8; 


void inputConsumer(Meter& consumer) {
    cout << "введите данные потребителя:" << endl;
    cout << "номер потребителя: ";
    cin >> consumer.consumerNumber;
    cout << "предыдущие показания (кВт*ч): ";
    cin >> consumer.previousReading;
    cout << "текущие показания (кВт*ч): ";
    cin >> consumer.currentReading;
    cout << "тариф (руб./кВт*ч): ";
    cin >> consumer.tariff;
    cout << "текущая задолженность (руб.): ";
    cin >> consumer.debt;
}


void displayConsumer(const Meter& consumer) {
    cout << "потребитель №" << consumer.consumerNumber << ":" << endl;
    cout << "  предыдущие показания: " << consumer.previousReading << " кВт*ч" << endl;
    cout << "  текущие показания: " << consumer.currentReading << " кВт*ч" << endl;
    cout << "  тариф: " << consumer.tariff << " руб./кВт*ч" << endl;
    cout << "  задолженность: " << consumer.debt << " руб." << endl;
}

// --- Вывод всех потребителей ---
void displayAllConsumers(const Meter consumers[]) {
  
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        cout << endl <<" потребитель " << (i + 1) << endl;
        displayConsumer(consumers[i]);
    }

}

void calculateConsumption(const Meter consumers[]) {
  
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        int consumption = consumers[i].currentReading - consumers[i].previousReading;
        cout << "потребитель №" << consumers[i].consumerNumber  << ": " << consumption << " кВт*ч" << endl;
    }
 
}


void calculateCharges(const Meter consumers[]) {
   
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        int consumption = consumers[i].currentReading - consumers[i].previousReading;
        double charge = consumption * consumers[i].tariff;
        cout << "потребитель №" << consumers[i].consumerNumber << ": " << charge << " руб." << endl;
    }
 
}


void calculateTotalDebt(Meter consumers[]) {
 
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        int consumption = consumers[i].currentReading - consumers[i].previousReading;
        double charge = consumption * consumers[i].tariff;
        consumers[i].debt += charge;  

        cout << "потребитель №" << consumers[i].consumerNumber << ": " << consumers[i].debt << " руб." << endl;
    }
 
    cout << "задолженность обновлена для всех потребителей" << endl;
}


void findMaxConsumer(const Meter consumers[]) {
    if (CONSUMERS_COUNT == 0) {
        cout << "список потребителей пуст" << endl;
        return;
    }

    int maxConsumption = consumers[0].currentReading - consumers[0].previousReading;
    int maxIndex = 0;

    for (int i = 1; i < CONSUMERS_COUNT; i++) {
        int consumption = consumers[i].currentReading - consumers[i].previousReading;
        if (consumption > maxConsumption) {
            maxConsumption = consumption;
            maxIndex = i;
        }
    }


    cout << "потребитель с максимальным потреблением:" << endl;
    displayConsumer(consumers[maxIndex]);
    cout << "потребление: " << maxConsumption << " кВт*ч" << endl;
 
}


void calculateTotalDebtAll(const Meter consumers[]) {
    double totalDebt = 0;

    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        totalDebt += consumers[i].debt;
    }


    cout << "общая задолженность всех потребителей: " << totalDebt << " руб." << endl;

}


void makePayment(Meter consumers[]) {
    int consumerNumber;
    cout << endl << "введите номер потребителя для оплаты: ";
    cin >> consumerNumber;

    
    int foundIndex = -1;
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        if (consumers[i].consumerNumber == consumerNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "потребитель с таким номером не найден!" << endl;
        return;
    }


    cout << "текущая задолженность потребителя №" << consumerNumber
        << ": " << consumers[foundIndex].debt << " руб." << endl;

    double payment;
    cout << "введите сумму оплаты (руб.): ";
    cin >> payment;

    if (payment <= 0) {
        cout << "сумма оплаты должна быть положительной!" << endl;
        return;
    }

  
    consumers[foundIndex].debt -= payment;

    if (consumers[foundIndex].debt < 0) {
        consumers[foundIndex].debt = 0;  
    }

    cout << endl <<"оплата произведена!" << endl;
    cout << "новая задолженность: " << consumers[foundIndex].debt << " руб." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

 
    Meter consumers[CONSUMERS_COUNT];

   
    for (int i = 0; i < CONSUMERS_COUNT; i++) {
        cout << endl << " потребитель " << (i + 1) << " из " << CONSUMERS_COUNT << endl;
        inputConsumer(consumers[i]);
    }

    cout <<endl<< "ланные введены успешно!" << endl;

    
    int choice;
    do {
 
        cout << " 1. показать всех потребителей" << endl;
        cout << " 2. рассчитать потребление электроэнергии" << endl;
        cout << " 3. рассчитать начисления за период" << endl;
        cout << " 4. определить итоговую задолженность" << endl;
        cout << " 5. найти потребителя с макс потреблением" << endl;
        cout << " 6. рассчитать общую задолженность" << endl;
        cout << " 7. выполнить оплату" << endl;
        cout << " 0. выход" << endl;
        cout << "выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllConsumers(consumers);
            break;
        case 2:
            calculateConsumption(consumers);
            break;
        case 3:
            calculateCharges(consumers);
            break;
        case 4:
            calculateTotalDebt(consumers);
            break;
        case 5:
            findMaxConsumer(consumers);
            break;
        case 6:
            calculateTotalDebtAll(consumers);
            break;
        case 7:
            makePayment(consumers);
            break;
        case 0:
            cout << "выход из программы" << endl;
            break;
        default:
            cout << "неверный выбор, попробуйте ещё раз" << endl;
        }
    } while (choice != 0);

    return 0;
}