#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

// Клас "Робот" з основними характеристиками
class Robot {
private:
    string name;
    int health;
    int energy;
    int attack;
    string strategy;

public:
    // Конструктор для ініціалізації характеристик робота
    Robot(string n, int h, int e, int a, string s) : name(n), health(h), energy(e), attack(a), strategy(s) {}

    // Метод для захисту від атаки
    void defend(int strategyCode) {
        // Реалізація логіки захисту на основі коду стратегії
        switch (strategyCode) {
        case 1:  // агресивна стратегія
            energy -= 5;
            attack += 5;
            strategy = "aggressive";
            cout << name << " вибирає агресивну стратегію захисту.\n";
            break;
        case 2:  // оборонна стратегія
            energy -= 3;
            attack += 2;
            strategy = "defensive";
            cout << name << " вибирає оборонну стратегію захисту.\n";
            break;
        case 3:  // збалансована стратегія
            strategy = "balanced";
            cout << name << " вибирає збалансовану стратегію захисту.\n";
            break;
        default:
            cout << "Невірний код стратегії. Вибрано збалансовану стратегію захисту.\n";
        }
    }

    // Метод для атаки враховуючи захист противника
    void attackEnemy(Robot* enemy) {
        int damage = attack+energy/10;
        damage = (damage > 0) ? damage : 0;
        enemy->receiveDamage(damage);
        cout << name << " атакує " << enemy->getName() << " і завдає " << damage << " урона.\n";
    }

    // Метод для отримання урону
    void receiveDamage(int damage) {
        health -= damage;
        health = (health > 0) ? health : 0;
        cout << name << " отримує " << damage << " урону. Поточне здоров'я: " << health << "\n";
    }

   

    // Методи для отримання значень характеристик робота
    string getName() const { return name; }
    int getAttack() const { return attack; }
    int getHealth() const { return health; }
    int getEnergy() const { return energy; }
    string getStrategy() const { return strategy; }
};

class Arena {
private:
    vector<Robot*> robots;

public:
    // Метод для додавання робота на арену
    void addRobot(Robot* robot) {
        robots.push_back(robot);
        cout << "До арени додано робота: " << robot->getName() << "\n";
    }

    // Метод для початку бою
    void startBattle() {
        cout << "Бій розпочався!\n";

        // Поки на арені є більше одного робота, обираємо опонента та ведемо бій
        while (robots.size() > 1) {
            Robot* attacker = chooseAttacker();
            Robot* defender = chooseDefender(attacker);

            if (attacker && defender) {
                // Робот атакує опонента
                attacker->attackEnemy(defender);

                // Перевірка, чи опонент ще живий
                if (defender->getHealth() <= 0) {
                    cout << attacker->getName() << " перемагає " << defender->getName() << "!\n";
                    removeDefeatedRobot(defender);
                }

                // Вивід статусу роботів на арені
                displayRobotStatus();
            }
        }

        // Визначення та виведення переможця
        Robot* winner = determineWinner();
        if (winner) {
            cout << "Бій завершено! " << winner->getName() << " - переможець!\n";
        }
        else {
            cout << "Бій завершено! Немає переможця.\n";
        }
    }

    // Метод для отримання кількості роботів в арені
    int getRobotCount() const {
        return robots.size();
    }

private:
    // Метод для обрання робота, який буде атакувати
    Robot* chooseAttacker() {
        if (robots.size() > 0) {
            return robots[rand() % robots.size()];
        }
        return nullptr;
    }

    // Метод для обрання опонента для атаки
    Robot* chooseDefender(Robot* attacker) {
        if (robots.size() > 1) {
            int defenderIndex = rand() % robots.size();
            while (robots[defenderIndex] == attacker) {
                defenderIndex = rand() % robots.size();
            }
            return robots[defenderIndex];
        }
        return nullptr;
    }

    // Метод для видалення впавшого робота з арени
    void removeDefeatedRobot(Robot* defeatedRobot) {
        auto it = find(robots.begin(), robots.end(), defeatedRobot);
        if (it != robots.end()) {
            robots.erase(it);
            cout << defeatedRobot->getName() << " видалено з арени.\n";
            // Видалення робота з арени, але пам'ять не вивільняється, треба додати видалення об'єкта.
            delete defeatedRobot;
        }
    }

    // Метод для визначення переможця
    Robot* determineWinner() {
        if (robots.size() == 1) {
            return robots[0];
        }
        return nullptr;
    }

    // Метод для виведення статусу всіх роботів на арені
    void displayRobotStatus() {
        cout << "Статус роботів на арені:\n";
        for (const auto& robot : robots) {
            cout << "Робот " << robot->getName()
                << " | Здоров'я: " << robot->getHealth()
                << " | Енергія: " << robot->getEnergy()
                << " | Атака: " << robot->getAttack()
                << " | Стратегія: " << robot->getStrategy() << "\n";
        }
        cout << "\n";
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Встановлення генератора випадкових чисел на основі часу
    srand(time(0));
    cout << "Вітаємо вас у грі Aggressive Killer 2000. Правила гри:" << endl <<
        "1. Ви вибираєте кількість роботів на арені (кількість роботів може бути необмеженою). " << endl <<
        "2. Ви вказуєте ім'я вашого робота та ваших апонентів (можна використовувати як і кирилицю, так і латиницю).  " << endl <<
        "3. Ви вказуєте характеристики роботів, такі, як здоров'я, енергія, атака, захист (обмеження характеристик 500 одиниць).  " << endl <<
        "4. Починається бій, все відбувається автоматично, переможця буде виведено в кінці.  " << endl << endl;
    // Створення арени для бою
    Arena battleArena;

    // Кількість роботів, яку користувач вводить
    int robotCount;
    cout << "Введіть кількість роботів: ";
    cin >> robotCount;

    // Введення характеристик кожного робота та додавання їх на арену
    for (int i = 0; i < robotCount; ++i) {
        string name;
        int health, energy, attack;
        string strategy;

        cout << "Введіть ім'я робота " << i + 1 << ": ";
        cin >> name;

        cout << "Введіть здоров'я робота " << i + 1 << ": ";
        cin >> health;
        while (health > 500 || health < 0) {
            cout << "Ви ввели більше/меньше ніж 500/0 одиниць здоров'я, хоча у правилах було СКАЗАНО, що обмеження 500/0 \n";
            cout << "Введіть здоров'я робота " << i + 1 << ": ";
            cin >> health;
        }

        cout << "Введіть енергію робота " << i + 1 << ": ";
        cin >> energy;
        while (energy > 500 || energy < 0) {
            cout << "Ви ввели більше/меньше ніж 500/0 одиниць енергії, хоча у правилах було СКАЗАНО, що обмеження 500/0 \n";
            cout << "Введіть енергію робота" << i + 1 << ": ";
            cin >> energy;
        }

        cout << "Введіть атаку робота " << i + 1 << ": ";
        cin >> attack;
        while (attack > 500 || attack < 0) {
            cout << "Ви ввели більше/меньше ніж 500/0 одиниць актаки, хоча у правилах було СКАЗАНО, що обмеження 500/0 \n";
            cout << "Введіть атаку робота" << i + 1 << ": ";
            cin >> attack;
        }

        cout << "Введіть стратегію захисту робота(aggressive,defensive,balanced) " << i + 1 << ": ";
        cin >> strategy;
        while (strategy != "aggressive" && strategy != "defensive" && strategy != "balanced") {
            cout << "Ви ввели більше/меньше ніж 3/0 одиниць стратегії, хоча у правилах було СКАЗАНО, що обмеження 3/0  \n";
            cout << "Введіть стратегію захисту робота(aggressive,defensive,balanced) " << i + 1 << ": ";
            cin >> strategy;
        }

        // Створення робота та додавання його на арену
        Robot* newRobot = new Robot(name, health, energy, attack, strategy);
        battleArena.addRobot(newRobot);
    }

    // Початок бою
    battleArena.startBattle();
}