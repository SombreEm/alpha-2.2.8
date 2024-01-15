#include <iostream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class Robot {
private:
    string name;
    int health;
    int energy;
    int attack;
    int defense;
    string strategy;

public:
    Robot(string n, int h, int e, int a, int d, string s) : name(n), health(h), energy(e), attack(a), defense(d), strategy(s) {}

    void defend(int strategyCode) {
        switch (strategyCode) {
        case 1:  
            energy -= 5;
            attack += 5;
            defense -= 5; 
            strategy = "aggressive";
            cout << name << " вибирає агресивну стратегію захисту.\n";
            break;
        case 2: 
            energy -= 3;
            attack += 2;
            defense += 5;  
            strategy = "defensive";
            cout << name << " вибирає оборонну стратегію захисту.\n";
            break;
        case 3: 
            strategy = "balanced";
            defense += 3; 
            cout << name << " вибирає збалансовану стратегію захисту.\n";
            break;
        default:
            cout << "Невірний код стратегії. Вибрано збалансовану стратегію захисту.\n";
        }
    }

    void attackEnemy(Robot* enemy) {
        int damage = (attack + energy / 10) - enemy->getDefense(); 
        damage = (damage > 0) ? damage : 0;
        cout << name << " атакує " << enemy->getName() << " і завдає " << damage << " урона.\n";
        enemy->receiveDamage(damage);
    }

    void receiveDamage(int damage) {
        health -= damage;
        health = (health > 0) ? health : 0;
        cout << name << " отримує " << damage << " урону. Поточне здоров'я: " << health << "\n";
    }

    string getName() const { return name; }
    int getAttack() const { return attack; }
    int getHealth() const { return health; }
    int getEnergy() const { return energy; }
    int getDefense() const { return defense; }
    string getStrategy() const { return strategy; }
};

class Arena {
private:
    vector<Robot*> robots;

public:
    void addRobot(Robot* robot) {
        robots.push_back(robot);
        cout << "До арени додано робота: " << robot->getName() << "\n";
    }

    void startBattle() {
        cout << "Бій розпочався!\n";
        while (robots.size() > 1) {
            Robot* attacker = chooseAttacker();
            Robot* defender = chooseDefender(attacker);
            if (attacker && defender) {
                attacker->attackEnemy(defender);
                if (defender->getHealth() <= 0) {
                    cout << attacker->getName() << " перемагає " << defender->getName() << "!\n";
                    removeDefeatedRobot(defender);
                }
                displayRobotStatus();
            }
        }

        Robot* winner = determineWinner();
        if (winner) {
            cout << "Бій завершено! " << winner->getName() << " - переможець!\n";
        }
        else {
            cout << "Бій завершено! Немає переможця.\n";
        }
    }

    int getRobotCount() const {
        return robots.size();
    }

private:
    Robot* chooseAttacker() {
        if (robots.size() > 0) {
            return robots[rand() % robots.size()];
        }
        return nullptr;
    }

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

    void removeDefeatedRobot(Robot* defeatedRobot) {
        auto it = find(robots.begin(), robots.end(), defeatedRobot);
        if (it != robots.end()) {
            robots.erase(it);
            cout << defeatedRobot->getName() << " видалено з арени.\n";
            delete defeatedRobot;
        }
    }

    Robot* determineWinner() {
        if (robots.size() == 1) {
            return robots[0];
        }
        return nullptr;
    }

    void displayRobotStatus() {
        cout << "Статус роботів на арені:\n";
        for (const auto& robot : robots) {
            cout << "Робот " << robot->getName()
                << " | Здоров'я: " << robot->getHealth()
                << " | Енергія: " << robot->getEnergy()
                << " | Атака: " << robot->getAttack()
                << " | Захист: " << robot->getDefense()
                << " | Стратегія: " << robot->getStrategy() << "\n";
        }
        cout << "\n";
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));
    cout << "Вітаємо вас у грі Aggressive Killer 2000. Правила гри:" << endl <<
        "1. Ви вибираєте кількість роботів на арені (кількість роботів може бути необмеженою). " << endl <<
        "2. Ви вказуєте ім'я вашого робота та ваших апонентів (можна використовувати як і кирилицю, так і латиницю).  " << endl <<
        "3. Ви вказуєте характеристики роботів, такі, як здоров'я, енергія, атака, захист (обмеження характеристик 500 одиниць).  " << endl <<
        "4. Починається бій, все відбувається автоматично, переможця буде виведено в кінці.  " << endl << endl;

    Arena battleArena;

    int robotCount;
    cout << "Введіть кількість роботів: ";
    cin >> robotCount;

    for (int i = 0; i < robotCount; ++i) {
        string name;
        int health, energy, attack, defense;
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

        cout << "Введіть захист робота " << i + 1 << ": ";
        cin >> defense;
        while (defense > 500 || defense < 0) {
            cout << "Ви ввели більше/меньше ніж 500/0 одиниць захисту, хоча у правилах було СКАЗАНО, що обмеження 500/0 \n";
            cout << "Введіть захист робота" << i + 1 << ": ";
            cin >> defense;
        }

        cout << "Введіть стратегію захисту робота(aggressive,defensive,balanced) " << i + 1 << ": ";
        cin >> strategy;
        while (strategy != "aggressive" && strategy != "defensive" && strategy != "balanced") {
            cout << "Ви ввели більше/меньше ніж 3/0 одиниць стратегії, хоча у правилах було СКАЗАНО, що обмеження 3/0  \n";
            cout << "Введіть стратегію захисту робота(aggressive,defensive,balanced) " << i + 1 << ": ";
            cin >> strategy;
        }

        Robot* newRobot = new Robot(name, health, energy, attack, defense, strategy);
        battleArena.addRobot(newRobot);
    }

    battleArena.startBattle();
}