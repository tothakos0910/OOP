#include <iostream>
#include <string>
#include <vector>

class Document {
    double sizeInMbs;
public:
    Document(double sz) : sizeInMbs(sz) {}
    virtual ~Document() {}
    // keszitse el a getSize() metodust!
    double getSize() const { return sizeInMbs;}
    // keszitsen el egy printDetails() nevu pure virtual metodust!
    virtual void printDetails() = 0;
};

class TextDocument : public Document { // Ezt a sort javitsa, hogy TextDocument egyfajta Document legyen!
    const std::string title;
public:
    // Keszitse el TextDocument osztaly konstruktorat!
    TextDocument(const std::string title, double size) : Document(size) ,title(title) {}
    void printDetails() override {
        std::cout << "Text document entitled: " << title << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class AudioFile : public Document { // ezt a sort javitsa, hogy AudioFile egyfajta Document legyen!
    const std::string title;
    const std::string format;
public:
    // Keszitse el AudioFile osztaly konstruktorat!
    AudioFile(const std::string& title, const std::string format, double size)
        : Document(size), title(title), format(format) {}
    void printDetails() override {
        std::cout << format << " file entitled: " << title << " - with size of " << getSize() << "Mb" << std::endl;
    }
};

class DocumentFactory {
private:
    DocumentFactory() {}
public:
    // keszitse el a NewDocument metodust ugy, hogy a main leforduljon es mukodjon.
    // elso argumentum egy const string& tipusu argumentum, 
        //amely erteke ha "music" akkor AudioFile, ha "text" akkor TextDocument pointer
        // keszul a heap-en! (es ezt adja vissza a metodus).
    // masodik argumentum egy stringeket tartalmazo vektor!
    // harmadik argumentum egy double ertekeket tartalmazo vektor!
    // ha az elso argumentum nem "music" vagy "text", 
        //VAGY ha nincs eleg argumentum a vektorokban, akkor nullptr a visszateresi ertek
    static Document* NewDocument(const std::string& type, const std::vector<std::string>& data, const std::vector<double>& size) {
        if(type == "music" && data.size() == 2){
            AudioFile* af = new AudioFile(data[0], data[1], size[0]);
            return af;
        } else if(type == "text" && data.size() == 1) {
            TextDocument* txt = new TextDocument(data[0], size[0]);
            return txt;
        }
        return nullptr;
    }
    
};

int main(int argc, char const *argv[])
{
    Document* af1 = DocumentFactory::NewDocument("music", { "Back Chat", "mp3" }, {3.41}); // masodik es harmadik argumentum std::string illetve double vektorok!
    Document* af2 = DocumentFactory::NewDocument("music", { "All you need is love", "flac" }, { 5.89 });
    Document* tf1 = DocumentFactory::NewDocument("text", { "Nobel.txt" }, { 2.20 });
    Document* af3 = DocumentFactory::NewDocument("music", { "Some audio" }, { 5.00 }); // nincs eleg argumentum!
    if (af1) { af1->printDetails(); }
    if (af2) { af2->printDetails(); }
    if (tf1) { tf1->printDetails(); }
    if (af3) { af3->printDetails(); }
    else { std::cout << "af3: cannot create based on arguments" << std::endl; }

    delete af1;
    delete af2;
    delete tf1;
    return 0;
}
