#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Level;
class Game;
class Levelgenerator;
class Map;
class Player;
class Wave;
class Tower;
class Enemy;
class Boss;
class Terrain;
class Road;
class Grass;
class Hill;
class Placedtowers;
class Trap;
class Gun;
class MachineGun;
class Sniper;
class Magic;
class ammunition_depot;
class Boss;


class Game {
public:
    void playGame() {
        Level a;
        int loops = 0;
        while (true) {
            // move enemy function called every 5 loops
            loops++;
            if (loops % 5 == 0) {
                moveEnemies(a);
            }
            // attack function called every loop but no attacks until firerate is reached
            if (p.getfirerate() <= 0) {
                attack(a, loops);
                p.setfirerate(p.getfirerate() - 1);
            }
            // Check if enemies are out of map and reposition them
            for (int i = 0; i < a.getTerrainMap().size(); ++i) {
                for (int j = 0; j < a.getTerrainMap()[i].size(); ++j) {
                    if (a.getTerrainMap()[i][j]->t != nullptr && a.getTerrainMap()[i][j]->t->getIsVisible()) {
                        if (a.getTerrainMap()[i][j]->getEnemy()->getx() < 0 || a.getTerrainMap()[i][j]->getEnemy()->getx() >= a.getTerrainMap().size() || a.getTerrainMap()[i][j]->getEnemy()->gety() < 0 || a.getTerrainMap()[i][j]->getEnemy()->gety() >= a.getTerrainMap()[i].size()) {
                            a.getTerrainMap()[i][j]->getEnemy()->setx(std::rand() % a.getTerrainMap().size());
                            a.getTerrainMap()[i][j]->getEnemy()->sety(std::rand() % a.getTerrainMap()[i].size());
                        }
                    }
                }
            }

            // update player position
            m.printMap();
            // if (p.getx() >= a.getTerrainMap().size() || p.getx() < 0 || p.gety() >= a.getTerrainMap()[0].size() || p.gety() < 0) {
            //     cout << "Game Over" << endl;
            //     break;
            // }
            // generate the level map
            Levelgenerator l;
            l.generatelvl1(a);
            m.printMap();

            // add score and kills to player
            p.addscore(a.score);
            p.addkills(a.kills);

            // save player data to file
            // p.savedatatoFile();

            if (a.getIsBossDead()) {
                cout << "Congratulations! You have defeated the boss!" << endl;
                break;
            }

            // check if player has reached the end of the level
            // if (p.getx() >= a.getEndX() && p.gety() >= a.getEndY()) {
            //     cout << "Level Completed!" << endl;
            //     break;
            // }

            // update player stats
            p.updateStats(a.getEnemyDamage(), a.getEnemyHealth());
            if (p.getHealth() <= 0) {
                cout << "Game Over" << endl;
                break;
            }

            // level end
            if (loops == a.getLoopCount()) {
                cout << "Level Completed!" << endl;
                break;
            }

            // wait a bit
            // this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
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
            Levelgenerator lg;
            lg.generatelvl1(a);
            break;
        case 2:
            Levelgenerator lg;
            lg.generatelvl2(a);
            break;
        case 3:
            Levelgenerator lg;
            lg.generatelvl3(a);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

private:
    void moveEnemies(Level& a) {
        for (int i = 0; i < a.getTerrainMap().size(); ++i) {
            for (int j = 0; j < a.getTerrainMap()[i].size(); ++j) {
                if (a.getTerrainMap()[i][j]->t != nullptr && a.getTerrainMap()[i][j]->t->getIsVisible()) {
                    a.getTerrainMap()[i][j]->t->moveEnemy(a);
                }
            }
        }
    }

    void attack(Level& a, int currentLoop) {
        for (int i = 0; i < a.getTerrainMap().size(); ++i) {
            for (int j = 0; j < a.getTerrainMap()[i].size(); ++j) {
                if (a.getTerrainMap()[i][j]->t != nullptr && a.getTerrainMap()[i][j]->t->getIsVisible()) {
                    a.getTerrainMap()[i][j]->t->attack(a, currentLoop);
                }
            }
        }
    }

    Levelgenerator lg;
    Map m;
    Player p;
};

class Levelgenerator {
public:
    void generatelvl1(Level& i) {
        char* wavedata = "llll";
        i.translatewave(wavedata);
    }
    void generatelvl2(Level& i) {
        char* wavedata="wlwlwlwlw";
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
        char* wavedata="wllllw";
    i.setstartcash(100);
    i.setstartscore(0);
    i.setstartkills(0);
    }


};

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
public:
    Wave *w[9];

    Map *m;
    int money = 0;
    int health = 100;


    void translatemap(int a) {
        switch (a) {
            case 1:
                m->r[0][0]->e = new Grass();
                break;
            case 2:
                m->r[0][0]->e = new Hill();
                break;
            case 3:
                m->r[0][0]->e = new Road();
                break;
        }
    }

    void setstartcash(int cash) {
        money = cash;
    }

    int getstartcash() {
        return money;
    }

    void setstartscore(int score) {
        this->score = score;
    }

    int getstartscore() {
        return score;
    }

    void setstartkills(int kills) {
        this->kills = kills;
    }

    int getstartkills() {
        return kills;
   }
   void getTerrainMap() {
       // Print the terrain map
       for (int i = 0; i < m->rows; i++) {
           for (int j = 0; j < m->columns; j++) {
               switch (m->r[i][j]->e->type) {
                   case 0:
                       cout << " ";
                       break;
                   case 1:
                       cout << "G";
                       break;
                   case 2:
                       cout << "H";
                       break;
                   case 3:
                       cout << "R";
                       break;
               }
           }
           cout << endl;
       }
   }
   void translatewave(const char* e) {
    int waveIndex = 0; // Index for the wave
    int dataIndex = 0; // Index for parsing the input string
    int enemyIndex = 0; // Index for traversing the input string

    // Initialize enemies vector for each wave
    enemies.resize(10);

    while (e[dataIndex] != '|') { // Continue until '|' is encountered
        waveIndex++;
        while (e[dataIndex] != ' ') { // Continue until space is encountered
            int enemyHealth = 0;
            int enemyMoney = 0;
            int enemyRange = 0;
            int enemyAttack = 0;

            switch (e[dataIndex]) {
                case 'l':
                    enemyHealth = 10; // Adjust health value as needed
                    enemyMoney = 5; // Adjust money value as needed
                    enemyRange = 2; // Adjust range value as needed
                    enemyAttack = 1; // Adjust attack value as needed
                    enemies[waveIndex].push_back(new Enemy(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
                    break;
                case 'b':
                    enemyHealth = 50; // Adjust health value for a boss
                    enemyMoney = 20; // Adjust money value for a boss
                    enemyRange = 3; // Adjust range value for a boss
                    enemyAttack = 5; // Adjust attack value for a boss
                    enemies[waveIndex].push_back(new Boss(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
            }
            dataIndex++; // Move to the next character in the input string
            enemyIndex++; // Increment enemy index
        }
        dataIndex++; // Move past the space character
    }
}

    void printEnemies() {
        for (int i = 0; i < enemies.size(); i++) {
            std::cout << "Wave " << i + 1 << ":\n";
            for (int j = 0; j < enemies[i].size(); j++) {
                Enemy *e = dynamic_cast<Enemy*>(enemies[i][j]);
                Boss *b = dynamic_cast<Boss*>(enemies[i][j]);
                if (e != nullptr) {
                    cout << "Enemy " << j + 1 << ": Health = " << e->health << ", Money = " << e->money << ", Position = (" << e->x << ", " << e->y << ")\n";
                }
                else if (b != nullptr) {
                    cout << "Enemy " << j + 1 << ": Health = " << b->health << ", Money = " << b->money << ", Position = (" << b->x << ", " << b->y << ")\n";
                }
            }
        }
    }
    
    private:
    std::vector<std::vector<Enemy*>> enemies;// Vector of vectors to store enemies for each wave

    int findstartpoint() {
        // yay batao user input ha ya map say khud identify krni upper code khud identify k Lia hua WA agr user I put ja to changes needed 
        
        return 0; // Placeholder value
    }
};

class Wave {
    public:
    // Vector to store enemy objects
    std::vector<Enemy*> enemies;

    // Constructor to initialize the wave
    Wave() {}

    // Function to translate the input string and create enemy objects
    void translate(const char* e) {
        int dataIndex = 0; // Index for parsing the input string
        int enemyIndex = 0; // Index for traversing the input string

        while (e[dataIndex] != '|') { // Continue until '|' is encountered
            int enemyHealth = 0;
            int enemyMoney = 0;
            int enemyRange = 0;
            int enemyAttack = 0;

            switch (e[dataIndex]) {
                case 'l':
                    enemyHealth = 10; // Adjust health value as needed
                    enemyMoney = 5; // Adjust money value as needed
                    enemyRange = 2; // Adjust range value as needed
                    enemyAttack = 1; // Adjust attack value as needed
                    enemies.push_back(new Enemy(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
                    break;
                case 'b':
                    enemyHealth = 50; // Adjust health value for a boss
                    enemyMoney = 20; // Adjust money value for a boss
                    enemyRange = 3; // Adjust range value for a boss
                    enemyAttack = 5; // Adjust attack value for a boss
                    enemies.push_back(new Boss(enemyHealth, enemyMoney, -enemyIndex, findstartpoint(), enemyRange, enemyAttack));
            }
            dataIndex++; // Move to the next character in the input string
            enemyIndex++; // Increment enemy index
        }
    }
     
};
class Terrain{
public:
    // Vector to store terrain objects
    std::vector<TerrainObject*> terrainObjects;

    // Enum to represent different types of terrain
    enum TerrainType {
        GRASS,
        WATER,
        HILL
    };

    // Struct to represent a terrain object
    struct TerrainObject {
        TerrainType type;
        Point position;

        // Constructor to initialize a terrain object
        TerrainObject(TerrainType type, Point position) : type(type), position(position) {} 
    };

    // Constructor to initialize the terrain
    Terrain() {}

    // Function to add a terrain object to the terrain
    void addTerrainObject(TerrainObject* terrainObject) {
        terrainObjects.push_back(terrainObject);
    }

    // Function to check if a point is on a terrain object
    bool isOnTerrain(Point point) {
        for (auto& terrainObject : terrainObjects) {
            if (terrainObject->type == GRASS && terrainObject->position.distance(point) < 5) {
                return true;
            }
            else if (terrainObject->type == WATER && terrainObject->position.distance(point) < 5) {
                return true;
            }
            else if (terrainObject->type == HILL && terrainObject->position.distance(point) < 10) {
                return true;
            }
        }
        return false;
    }
    int display()  {

        for (auto& terrainObject : terrainObjects) {
            switch (terrainObject->type) {
            case GRASS:
                cout << "g";
                break;
            case WATER:
                cout << "w";
                break;
            case HILL:
                cout << "h";
                break;
            }
        }

        return 0;

    }
    // Function to activate a terrain
    void activate() {

        // Loop through all enemies on the terrain and reduce their health points
        for (auto& enemy : enemyOnTerrain) {
            enemy->loseHealth(5, *this->level);
        }

        // Loop through all traps on the terrain and activate them
        for (auto& trap : trapOnTerrain) {
            trap->activate();
        }

    }
};

class Road : public Terrain {
public:
    Enemy *e;
    Trap *t;
    Boss* b;
    bool onmap;
public:

    Road() : Terrain() {
        e = 0;
        t = 0;
        onmap = false;
    }

    Road(int a) : Terrain(a) {
        e = NULL;
        t = NULL;
        onmap = true;
    }

    int display() override {
        return 1; // Return a value to indicate this is a road tile
    }

    void activate() override {
        // Add special effects for road tiles here
    }
};


class Grass : public Terrain {
public:
    Tower *t;

public:
    Grass() {
        t = NULL;
    }

    Grass(int a) {
        t = 0;
    }

    int display() override {
        return 1; // Return a value to indicate this is a grass tile
    }

    void activate() override {
        // Loop through all enemies on the tile and reduce their health points
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Enemy* e = terrainMap[i][j]->e;
                if (e != nullptr) {
                    e->loseHealth(5, p);
                }
            }
        }
    }
};


class Hill :public Terrain{
public:
    bool built;
    Tower *t;

    Hill(){
        t=NULL;
        built=false;
    }

    Hill(int a){
        t=0;
        built=true;
    }

    int display() override {
        return 2; // Return a value to indicate this is a hill tile
    }

    void activate() override {
        // Loop through all enemies on the tile and reduce their health points
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Enemy* e = terrainMap[i][j]->e;
                if (e != nullptr) {
                    e->loseHealth(3, p);
                }
            }
        }
    }

    bool isBuilt() {
        return built;
    }

    void setBuilt(bool built) {
        this->built = built;
    }

    Tower* getTower() {
        return t;
    }

    void setTower(Tower* t) {
        this->t = t;
    }
};

class Placedtowers {
    friend class Gun;
    friend class MachineGun;
    friend class Sniper;
    friend class Magic;
    // friend class antiarmor;
    friend class Mantainence;
    friend class Tower;
    friend class Grass;
    friend class Water;
    friend class Road;
    friend class Level;
  //  friend class level;
    std::vector<vector<Terrain*>> &terrainMap; // Reference to the map's terrain
    Player &p; // Reference to the player object
    Gun *g;
    MachineGun*mg;
    Sniper *s;
    Magic *m;
    // antiarmor *a;
    // antiboss *ab;
    public:
        //void attack(level *l,int a) { // a refers to  no of ingame loop. firerarte refers to the number of loops before every fire.(enemy moves arpund every 5 loops)  
   
    //  Placedtowers(vector<vector<Terrain*>>&terrainMap, Player&playerObj) 
    //     : terrainMap(terrainMap), p(playerObj) {}

    void attack(Level* l, int currentLoop) {
        for (int i = 0; i < terrainMap.size(); ++i) {
            for (int j = 0; j < terrainMap[i].size(); ++j) {
                if (terrainMap[i][j]->t != nullptr) {
                    terrainMap[i][j]->t->attack(l, currentLoop);
                }
            }
        }
    }
    
    void placeTower(Level& level) {
        int towerType, x, y;
        
        // Ask the player to choose the type of tower
        cout << "Enter the type of tower to place (1. Gun, 2. Machinegun, 3. Sniper, 4. Magic): ";
        cin >> towerType;

        // Validate the tower type
        if (towerType < 1 || towerType > 4) {
            cout << "Invalid tower type!" << endl;
            return;
        }

        // Ask the player to enter the coordinates to place the tower
        cout << "Enter the coordinates (x y) to place the tower: ";
        cin >> x >> y;

        // Validate the coordinates
        if (x < 0 || x >= level.m->size() || y < 0 || y >= level.m->at(0).size()) {
            cout << "Invalid coordinates!" << endl;
            return;
        }

        // Check if there's already a tower at the specified location
        if (level.m->at(x).at(y)->t != nullptr) {
            cout << "A tower is already placed at this location!" << endl;
            return;
        }

        // Create a new tower based on the chosen type
        Tower* newTower = nullptr;
        switch (towerType) {
            case 1:
                newTower = new Gun(x, y); // Assuming Gun tower constructor takes x and y coordinates
                break;
            case 2:
                newTower = new MachineGun(x, y); // Assuming MachineGun tower constructor takes x and y coordinates
                break;
            case 3:
                newTower = new Sniper(x, y); // Assuming Sniper tower constructor takes x and y coordinates
                break;
            case 4:
                newTower = new Magic(x, y); // Assuming Magic tower constructor takes x and y coordinates
                break;
        }

        // Check if the player has enough money to place the tower
        if (p.money < newTower->cost) {
            cout << "Insufficient funds to place this tower!" << endl;
            delete newTower;
            return;
        }

        // Place the tower on the map
        level.m->at(x).at(y)->t = newTower;
        p.money -= newTower->cost; // Deduct the tower cost from the player's money
        cout << "Tower placed successfully!" << endl;
    }
    
    void Placetower(Level& l) {
        int towerType, x, y;
        cout << "Enter the type of tower to place (1. Gun, 2. Machinegun, 3. Sniper, 4. Magic): ";
        cin >> towerType;

        if (towerType < 1 || towerType > 4) {
            cout << "Invalid tower type!" << endl;
            return;
        }

        cout << "Enter the coordinates (x y) to place the tower: ";
        cin >> x >> y;

        if (x < 0 || x >= terrainMap.size() || y < 0 || y >= terrainMap[0].size()) {
            cout << "Invalid coordinates!" << endl;
            return;
        }

        if (terrainMap[x][y]->t != nullptr) {
            cout << "A tower is already placed at this location!" << endl;
            return;
        }

        Tower* newTower = nullptr;
        switch (towerType) {
            case 1:
                newTower = new Gun();
                break;
            case 2:
                newTower = new MachineGun();
                break;
            case 3:
                newTower = new Sniper();
                break;
            case 4:
                newTower = new Magic();
                break;
        }

        if (p.money < newTower->cost) {
            cout << "Insufficient funds to place this tower!" << endl;
            delete newTower;
            return;
        }

        terrainMap[x][y]->t = newTower;
        p.money -= newTower->cost;
        cout << "Tower placed successfully!" << endl;
    }
};

class Trap {
protected:
    int cost;
public:
    Trap(int cost) : cost(cost) {}

    virtual int display() = 0;
    virtual void activate() = 0;
};

// Example trap that reduces the player's health by 10
class PlayerHealthTrap : public Trap {
public:
    PlayerHealthTrap(int cost) : Trap(cost) {}

    int display() override {
        return 2; // Return a value to indicate this is a player health trap
    }

    void activate() override {
        p.health -= 10;
    }
};

// Example trap that damages all enemies on the tile
class EnemyDamageTrap : public Trap {
public:
    EnemyDamageTrap(int cost) : Trap(cost) {}

    int display() override {

        return 3; // Return a value to indicate this is an enemy damage trap
    }

    void activate() override {
        // Loop through all enemies on the tile and reduce their health points
        for (int i = 0; i < terrainMap.size(); i++) {
            for (int j = 0; j < terrainMap[i].size(); j++) {
                Enemy* e = terrainMap[i][j]->e;
                if (e != nullptr) {
                    e->loseHealth(10, p);
                }
            }
        }
    }
};

class Player {
private:
    int health = 100;
    int score = 0;
    int kills = 0;
    double money = 0;
    int firerate = 0; // seconds

public:
    Player() : health(100), firerate(0) {}

    void addscore(int a) { // a is the score to be added to level
        score += a;
    }

    void addkills(int b) //all kills added end of the wave
    {
        kills += b;
    }

    void setHealth(int a) { health = a; }
    int getHealth() const { return health; }

    void setfirerate(int a) { firerate = a; }
    int getfirerate() const { return firerate; }

    void reduceHealth(int a) { health -= a; }
    void gainMoney(double a) { money += a; }
    double getMoney() const { return money; }
};
class Map {
private:
    Hill* h[15][10];
    Road* r[15][10];
    Grass* g[15][10];
    Tower** towers;
    int numTower;
public:
    Map() : numTower(0) {}

    int findStartPoint() {
        for (int i = 0; i < 15; i++) {
            if (r[i][0] == nullptr) {
                return i;
            }
        }
        return -1; // Indicate no start point found
    }

    void printMap() {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 10; j++) {
                if (r[i][j] != nullptr && r[i][j]->e != nullptr && r[i][j]->e != 0) {
                    cout << "E";
                } else if (r[i][j] != nullptr && r[i][j]->t != nullptr && r[i][j]->t != 0) {
                    cout << r[i][j]->t->display();
                } else if (r[i][j] != nullptr && r[i][j]->b != nullptr && r[i][j]->b != 0) {
                    cout << "b";
                } else if (r[i][j] == nullptr || (r[i][j]->b == nullptr && r[i][j]->e == nullptr)) {
                    cout << "_";
                }
                if (h[i][j] != nullptr && h[i][j]->t == nullptr) {
                    cout << "^";
                } else if (g[i][j] != nullptr && g[i][j]->t != nullptr) {
                    g[i][j]->t->display();
                } else if (g[i][j] != nullptr && g[i][j]->t == nullptr) {
                    cout << ',';
                } else if (h[i][j] != nullptr && h[i][j]->t != nullptr) {
                    h[i][j]->t->display();
                }
            }
            cout << endl;
        }
    }

    void addTower(Tower* t, int x, int y) {
        if (r[x][y] != nullptr && r[x][y]->t == nullptr && r[x][y]->e == nullptr && r[x][y]->b == nullptr) {
            r[x][y]->t = t;
            towers[numTower] = r[x][y];
            numTower++;
        }
    }

    void moveEnemy() {
        for (int i = 14; i >= 0; i--) { 
            for (int j = 9; j >= 0; j--) {
                if (r[i][j] != nullptr && r[i][j]->e != nullptr) {
                    if (i + 1 < 15 && (r[i + 1][j]->e == nullptr || r[i + 1][j]->e == 0)) {
                        r[i + 1][j]->e = r[i][j]->e;
                        r[i + 1][j]->e->setCoordinate(i + 1, j);
                        r[i][j]->e = nullptr;
                    } else if (j + 1 < 10 && (r[i][j + 1]->e == nullptr || r[i][j + 1]->e == 0)) {
                        r[i][j + 1]->e = r[i][j]->e;
                        r[i][j + 1]->e->setCoordinate(i, j + 1);
                        r[i][j]->e = nullptr;
                    }
                }
            }
        }
    }
};



class Tower {
public:
    int x, y; // Coordinates
    int range;
    int damage;
    int cost;
    int firerate; // Fire rate in milliseconds
    int sellCost; // Sell cost of the tower
public:
    Tower(int x, int y, int range, int damage, int cost, int fireRate, int sellCost) : x(x), y(y), range(range), damage(damage), cost(cost), firerate(fireRate), sellCost(sellCost) {}

    virtual void attack(Level *level, int currentLoop) = 0;

    virtual void display() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }

    // Sell the tower and return the sell cost
    int sell() {
        return sellCost;
    }
};

class Gun : public Tower {
public:
    GunTower(int x, int y) : Tower(x, y, 3, 10, 50, 500) {}

    void attack(level *l, int currentLoop) {
        if (currentLoop % firerate == 0) {
            for (int i = 0; pow(i, 2) <= pow(range, 2); i++) {
                for (int j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                    if (l->m->r[x + i][y + j]->e != nullptr) {
                        l->m->r[x + i][y + j]->e->loseHealth(damage, *l);
                        break;
                    }
                }
            }
        }
    }

    void display() const override {
        cout << "G";
    }
};

class MachineGun : public Tower {
public:
    MachineGunTower(int x, int y) : Tower(x, y, 5, 5, 100, 200) {}

    void attack(level *l, int currentLoop) {
        int j = 0;
        if (currentLoop % firerate == 0) {
            for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
                for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                    if (l->m->r[x + i][y + j]->e != nullptr) {
                        l->m->r[x + i][y + j]->e->loseHealth(damage, *l);
                        break;
                    }
                }
            }
        }
    }

    void display() const override {
        cout << "M";
    }
};

class Sniper : public Tower {
public:
    Sniper(int x, int y) : Tower(x, y, 10, 50, 100, 1000) {}

    void attack( level *l, int currentLoop) {
        int j = 0;
        if (currentLoop % firerate == 0) {
            for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
                for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                    if (l->m->r[x + i][y + j]->e != nullptr) {
                        l->m->r[x + i][y + j]->e->loseHealth(damage, *l);
                        break;
                    }
                }
            }
        }
    }

    void display() const override {
        cout << "S";
    }
};


class Magic : public Tower {
public:
    MagicTower(int x, int y) : Tower(x, y, 5, 20, 200, 1500) {}

    void attack( level *l, int currentLoop) {
        int j = 0;
        if (currentLoop % firerate == 0) {
            for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
                for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                    if (l->m->r[x + i][y + j]->e != nullptr) {
                        l->m->r[x + i][y + j]->e->loseHealth(damage, *l);
                        break;
                    }
                }
            }
        }
    }

    void display() const override {
        cout << "C";
    }
};

class Dushman{
    friend class Map;
    int health;
    int money;
    int x,y;
    virtual void display() const = 0;

    virtual bool losehealth(int damage, Level& l) = 0;
    public:
        Dushman(int h, int m, int x, int y) : health(h), money(m), x(x), y(y) {}
        int getHealth() const {
        return health;
    }

    int getMoney() const {
        return money;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setCoordinate(int a, int b, Level& i) {
        x = a;
        y = b;

        if (a >= 10 || b >= 10) {
            i.m->r[x][y]->e = nullptr;
            return;
        }

        if (i.m->r[x][y]->e != nullptr) {
            i.m->r[x][y]->e->setCoordinate(-1, -1, i);
        }

        i.m->r[x][y]->e = this;
    }  
};
class Enemy: public Dushman  {
public:
    Enemy(int h, int m, int x, int y) : Dushman(h, m, x, y){}
    
    virtual ~Enemy() = default;
    
    virtual void display() override {
        cout << "E";
    }
    
    virtual bool losehealth(int damage, Level& l) override {
        health -= damage;
        if (health <= 0) {
            l.m->r[x][y]->e = nullptr;
            return true;
        }
        return false;
    }
    
};

class Boss : public Enemy {
public:
    Boss(int h, int d, int s, int a) : Enemy(h, d, s, a) {}

    void display() override {
    // Boss(int h, int d, int s, int a) : health(h), damage(d), speed(s), armor(a) {}
        cout << "b";
    }

    bool losehealth(int damage, Level& l) override {
        health -= damage;
        if (health <= 0) {
            l.money += money;
            l.m->r[x][y]->e = nullptr;
            return true;
        }
        return false;
    }

    void attack(int x, int y, Level& l) {
        if (x >= 0 && y >= 0 && x < l.m->n && y < l.m->m && l.m->r[x][y]->e == nullptr) {
            Enemy* e = new Tank(health, money, x, y);
            l.m->r[x][y]->e = e;
            e->setMoney(money);
            l.m->r[x][y]->e->setCoordinate(x, y, l);
            l.m->r[x][y]->e->display();
        }
    }

    ~Boss() {}

    // Traps do not work on these guys and they just disintegrate.
    // can atk
};


class Tank : public Enemy {
public:
    Tank(int h, int m, int x, int y) : Enemy(h, m, x, y) {}

    void display() override {
        cout << "T";
    }

    bool losehealth(int damage, Level& l) override {
        health -= damage;
        if (health <= 0) {
            l.money += money;
            l.m->r[x][y]->e = nullptr;
            return true;

        }
        return false;
 
    }

    void attack(int x, int y, Level& l) {
        if (x >= 0 && y >= 0 && x < l.m->n && y < l.m->m && l.m->r[x][y]->e == nullptr) {
            Enemy* e = new Tank(health, money, x, y);
            l.m->r[x][y]->e = e;
            e->setMoney(money);
            l.m->r[x][y]->e->setCoordinate(x, y, l);
            l.m->r[x][y]->e->display();
        }
    }

    ~Tank() {}
};
class Armoured : public Enemy
{
private:
    int armour;// level of armur
public:
    Armoured(int h, int m, int x, int y, int a) : Enemy(h, m, x, y)
    {
        armour = a;
    }

    bool losehealth(int damage, Level& l) override
    {
        health -= (damage / (3.14 * armour) + (0.3 * pow(damage, log(3)) + 10);

        if (health <= 0)
        {
            l.money += money;
            l.m->r[x][y]->e = nullptr;

            return true;
        }

        return false;
    }
    // armoured trooop,takes less damage frim all towers except 1.
};