#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Lamp {
 protected:
    std::string name;
    bool status;
 public:
    Lamp(const std::string& name) : name(name), status(false) {}
    virtual ~Lamp() {}
    bool isOn() const {return status;}
    virtual void flip() {
        status = !status;
        std::cout << name << " turned " << (status ? "ON" : "OFF") << std::endl;
    }
};

class DimmableLamp : public Lamp {
    int brightness;
 public: 
    DimmableLamp(const std::string& name) : Lamp(name), brightness(100) {}
    int getBrightness() const {return status ? brightness : 0;}
    void setBrightness(int b){
        brightness = b;
        if (b > 100) brightness = 100;
        else if (b < 1) brightness = 1;
    }

    void flip() override {
        status = !status;
        std::cout << name << " turned " << (status ? "ON" : "OFF");
        if(status) std::cout << " at " << brightness << "% brightness ";
        std::cout << std::endl;
    }
};


class Room {
    std::vector<Lamp*> lamps;
 public:
    ~Room() {
        for(size_t i = 0; i < lamps.size(); i++) delete lamps[i];
    }
    void add(Lamp* l) {lamps.push_back(l);}
    int lampCount() const {return lamps.size();}

    Lamp& operator [](int i) {return *lamps[i];}

    void setAllLamps(bool switcher) {
        for (auto l : lamps){
            if(l->isOn() != switcher) l->flip();
        }
    }
    void adjustLights(int change) {
        for (auto l : lamps) {
            DimmableLamp* dl = dynamic_cast<DimmableLamp*>(l);
            if (dl && dl->isOn())
            {
                dl->setBrightness(dl->getBrightness() + change);
            }
            
        }
    }
};








int main(int argc, char const *argv[])
{
    Room r;
    cout << "Test 1: " << r.lampCount() << endl;
    r.add(new Lamp("Desk lamp"));
    cout << "Test 2: " << r.lampCount() << endl;
    cout << "Test 3: " << r[0].isOn() << endl;
    r[0].flip();
    cout << "Test 4: " << r[0].isOn() << endl;
    r.setAllLamps(false);
    r.setAllLamps(false);
    r.setAllLamps(true);
    r.setAllLamps(true);
    r.setAllLamps(false);

    r.add(new DimmableLamp("Ceiling lamp"));
    cout << "DimmableLamp is bought" <<endl;
    cout << "Test 5: " << r.lampCount() << endl;
    cout << "Test 6: " << r[1].isOn() << endl;
    r[1].flip();
    cout << "Test 7: " << r[1].isOn() << endl;
    r.setAllLamps(false);
    r[0].flip();
    r.setAllLamps(true);
    r[1].flip();
    r.setAllLamps(true);
    r.setAllLamps(true);
    r.setAllLamps(false);
    r.setAllLamps(false);
    return 0;
}
