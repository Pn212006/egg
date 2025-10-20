#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


class bad_egg : public exception {
public:
    const char* what() const noexcept override {
        return "You tried to eat a rotten egg!";
    }
};


class Egg {
protected:
    string size;
    string flavor;

public:
    
    Egg(string s, string f) : size(s), flavor(f) {}

    
    string getSize() const { return size; }
    string getFlavor() const { return flavor; }


    virtual void eat_egg() const = 0;

    
    virtual ~Egg() {}
};


class BoiledEgg : public Egg {
public:
    BoiledEgg(string s) : Egg(s, "savory") {}

    void eat_egg() const override {
        cout << "You peel the " << size << " boiled egg. "
             << "It tastes " << flavor << " and satisfying!" << endl;
    }
};


class ChocolateEgg : public Egg {
public:
    ChocolateEgg(string s) : Egg(s, "sweet") {}

    void eat_egg() const override {
        cout << "You bite into the " << size << " chocolate egg. "
             << "Its " << flavor << " and delicious!" << endl;
    }
};


class RottenEgg : public Egg {
public:
    RottenEgg(string s) : Egg(s, "disgusting") {}

    void eat_egg() const override {
        throw bad_egg(); 
    }
};


class Carton {
private:
    Egg* eggs[12];
    int count;

public:
    Carton() : count(0) {}

    void addEgg(Egg* egg) {
        if (count < 12) {
            eggs[count++] = egg;
        } else {
            cout << "Carton is full!" << endl;
        }
    }

    void eatEgg(int index) {
        if (index < 0 || index >= count) {
            cout << "Invalid egg index." << endl;
            return;
        }

        try {
            eggs[index]->eat_egg();
        }
        catch (const bad_egg &e) {
            cout << " Warning: " << e.what() << endl;
        }
    }

    ~Carton() {
        for (int i = 0; i < count; ++i) {
            delete eggs[i];
        }
    }
};


int main() {
    Carton carton;

    carton.addEgg(new BoiledEgg("large"));
    carton.addEgg(new ChocolateEgg("small"));
    carton.addEgg(new RottenEgg("medium"));

    cout << "Eating egg #1:" << endl;
    carton.eatEgg(0);

    cout << "\nEating egg #2:" << endl;
    carton.eatEgg(1);

    cout << "\nEating egg #3:" << endl;
    carton.eatEgg(2);

    return 0;
}
