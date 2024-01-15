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
            cout << name << " ������ ��������� �������� �������.\n";
            break;
        case 2: 
            energy -= 3;
            attack += 2;
            defense += 5;  
            strategy = "defensive";
            cout << name << " ������ �������� �������� �������.\n";
            break;
        case 3: 
            strategy = "balanced";
            defense += 3; 
            cout << name << " ������ ������������ �������� �������.\n";
            break;
        default:
            cout << "������� ��� ������㳿. ������� ������������ �������� �������.\n";
        }
    }

    void attackEnemy(Robot* enemy) {
        int damage = (attack + energy / 10) - enemy->getDefense(); 
        damage = (damage > 0) ? damage : 0;
        cout << name << " ����� " << enemy->getName() << " � ����� " << damage << " �����.\n";
        enemy->receiveDamage(damage);
    }

    void receiveDamage(int damage) {
        health -= damage;
        health = (health > 0) ? health : 0;
        cout << name << " ������ " << damage << " �����. ������� ������'�: " << health << "\n";
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
        cout << "�� ����� ������ ������: " << robot->getName() << "\n";
    }

    void startBattle() {
        cout << "��� ����������!\n";
        while (robots.size() > 1) {
            Robot* attacker = chooseAttacker();
            Robot* defender = chooseDefender(attacker);
            if (attacker && defender) {
                attacker->attackEnemy(defender);
                if (defender->getHealth() <= 0) {
                    cout << attacker->getName() << " �������� " << defender->getName() << "!\n";
                    removeDefeatedRobot(defender);
                }
                displayRobotStatus();
            }
        }

        Robot* winner = determineWinner();
        if (winner) {
            cout << "��� ���������! " << winner->getName() << " - ����������!\n";
        }
        else {
            cout << "��� ���������! ���� ���������.\n";
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
            cout << defeatedRobot->getName() << " �������� � �����.\n";
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
        cout << "������ ������ �� ����:\n";
        for (const auto& robot : robots) {
            cout << "����� " << robot->getName()
                << " | ������'�: " << robot->getHealth()
                << " | ������: " << robot->getEnergy()
                << " | �����: " << robot->getAttack()
                << " | ������: " << robot->getDefense()
                << " | ��������: " << robot->getStrategy() << "\n";
        }
        cout << "\n";
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));
    cout << "³���� ��� � �� Aggressive Killer 2000. ������� ���:" << endl <<
        "1. �� �������� ������� ������ �� ���� (������� ������ ���� ���� �����������). " << endl <<
        "2. �� ������� ��'� ������ ������ �� ����� �������� (����� ��������������� �� � ��������, ��� � ��������).  " << endl <<
        "3. �� ������� �������������� ������, ���, �� ������'�, ������, �����, ������ (��������� ������������� 500 �������).  " << endl <<
        "4. ���������� ��, ��� ���������� �����������, ��������� ���� �������� � ����.  " << endl << endl;

    Arena battleArena;

    int robotCount;
    cout << "������ ������� ������: ";
    cin >> robotCount;

    for (int i = 0; i < robotCount; ++i) {
        string name;
        int health, energy, attack, defense;
        string strategy;

        cout << "������ ��'� ������ " << i + 1 << ": ";
        cin >> name;

        cout << "������ ������'� ������ " << i + 1 << ": ";
        cin >> health;
        while (health > 500 || health < 0) {
            cout << "�� ����� �����/������ �� 500/0 ������� ������'�, ���� � �������� ���� �������, �� ��������� 500/0 \n";
            cout << "������ ������'� ������ " << i + 1 << ": ";
            cin >> health;
        }

        cout << "������ ������ ������ " << i + 1 << ": ";
        cin >> energy;
        while (energy > 500 || energy < 0) {
            cout << "�� ����� �����/������ �� 500/0 ������� ����㳿, ���� � �������� ���� �������, �� ��������� 500/0 \n";
            cout << "������ ������ ������" << i + 1 << ": ";
            cin >> energy;
        }

        cout << "������ ����� ������ " << i + 1 << ": ";
        cin >> attack;
        while (attack > 500 || attack < 0) {
            cout << "�� ����� �����/������ �� 500/0 ������� ������, ���� � �������� ���� �������, �� ��������� 500/0 \n";
            cout << "������ ����� ������" << i + 1 << ": ";
            cin >> attack;
        }

        cout << "������ ������ ������ " << i + 1 << ": ";
        cin >> defense;
        while (defense > 500 || defense < 0) {
            cout << "�� ����� �����/������ �� 500/0 ������� �������, ���� � �������� ���� �������, �� ��������� 500/0 \n";
            cout << "������ ������ ������" << i + 1 << ": ";
            cin >> defense;
        }

        cout << "������ �������� ������� ������(aggressive,defensive,balanced) " << i + 1 << ": ";
        cin >> strategy;
        while (strategy != "aggressive" && strategy != "defensive" && strategy != "balanced") {
            cout << "�� ����� �����/������ �� 3/0 ������� ������㳿, ���� � �������� ���� �������, �� ��������� 3/0  \n";
            cout << "������ �������� ������� ������(aggressive,defensive,balanced) " << i + 1 << ": ";
            cin >> strategy;
        }

        Robot* newRobot = new Robot(name, health, energy, attack, defense, strategy);
        battleArena.addRobot(newRobot);
    }

    battleArena.startBattle();
}