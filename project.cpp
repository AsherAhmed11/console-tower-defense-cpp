#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

class Terrain {
protected:
    int X, Y;
public:
    Terrain(int x, int y) : X(x), Y(y) {}
    virtual void display() = 0; // Pure virtual function
};

class Tower {
protected:
    int X, Y, range, damage, cost, firerate;
public:
    Tower(int x, int y, int r, int d, int c, int f)
        : X(x), Y(y), range(r), damage(d), cost(c), firerate(f) {}

    virtual void fire() = 0; // Pure virtual function
};

class Gun : public Tower {
public:
    Gun(int x, int y, int r, int d, int c, int f)
        : Tower(x, y, r, d, c, f) {}

    void fire() override {
        std::cout << "Gun firing at (" << X << ", " << Y << ") with damage " << damage << std::endl;
    }
};

class MachineGun : public Tower {
public:
    MachineGun(int x, int y, int r, int d, int c, int f)
        : Tower(x, y, r, d, c, f) {}

    void fire() override {
        std::cout << "MachineGun firing at (" << X << ", " << Y << ") with damage " << damage << std::endl;
    }
};

class Sniper : public Tower {
public:
    Sniper(int x, int y, int r, int d, int c, int f)
        : Tower(x, y, r, d, c, f) {}

    void fire() override {
        std::cout << "Sniper firing at (" << X << ", " << Y << ") with damage " << damage << std::endl;
    }
};

class Magic : public Tower {
public:
    Magic(int x, int y, int r, int d, int c, int f)
        : Tower(x, y, r, d, c, f) {}

    void fire() override {
        std::cout << "Magic firing at (" << X << ", " << Y << ") with damage " << damage << std::endl;
    }
};

class Enemy {
protected:
    int health, speed;
public:
    Enemy(int h, int s) : health(h), speed(s) {}
    virtual void move() = 0; // Pure virtual function
};

class Boss : public Enemy {
public:
    Boss(int h, int s) : Enemy(h, s) {}

    void move() override {
        std::cout << "Boss moving with speed " << speed << std::endl;
    }
};

class Tank : public Enemy {
    int armour;
public:
    Tank(int h, int s, int a) : Enemy(h, s), armour(a) {}

    void move() override {
        std::cout << "Tank moving with speed " << speed << " and armour " << armour << std::endl;
    }
};

class Armoured : public Enemy {
public:
    Armoured(int h, int s) : Enemy(h, s) {}

    void move() override {
        std::cout << "Armoured enemy moving with speed " << speed << std::endl;
    }
};

class Road : public Terrain {
    Enemy* e;
    Boss* b;
public:
    Road(int x, int y) : Terrain(x, y), e(nullptr), b(nullptr) {}

    void setEnemy(Enemy* enemy) {
        e = enemy;
    }

    void setBoss(Boss* boss) {
        b = boss;
    }

    void display() override {
        std::cout << "Road at (" << X << ", " << Y << ")" << std::endl;
    }
};

class Grass : public Terrain {
    Tower* t;
public:
    Grass(int x, int y) : Terrain(x, y), t(nullptr) {}

    void setTower(Tower* tower) {
        t = tower;
    }

    void display() override {
        std::cout << "Grass at (" << X << ", " << Y << ")" << std::endl;
    }
};

class Hill : public Terrain {
    bool built;
public:
    Hill(int x, int y) : Terrain(x, y), built(false) {}

    void build() {
        built = true;
    }

    void display() override {
        std::cout << "Hill at (" << X << ", " << Y << "), built: " << built << std::string line;
                while (getline(file, line)) {
                    std::cout << line << std::endl;
                }
                file.close();
            } catch (const std::exception& e) {
                std::cerr << "Error loading game: " << e.what() << std::endl;
            }
        }
    }
};

int main() {
    try {
        // Create a map
        Map* gameMap = new Map();
        
        // Add terrain elements
        gameMap->addRoad(new Road(1, 1));
        gameMap->addGrass(new Grass(2, 2));
        gameMap->addHill(new Hill(3, 3));

        // Display map
        gameMap->display();
        
        // Create a player
        Player player("John Doe");
        player.addScore(100);
        player.savePlayer("player.txt");
        player.loadPlayer("player.txt");
        
        // Create a level
        Level level(gameMap);
        Wave* wave1 = new Wave();
        wave1->addEnemy(new Boss(1000, 10));
        wave1->addEnemy(new Tank(500, 5, 50));
        level.addWave(wave1);

        // Save and load level
        level.saveLevel("level.txt");
        level.loadLevel("level.txt");

        // Start the game
        Game game;
        game.startGame();
        game.saveGame("game.txt");
        game.loadGame("game.txt");

        // Clean up
        delete gameMap;
        delete wave1;

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}


