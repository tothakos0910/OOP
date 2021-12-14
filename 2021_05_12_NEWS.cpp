#include <string>
#include <vector>
#include <iostream>

class News;
class NewsSource; 

class NewsConsumer{
    std::string name;
    std::vector<News*> inbox;
 public:
    NewsConsumer(std::string name) : name(name) {}
    void registerToSource(NewsSource* ns);
    void recive(News* news){inbox.push_back(news);}

    void printInbox();
    void printCultural();
    void printSports();
};

class NewsSource{
    std::string name;
    std::vector<NewsConsumer*> consumers;
 public:
    NewsSource(std::string name) : name(name) {}
    void publishNews(News* ns) {for(auto& cons : consumers) cons->recive(ns);}
    void registerConsumer(NewsConsumer* nc) {consumers.push_back(nc);}
};

class News{
 protected:
    std::string content;
    virtual ~News() = 0;
 public:
    News(std::string& content) : content(content) {}
    virtual std::string getText() {return content;}
};
News::~News() {};

class SportsNews : public News{
 public:
    SportsNews(std::string name) : News(name) {}

};

class CulturalNews : public News{
 public:
    CulturalNews(std::string name) : News(name) {}
};



void NewsConsumer::registerToSource(NewsSource* ns){ns->registerConsumer(this);}


void NewsConsumer::printInbox() {
    std::cout << "Inbox for consumer " << name <<":"<< std::endl;
    for(auto& news : inbox){
        std::cout << news->getText() << std::endl;
    }
    std::cout << "===" << std::endl;
}
void NewsConsumer::printCultural() {
    std::cout << "Cultural news for consumer " << name <<":"<< std::endl;
    for(auto& news : inbox){
        if(dynamic_cast<CulturalNews*>(news)) std::cout << news->getText() << std::endl;
    }
    std::cout << "===" << std::endl;
}
void NewsConsumer::printSports() {
    std::cout << "Sports news for consumer " << name <<":"<< std::endl;
    for(auto& news : inbox){
        if(dynamic_cast<SportsNews*>(news)) std::cout << news->getText() << std::endl;
    }
    std::cout << "===" << std::endl;
}


int main(int argc, char const *argv[])
{
    NewsSource ns1("News Source 1");
    NewsSource ns2("News Source 2");

    NewsConsumer dirk("Dirk");
    NewsConsumer blaise("Blaise");

    blaise.registerToSource(&ns1);
    dirk.registerToSource(&ns2);

    SportsNews nn1("sports for blaise");
    SportsNews nn2("sports for dirk");
    CulturalNews nn3("cultural news for blaise");
    CulturalNews nn4("cultural news for dirk");

    News* news1 = &nn1;
    news1 = &nn3;

    ns1.publishNews(&nn1); ns1.publishNews(news1);
    ns2.publishNews(&nn2); ns2.publishNews(&nn4);

    blaise.printInbox();
    blaise.printCultural();
    blaise.printSports();
    dirk.printInbox();
    dirk.printCultural();
    dirk.printSports();
    return 0;
}
