#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Terrain;
class Road;
class Grass;
class Hill;
class Placedtowers;
class Trap;
class Tower;
class Enemy;
class Boss;
class Level;
class Game;
class Levelgenerator;
class Wave;
class Player;
class ammunition_depot;

class Level {
public:
    int score = 0; // score for level
    int kills = 0; // kill for level
    friend class Playgame;
    friend class Tower;
    friend class Wave;
    friend class Map;
    friend class Enemy;
    friend class Boss;
    friend class Levelgenerator;

    Terrain** terrainMap;
    int rows;
    int columns;
    int enemyDamage;
    int enemyHealth;
    int enemyAttack;
    int enemyRange;
    int startCash;
    int startScore;
    int startKills;
    int loopCount;
    bool isBossDead;
    Enemy* getEnemy(int x, int y) {
        Terrain* t = getTerrain(x, y);
        if (t != nullptr && t->getEnemy() != nullptr) {
            return t->getEnemy();
        }
        return nullptr;
    }

    Level() : terrainMap(nullptr), rows(0), columns(0), enemyDamage(0), enemyHealth(0), enemyAttack(0), enemyRange(0), startCash(0), startScore(0), startKills(0), loopCount(0), isBossDead(false) {}

    void translatewave(const char* wavedata) {
        // Implement wave translation logic here
    }

    void setwave(const char* wavedata) {
        translatewave(wavedata);
        setenemynum(5);
        setenemyhealth(5);
        setenemyattack(1);
        setenemyrange(2);
        setstartcash(50);
        setstartscore(0);
        setstartkills(0);
    }

    void setenemynum(int num) {
        // Implement enemy number setting logic here
    }

    void setenemyhealth(int health) {
        enemyHealth = health;
    }

    void setenemyattack(int attack) {
        enemyAttack = attack;
    }

    void setenemyrange(int range) {
        enemyRange = range;
    }

    void setstartcash(int cash) {
        startCash = cash;
    }

    void setstartscore(int score) {
        startScore = score;
    }

    void setstartkills(int kills) {
        startKills = kills;
    }

    void setloopcount(int count) {
        loopCount = count;
    }

    int getstartcash() {
        return startCash;
    }

    int getstartscore() {
        return startScore;
    }

    int getstartkills() {
        return startKills;
    }

    int getenemynum() {
        // Implement enemy number retrieval logic here
    }

    int getenemyhealth() {
        return enemyHealth;
    }

    int getenemyattack() {
        return enemyAttack;
    }

    int getenemyrange() {
        return enemyRange;
    }

    int getloopcount() {
        return loopCount;
    }

    bool getisbossdead() {
        return isBossDead;
    }

    void setisbossdead(bool dead) {
        isBossDead = dead;
    }

    Terrain** getTerrainMap() {
        return terrainMap;
    }

    int getRows() {
        return rows;
    }

    int getColumns() {
        return columns;
    }
};

class Terrain {
public:
    virtual void display() const = 0;
    Terrain* getTerrain(int x, int y) {
        return terrainMap[x][y];
    }
};

class Road : public Terrain {
public:
    virtual void display() const override {
        cout << "R";
    }
};

class Grass : public Terrain {
public:
    virtual void display() const override {
        cout << "G";
    }
};class Hill : public Terrain {
public:
    virtual void display() const override {
        cout << "H";
    }
};

class Placedtowers {
public:
    virtual void attack(Level* l, int currentLoop) = 0;
};

class Tower : public Placedtowers {
public:
    int x, y;
    int range;
    int damage;
    int cost;
    int firerate;

    Tower(int x, int y, int range, int damage, int cost, int firerate) : x(x), y(y), range(range), damage(damage), cost(cost), firerate(firerate) {}

    virtual void attack(Level* l, int currentLoop) = 0;
};

class GunTower : public Tower {
public:
    GunTower(int x, int y) : Tower(x, y, 3, 10, 50, 500) {}

    void attack(Level* l, int currentLoop) override {
        if (currentLoop % firerate == 0) {
            for (int i = -range; i <= range; i++) {
                for (int j = -range; j <= range; j++) {
                    if (i * i + j * j <= range * range) {
                        int tx = x + i, ty = y + j;
                        if (tx >= 0 && tx < l->getRows() && ty >= 0 && ty < l->getColumns()) {
                            Terrain* t = l->getTerrainMap()[tx][ty];
                            if (t->getEnemy() != nullptr) {
                                t->getEnemy()->loseHealth(damage, *l);
                            }
                        }
                    }
                }
            }
        }
    }
};

class Levelgenerator {
public:
    void generatelvl1(Level& i) {
        char* wavedata = "llll";
        i.translatewave(wavedata);
    }

    void generatelvl2(Level& i) {
        char* wavedata = "wlwlwlwlw";
        i.setwave(wavedata);
        i.setenemynum(5);
        i.setenemyhealth(5);
        i.setenemyattack(1);
        i.setenemyrange(2);
        i.setstartcash(50);
        i.setstartscore(0);
        i.setstartkills(0);
    }

    void generatelvl3(Level& i) {
        char* wavedata = "wllllw";
        i.setstartcash(100);
        i.setstartscore(0);
        i.setstartkills(0);
    }
};

class Wave {
public:
    vector<Enemy*> enemies;

    Wave() {}

    void translate(const char* e) {
        int waveIndex = 0;
        int dataIndex = 0;
        int enemyIndex = 0;

        while (e[dataIndex] != '|') {
            waveIndex++;
            while (e[dataIndex] != ' ') {
                int enemyHealth = 0;
                int enemyMoney = 0;
                int enemyRange = 0;
                int enemyAttack = 0;

                switch (e[dataIndex]) {
                    case 'l':
                        enemyHealth = 10;
                        enemyMoney = 5;
                        enemyRange = 2;
                        enemyAttack = 1;
                        enemies.push_back(new Enemy(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
                        break;
                    case 'b':
                        enemyHealth = 50;
                        enemyMoney = 20;
                        enemyRange = 3;
                        enemyAttack = 5;
                        enemies.push_back(new Boss(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
                        break;
                }

                dataIndex++;
enemyIndex++;
            }

            dataIndex++;
        }
    }

    
};

class Player {
public:
    int health;
    int score;
    int kills;
    double money;
    int firerate;

    Player() : health(100), score(0), kills(0), money(0), firerate(0) {}

    void addscore(int a) {
        score += a;
    }

    void addkills(int b) {
        kills += b;
    }

    void setHealth(int a) {
        health = a;
    }

    int getHealth() const {
        return health;
    }

    void setfirerate(int a) {
        firerate = a;
    }

    int getfirerate() const {
        return firerate;
    }

    void reduceHealth(int a) {
        health -= a;
    }

    void gainMoney(double a) {
        money += a;
    }

    double getMoney() const {
        return money;
    }
};

class Map {
public:
    vector<vector<Terrain*>> terrainMap;
    Player p;

    Map() {}

    void printMap() {
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                terrainMap[i][j]->display();
            }
            cout << endl;
        }
    }
    int findStartPoint() {
        for (int i = 0; i < rows; i++) {
            if (r[i][0] == nullptr) {
                for (int j = 0; j < columns; j++) {
                    if (r[i][j]->e->type == 0) {
                        return i;
                    }
                }
            }
        }
        return -1; // Indicate no start point found
    }
    void addTerrain(int x, int y, Terrain* t) {
        terrainMap[x][y] = t;
    }

    

    void moveEnemies(Level& a) {
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Terrain* t = terrainMap[i][j];
                if (t != nullptr && t->getEnemy() != nullptr && t->getEnemy()->getIsVisible()) {
                    t->getEnemy()->moveEnemy(a);
                }
            }
        }
    }

    void attack(Level& a, int currentLoop) {
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Terrain* t = terrainMap[i][j];
                if (t != nullptr && t->getEnemy() != nullptr && t->getEnemy()->getIsVisible()) {
                    t->getEnemy()->attack(a, currentLoop);
                }
            }
        }
    }

    void checkEnemyOutOfMap(Level& a) {
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Terrain* t = terrainMap[i][j];
                if (t != nullptr && t->getEnemy() != nullptr && t->getEnemy()->getIsVisible()) {
                    if (t->getEnemy()->getX() < 0 || t->getEnemy()->getX() >= a.getRows() || t->getEnemy()->getY() < 0 || t->getEnemy()->getY() >= a.getColumns()) {
                        t->getEnemy()->setX(rand() % a.getRows());
                        t->getEnemy()->setY(rand() % a.getColumns());
                    }
                }
            }
        }
    }void updatePlayerPosition() {
        // Implement player position update logic here
    }

    void generateLevelMap(Levelgenerator& lg, Level& level) {
    lg.generatelvl1(level);
    }


    void addScoreAndKillsToPlayer(Level& a) {
        p.addscore(a.score);
        p.addkills(a.kills);
    }

    void savePlayerDataToFile() {
        // Implement saving player data to file logic here
    }

    void checkBossDeath(Level& a) {
        if (a.getIsBossDead()) {
            cout << "Congratulations! You have defeated the boss!" << endl;
        }
    }

    void checkPlayerReachedEndOfLevel(Level& a) {
        // Implement player reached end of level check logic here
    }

    void updatePlayerStats(int enemyDamage, int enemyHealth) {
        // Implement player stat update logic here
    }
};

class Game {
public:
    Level a;
    Levelgenerator lg;
    Map m;

    void playGame() {
        int loops = 0;
        while (true) {
            moveEnemies(a);
            if (p.getfirerate() <= 0) {
                attack(a, loops);
                p.setfirerate(p.getfirerate() - 1);
            }
            checkEnemyOutOfMap(a);
            m.printMap();
            generateLevelMap(lg);
            addScoreAndKillsToPlayer(a);
            checkBossDeath(a);
            checkPlayerReachedEndOfLevel(a);
            updatePlayerStats(a.getEnemyDamage(), a.getEnemyHealth());
            if (p.getHealth() <= 0) {
                cout << "Game Over" << endl;
                break;
            }
            if (loops == a.getLoopCount()) {
                cout << "Level Completed!" << endl;
                break;
            }
            loops++;
            this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
        }
    }

    void menu() {
        cout << "1. Play Game" << endl;
        cout << "2. Exit" << endl;
    }

    void chooseLevels() {
        int choice;
        cout << "Choose a level:" << endl;
        cout << "1. Level 1" << endl;
        cout << "2. Level 2" << endl;
        cout << "3. Level 3" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            lg.generatelvl1(a);
            break;
        case 2:
            lg.generatelvl2(a);
            break;
        case 3:
            lg.generatelvl3(a);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

private:
    void moveEnemies(Level& a) {
        m.moveEnemies(a);
    }

    void attack(Level& a, int currentLoop) {
        m.attack(a, currentLoop);
    }

    void checkEnemyOutOfMap(Level& a) {
        m.checkEnemyOutOfMap(a);
    }
};

int main() {
    Game g;
    g.menu();
    int choice;
    cin >> choice;
    if (choice == 1) {
        g.chooseLevels();
        g.playGame();
    } else {
        return 0;
    }

    return 0;
}