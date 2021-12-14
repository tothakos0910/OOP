#include <iostream>
#include <string>
#include <ostream>
using namespace std;


class SoccerPlayer {
    const std::string name; short speed;
    short stamina;
 public:
    SoccerPlayer(const std::string& name, short speed, short stamina); //TODO 
    virtual ~SoccerPlayer() = default;
    const std::string& getName() const { return name; }
    short getSpeed() const { return speed; }
    short getStamina() const { return stamina; }
    virtual short getOverall() const = 0;
};

SoccerPlayer::SoccerPlayer(const std::string& name, short speed, short stamina) : name(name), speed(speed), stamina(stamina){}

class FieldPlayer : public SoccerPlayer {
    short shooting, passing, tackling;
 public:
    FieldPlayer(const std::string& name, short speed, short stamina,short shooting, short passing, short tackling) 
    : SoccerPlayer(name, speed, stamina), shooting(shooting), passing(passing), tackling(tackling) {}
    virtual short getOverall() const override {return (getSpeed() + getStamina()+shooting+passing+tackling)/5;}
    short getShooting() const {return shooting;}
    short getPassing() const{return passing;}
    short getTackling() const {return tackling;}

    virtual ~FieldPlayer() = default;
};

class Goalkeeper :public SoccerPlayer {
    short reflex, agility;
 public:
    Goalkeeper(const std::string& name, short speed, short stamina, short reflex, short agility) 
    : SoccerPlayer(name, speed, stamina), reflex(reflex), agility(agility) {}
    virtual short getOverall() const override {return (getSpeed() + getStamina()+reflex+agility)/4;}

    short getReflexes() const {return reflex;}
    short getAgility() const {return agility;}

    virtual ~Goalkeeper() = default;
};

ostream& operator << (ostream& out, const SoccerPlayer& p) {
    return out << p.getName() << "(" << p.getOverall() << ")";
}


int main(int argc, char const *argv[])
{
 
const FieldPlayer* fp1 = new FieldPlayer("C. Ronaldo", 90, 85, 95, 91, 76); 
const FieldPlayer* fp2 = new FieldPlayer("L. Messi", 88, 93, 75, 88, 96); 
const Goalkeeper* gk = new Goalkeeper("M. Neuer", 89, 87, 94, 95);
const SoccerPlayer* p1 = fp1; 
const SoccerPlayer* p2 = fp2; 
const SoccerPlayer* p3 = gk;
cout << p1->getName() << endl; 
cout << p1->getSpeed() << endl; 
cout << p1->getStamina() << endl; 
cout << fp1->getShooting() << endl; 
cout << fp1->getPassing() << endl; 
cout << fp1->getTackling() << endl; 
cout << p1->getOverall() << endl; 
cout << endl;
cout << fp2->getName() << endl; 
cout << fp2->getSpeed() << endl; 
cout << fp2->getStamina() << endl; 
cout << fp2->getShooting() << endl; 
cout << fp2->getPassing() << endl; 
cout << fp2->getTackling() << endl; 
cout << fp2->getOverall() << endl; 
cout << endl;
cout << gk->getName() << endl; 
cout << gk->getSpeed() << endl; 
cout << gk->getStamina() << endl; 
cout << gk->getReflexes() << endl; 
cout << gk->getAgility() << endl; 
cout << gk->getOverall() << endl; 
cout << endl;
cout << *p1 << endl; 
cout << *p2 << endl; 
cout << *p3 << endl;
delete p1; delete fp2; delete gk;
}
