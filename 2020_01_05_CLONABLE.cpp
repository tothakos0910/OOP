#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Clonable {
public:
    virtual ~Clonable() = default;
    virtual Clonable* clone() const = 0;
};

class ClonableString : public Clonable {
    std::string a;
 public:
    ClonableString(std::string a) : a(a) {}
    std::string getString() const {return a;}
    ClonableString* clone() const override {return new ClonableString(getString());}
};

class ClonableNumber :public Clonable {
    double b;
 public:
    ClonableNumber(double b) : b(b) {}
    double getNumber() const {return b;}
    ClonableNumber* clone() const override {return new ClonableNumber(getNumber());}
};


class CloneContainer{
    vector<Clonable*> klon;
 public:
    void push_back(const Clonable& in) {klon.push_back(in.clone());}
    int size() {return klon.size();}
    ~CloneContainer() {
        for (size_t i = 0; i < klon.size(); ++i)
            delete klon[i];
    }

    Clonable& operator[](int index) const {
    return *klon[index];
    }
};

int main() {
const ClonableString str1("szo");
const ClonableString str2("szoveg");
const ClonableString str3("word");

const ClonableNumber num1(4.2);
const ClonableNumber num2(-6.66);

CloneContainer clones;
clones.push_back(str1);
clones.push_back(num1);
clones.push_back(str2);
cout << clones.size() << " clones have been made\n";

Clonable& i1 = clones[0];
string testStr = dynamic_cast<ClonableString*>(&i1)->getString();
cout << "Item 1: " << testStr << endl;

ClonableNumber* i2 = dynamic_cast<ClonableNumber*>(&clones[1]);
cout << "Item 2: " << i2->getNumber() << endl;

ClonableString& i3 = dynamic_cast<ClonableString&>(clones[2]);
cout << "Item 3: " << i3.getString() << endl;

clones.push_back(str3);
clones.push_back(num2);
cout << clones.size() << " clones have been made\n";

ClonableString* i4 = dynamic_cast<ClonableString*>(&clones[3]);
cout << "Item 4: " << i4->getString() << endl;

ClonableNumber& i5 = dynamic_cast<ClonableNumber&>(clones[4]);
cout << "Item 5: " << i5.getNumber() << endl;
}