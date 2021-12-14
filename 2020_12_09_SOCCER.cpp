#include <string>
#include <vector>
#include <iostream>
#include <ostream>

using namespace std;


class SoccerPlayer {
    const std::string name;
    short speed;
    short stamina;
public:
    SoccerPlayer(const std::string& name, short speed, short stamina); //TODO
    virtual ~SoccerPlayer() = default;
    const std::string& getName() const { return name; }
    short getSpeed() const { return speed; }
    short getStamina() const { return stamina; }
    virtual short getOverall() const = 0;
};
SoccerPlayer::SoccerPlayer(const std::string& name, short speed, short stamina) : name(name), speed(speed), stamina(stamina) {}

class FieldPlayer: public SoccerPlayer {
    short shooting;
    short passing;
    short tackling;
 public:
    FieldPlayer(const std::string& name, short speed, short stamina, short shooting, short passing, short tackling)
        : SoccerPlayer(name, speed, stamina), shooting(shooting), passing(passing), tackling(tackling) {}

    short getOverall() const {return (getSpeed() + getStamina() + shooting + passing + tackling)/5;} 

    short getShooting() const {return shooting;}
    short getPassing() const {return passing;}
    short getTackling() const {return tackling;}
};

class Goalkeeper: public SoccerPlayer {
    short reflex;
    short agility;
 public:
    Goalkeeper(const std::string name, short speed, short stamina, short reflex, short agility)
     : SoccerPlayer(name, speed, stamina), reflex(reflex), agility(agility) {}
    short getOverall() const {return (getSpeed() + getStamina() + reflex + agility)/4;}

    short getReflexes() const {return reflex;}
    short getAgility() const {return agility;}
};

std::ostream& operator << (std::ostream& out, const SoccerPlayer& p) {
    return out << p.getName() << "(" << p.getOverall() << ")";
}

class SoccerTeam {
    vector<const SoccerPlayer*> players;
 public:
    bool add(const SoccerPlayer* p);
    int playerCount() const {return players.size();}
    ~SoccerTeam() {
        for(auto p : players) delete p;
    }

    const SoccerPlayer* operator [](int i){return players.at(i);}
};

bool SoccerTeam::add(const SoccerPlayer* p) {
    bool igaz = true;
    for(size_t i = 0; i < players.size(); i ++){
        if (players[i] == p) igaz = false;
        if (dynamic_cast<const Goalkeeper*>(players[i]) && dynamic_cast<const Goalkeeper*>(p)) igaz = false;
    }

    if (!igaz){
        return false;
    } else {
        players.push_back(p);
        return true;
    }
    

}







//--------------------------------------------------------------------------------------------------------------------//
int main(int argc, char const *argv[])
{
    SoccerTeam team;

if (team.add(new FieldPlayer("C. Ronaldo", 90, 85, 95, 91, 76)))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add C. Ronaldo.\n";

if (team.add(new FieldPlayer("L. Messi", 88, 93, 75, 88, 96)))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add L. Messi.\n";

if (team.add(new Goalkeeper("M. Neuer", 89, 87, 94, 95)))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add M. Neuer.\n";


if (team.add(team[0]))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add " << *team[0] << endl;

if (team.add(team[1]))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add " << *team[1] << endl;

if (team.add(team[2]))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add " << *team[2] << endl;

Goalkeeper* gk2 = new Goalkeeper("H. Lloris", 85, 86, 92, 94);
if (team.add(gk2))
    cout << "Player added: " << *team[team.playerCount()-1] << endl;
else
    cout << "Failed to add " << *gk2 << endl;
delete gk2;

for (size_t i = 0; i < (size_t)team.playerCount(); ++i) {
    cout << *team[i] << endl;
    cout << team[i]->getName() << endl;
    cout << team[i]->getSpeed() << endl;
    cout << team[i]->getStamina() << endl << endl;
}

}
