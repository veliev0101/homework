#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Spell {
    string name;
    int power;
public:
    Spell(string n, int p) : name(n), power(p) {
        cout << "Created spell: " << name << endl;
    }
    
    ~Spell() {
        cout << "Destroyed spell: " << name << endl;
    }
    
    void show() const {
        cout << "Spell: " << name << ", sila: " << power << endl;
    }
};

class MagicSpell {
    char* text;
    int size;
    
public:
    MagicSpell(const char* t) : size(strlen(t)) {
        text = new char[size + 1];
        strcpy(text, t);
        cout << "MagicSpell constructor: " << text << endl;
    }
    
    ~MagicSpell() {
        cout << "MagicSpell destructor: " << (text ? text : "empty") << endl;
        delete[] text;
    }
    
    MagicSpell(const MagicSpell& other) : size(other.size) {
        text = new char[size + 1];
        strcpy(text, other.text);
        cout << "MagicSpell copy constructor: " << text << endl;
    }
    
    MagicSpell(MagicSpell&& other) noexcept : text(other.text), size(other.size) {
        other.text = nullptr;
        other.size = 0;
        cout << "MagicSpell move constructor" << endl;
    }
    
    MagicSpell& operator=(const MagicSpell& other) {
        if (this != &other) {
            delete[] text;
            size = other.size;
            text = new char[size + 1];
            strcpy(text, other.text);
            cout << "Copy assignment: " << text << endl;
        }
        return *this;
    }
    
    MagicSpell& operator=(MagicSpell&& other) noexcept {
        if (this != &other) {
            delete[] text;
            text = other.text;
            size = other.size;
            other.text = nullptr;
            other.size = 0;
            cout << "Move assignment" << endl;
        }
        return *this;
    }
    
    void print() const {
        if (text) cout << "Current spell: " << text << endl;
        else cout << "Spell is empty" << endl;
    }
};

class Wizard {
    unique_ptr<Spell> spell;
    
public:
    Wizard(string name, int power) {
        spell = make_unique<Spell>(name, power);
        cout << "Wizard got spell" << endl;
    }
    
    void showSpell() const {
        if (spell) spell->show();
        else cout << "No spell" << endl;
    }
    
    unique_ptr<Spell> giveSpell() {
        cout << "Wizard giving away spell" << endl;
        return move(spell);
    }
    
    void takeSpell(unique_ptr<Spell> newSpell) {
        cout << "Wizard taking spell" << endl;
        spell = move(newSpell);
    }
    
    bool hasSpell() const {
        return spell != nullptr;
    }
};

class Arena {
public:
    string name;
    Arena(string n) : name(n) {
        cout << "Arena created: " << name << endl;
    }
    
    ~Arena() {
        cout << "Arena destroyed: " << name << endl;
    }
    
    void battle() const {
        cout << "Battle on arena: " << name << endl;
    }
};

class Team {
    shared_ptr<Arena> arena;
    
public:
    Team(shared_ptr<Arena> a) : arena(a) {
        cout << "Team created, use_count: " << arena.use_count() << endl;
    }
    
    void fight() {
        if (arena) {
            arena->battle();
            cout << "Teams fighting, use_count: " << arena.use_count() << endl;
        }
    }
    
    shared_ptr<Arena> getArena() const {
        return arena;
    }
};

class Spectator {
    weak_ptr<Arena> arena;
    
public:
    void watch(shared_ptr<Arena> a) {
        arena = a;
        cout << "Spectator watching arena" << endl;
    }
    
    void observe() {
        if (auto a = arena.lock()) {
            cout << "Spectator sees: " << a->name << endl;
            cout << "Still alive, use_count: " << a.use_count() << endl;
        } else {
            cout << "Arena no longer exists" << endl;
        }
    }
};

void testRuleOfFive() {
    cout << "\n=== Test 1: Rule of Five ===" << endl;
    MagicSpell s1("Abrakadabra");
    MagicSpell s2 = s1;
    MagicSpell s3("Expelliarmus");
    s3 = s1;
    MagicSpell s4(move(s3));
    MagicSpell s5("Lumos");
    s5 = move(s4);
}

void testUniquePtr() {
    cout << "\n=== Test 2: unique_ptr ===" << endl;
    Wizard wiz1("Fireball", 100);
    Wizard wiz2("Icebolt", 80);
    
    wiz1.showSpell();
    wiz2.showSpell();
    
    auto spell = wiz1.giveSpell();
    wiz1.showSpell();
    wiz2.takeSpell(move(spell));
    
    wiz2.showSpell();
}

void testSharedWeakPtr() {
    cout << "\n=== Test 3: shared_ptr and weak_ptr ===" << endl;
    
    auto arena = make_shared<Arena>("Colosseum");
    cout << "Initial use_count: " << arena.use_count() << endl;
    
    Team team1(arena);
    Team team2(arena);
    cout << "After teams, use_count: " << arena.use_count() << endl;
    
    Spectator spectator;
    spectator.watch(arena);
    cout << "With spectator, use_count: " << arena.use_count() << endl;
    
    team1.fight();
    spectator.observe();
    
    team1 = Team(nullptr);
    team2 = Team(nullptr);
    cout << "After teams gone, use_count: " << arena.use_count() << endl;
    
    spectator.observe();
}

int main() {
    testRuleOfFive();
    testUniquePtr();
    testSharedWeakPtr();
    
    cout << "\nAll tests done" << endl;
    return 0;
}