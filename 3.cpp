#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Forward declarations
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
// class antiarmor;
class ammunition_depot;
// class antiboss;
// class armoured;
class Boss;

class Game{
public:
    void playgame(){
        Level a;
        int loops;// refers to no of loops;
        //move enemy function called every 5 loops
        // attack function called every loop but no attacks until firerate is reached\
        // IF ENEMY IS OUT OF THE MAP ITS COORDINATES WILL BECOME NEGATIVE BUT WHEN THEY BECOME POSITIVE BY INCREMENT THEY APPEAR ON MAP
        // this is incomplete but i wrote some random lines to clear some doubtsa
     // HEALTH IS IN LEVEL. AND IT SHOULD STAY THERE

            m.printMap();
            Levelgenerator l;
            l.generatelvl1(a);// printing map is incomplete ( grass aand hills and towers left TUM LOG KHUD KROGE LOL)
            // opper kia kiya ha chrnono shronno mere samjah m nahi aya mene player class ki filing k lia leverl end p yahan function call kiya ha 
            p.addscore(a.score); // define score in level a
            p.addkills(a.kills); // define kills in level a
            // p.safedatatofile();


        
        }
    
    void menu(){
        cout << "1. Play Game" << endl;
                

                    cout << "2. Exit" << endl;

    }
    void chooselevels(){


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
        
    }
    void generatelvl3(Level& i) {


    }


};

class Level {
public:
int score=0; // score for level
int kills=0; // kill for level
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
int money;
int health;
void translatemap(int a){
switch(a){
case 1:


break;
case 2:


break;
case 3:


break;


}
}// app sub ko pta he yehan krna kiya he

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
            switch (e[dataIndex]) {
                case 'l':
                    enemyHealth = 10; // Adjust health value as needed
                    enemyMoney = 5; // Adjust money value as needed
                    enemies[waveIndex].push_back(new Enemy(enemyHealth, enemyMoney, -enemyIndex, findstartpoint()));
                    break;
                case 'b':
                    enemyHealth = 50; // Adjust health value for a boss
                    enemyMoney = 20; // Adjust money value for a boss
                    enemies[waveIndex].push_back(new Boss(enemyHealth, enemyMoney, -enemyIndex, findstartpoint()));
                    break;
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
                cout << "Enemy " << j + 1 << ": Health = " << enemies[i][j]->health << ", Money = " << enemies[i][j]->money << ", Position = (" << enemies[i][j]->x << ", " << enemies[i][j]->y << ")\n";
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
    friend class enemy;
    friend class boss;
    friend class level;

    Enemy* e[10];
    public:
    Wave(){}

    
        
    
};
class Terrain{
public:


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
  //  friend class level;
    std::vector<vector<Terrain*>> &terrainMap; // Reference to the map's terrain
    Player &p; // Reference to the player object
Gun *g;
MachineGun*mg;
Sniper *s;
Magic *m;
// antiarmor *a;
// antiboss *ab;
friend class Level;
public:
    //void attack(level *l,int a) { // a refers to  no of ingame loop. firerarte refers to the number of loops before every fire.(enemy moves arpund every 5 loops)  
       // for (int i = 0; i < 3; i++) {
         //   for (int j = 0; j < 3; j++) {
            //    if (l->m->g[i][j]->t!= nullptr) {
                    l->m ->g[i][j]->t->attack(l,a);
             //   }
           // }
       // }
   // }

    Placedtowers(vector<vector<Terrain*>>& terrainMap, Player& playerObj) 
        : terrainMap(terrainMap), p(playerObj) {}

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

        // Place thetower on the map
        level.m->at(x).at(y)->t = newTower;
        p.money -= newTower->cost; // Deduct the tower cost from the player's money
        cout << "Tower placed successfully!" << endl;
    }

};

class Trap;

class Road:public Terrain {
public:
    Enemy *e;
    Trap *t;
    Boss* b;
public:
    bool onmap;
    Road() {
        e = 0;
        t = 0;
        onmap=false;
    }
    Road(int a){
        e = NULL;
                    t = NULL;
                    onmap=true;

    }

};

class Grass:public Terrain {
    public:

    Tower *t;

public:
Grass(){
    t=NULL;
}
Grass(int a){
    t=0;
}

};

class Hill :public Terrain{
public:
    bool built;
    Tower *t;
    Hill(){
        t=NULL;
        built=false;
    }    Hill(int a){
        t=0;
        built=true;
    }
};

class Player {
public:
    int score=0;
    int kills=0;
    double money=0;
    void addscore(int a){  // a is the score to be added to level

        
        score +=a;
        
        
        }
        void addkills(int b) //all kills added end of the wave
        {    
            kills  +=b;
        }
};
class Map {
private:
    Hill* h[15][10];
    Road* r[15][10];
    Grass* g[15][10];
public:
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

    void moveEnemy() {
        for (int i = 14; i >= 0; i--) { 
            for (int j = 9; j >= 0; j--) {
                if (r[i][j] != nullptr && r[i][j]->e != nullptr) {
                    if (i + 1 < 15 && (r[i + 1][j]->e == nullptr || r[i+ 1][j]->e == 0)) {
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
public:
    Tower(int x, int y, int range, int damage, int cost, int fireRate) : x(x), y(y), range(range), damage(damage), cost(cost), firerate(fireRate) {}

    virtual void attack(Level* level, int currentLoop) = 0;

    virtual void display() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
};

class Gun : public Tower {
public:
    GunTower(int x, int y) : Tower(x, y, 3, 10, 50, 500) {}

    void attack( Level *l,int a) {
        int j = 0;
        if(a % firerate==0){
        for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
            for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                if (l->m->r[x + i][y + j]->e!= nullptr) {
                    
                    break;
                }
            }
        }}
    }

    void display() const override {
        cout << "G";
    }
};

class MachineGun : public Tower {
public:
    MachineGunTower(int x, int y) : Tower(x, y, 5, 5, 100, 200) {}

    void attack( Level *l,int a) {
        int j = 0;
        if(a%firerate==0){
        for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
            for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                if (l->m->r[x + i][y + j]->e!= nullptr) {
                    
                    break;
                }
            }
        }}
    }

    void display() const override {
        cout << "M";
    }
};

class Sniper : public Tower {
public:
    Sniper(int x, int y) : Tower(x, y, 10, 50, 100, 1000) {}

    void attack( Level *l,int a) {
        int j = 0;
        if(a%firerate==0){
        for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
            for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                if (l->m->r[x + i][y + j]->e!= nullptr) {
                    
                    break;
                }
            }
        }}
    }

    void display() const override {
        cout << "S";
    }
};

class Magic : public Tower {
public:
MagicTower(int x, int y) : Tower(x, y, 5, 20, 200, 1500) {}

    void attack( Level *l,int a) {
        int j = 0;
        if(a%firerate==0){
        for (int i = 0; pow(i, 2) <= pow(range, 2) - pow(j, 2); i++) {
            for (j = 0; j <= sqrt(pow(range, 2) - pow(i, 2)); j++) {
                if (l->m->r[x + i][y + j]->e!= nullptr) {
                    
                    break;
                }
            }
        }}
    }

    void display() const override {
        cout << "C";
    }
};

class Trap {
public:
    virtual int display() = 0;
    virtual void activate() = 0;
};

class EnemyDamage : public Trap {
public:
    int display() override {

        return 1; // Return a value to indicate this is an enemy damage trap
    }

    void activate() override {
    // Loop through all enemies on the trap's tile and reduce their health points
        for (/each enemy on the tile/) {
            enemy->takeDamage(damageAmount);
        }
    }

};

class BossDamage : public Trap {
public:
    int display() override {
        return 2; // Return a value to indicate this is a tank and boss damage trap
    }

    void activate() override {
    // Check if any tank or boss enemy is on the trap's tile and apply damage or special effect
        if (t/here are tank or boss enemies on the tile/) {
            // Apply higher damage or a special effect to tank or boss enemies
            for (/each tank or boss enemy on the tile/) {
                enemy->takeDamage(higherDamageAmount);
                // Or apply a special effect like slowing down the enemy or reducing their armor temporarily
            }
        }
    }

};

// class antiboss : public tower {
// public:
// int catk=0;//only attacks boss
//     void display() {
//         cout << "B";
//     }

//     void attack(level &l) {
        
//         int j = 0;
        
//     }
// };

// class antiarmor : public tower {
// public:
//     void display() {
//         cout << "a";
//     }

//     // damage increased by (insert  number here)% when hitting an armoured unit.
// };

// class ammunition_depot : public tower {
// public:
//     void display() {
//         cout << "d";
//     }
//     // inc tower atk dmg
// };

class Enemy {
public:
    
    friend class Map;
    int health;
    int money;
    int x,y;

    void display() {
        cout << "e";
    }
    
    
    void setCoordinate(int a,int b,Level & i){// during main game call for health of this enemyto subtract from health
        x=a;
        y=b;
        if (a>=10 || b>=10)
        {
            
    
        
        }
        else{
    
        }

        
    
    }
    int getcoordinate(){
 return x ,y;//x,y= getcoordinates();

    }
    virtual bool losehealth(int damage,Level& l)=0;
    ~Enemy() {
        cout << "enemy destroyed"<<endl;
    }

};

class Boss : public Enemy {
public:
    // Boss(int h, int d, int s, int a) : health(h), damage(d), speed(s), armor(a) {}
    void display() {
        cout << "b";
    }
    bool losehealth(int damage,Level& l){// use this function in the attack.
        
            health-=damage;
            return false;
        if(health<=0){

            l.money+=money;
            l.m-> r[x][y] ->e = NULL;
            
        return true;

        }


}
    void attack(){
        
    }

~Boss(){


}

    
    // traps do not work on these guys and they just disintegrate.
    // can atk
};

// class Tank : public Enemy {
// public:
//     void display() {
//         cout << "T";
//     }
//     bool losehealth(int damage,Level& l){// use this function in the attack.
//         
//             health-=damage;
//             if(health<=0){

//                l.money+=money;
//                l.m-> r[x][y] ->e = NULL;
//             return true;

//             }
//             return false;
//         }
//     // tanks are immune to most traps .
// };

class Armoured : public Enemy
{
private:
    int armour;// level of armur
public:
    bool losehealth  (int damage,Level& l){// use this function in the attack.
        
            health-= (damage/(3.14* armour)+ (0.3*pow(damage,log(3))+10));
        
        
        if(health<=0){

            l.money+=money;
            l.m-> r[x][y] ->e = nullptr;
            
        return true;

        }
return false;

    }
     // armoured trooop,takes less damage frim all towers except 1.
};

//  class dushman: public enemy{
//     public:
//         bool losehealth(int damage,level& l){// use this function in the attack.
//             
//                 health-=damage;
//                 if(health<=0){

//                    l.money+=money;
//                    l.m-> r[x][y] ->e = NULL;
//                 }
//                 return true;

//             }

// };

int main() {
    Game g;
    g.playgame();

    return 0;
}