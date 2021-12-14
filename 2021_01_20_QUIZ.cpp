#include <string>
#include <iostream>
#include <vector>
#include <ostream>

using namespace std;

class Question {
    string text;
    int points;
public:
    Question(const string& text, int points)
        : text(text)
        , points(points)
    {}
    virtual ~Question() = default;
    virtual string getText() const { return text + '\n'; }
    int getPoints() const { return points; }
    void setText(const string& newtext) { text = newtext; }
    void setPoints(int newpoints) { points = newpoints; }
    virtual bool checkAnswer() const = 0;
};

class IntegerQ : public Question {
    int answer;
 public:
    IntegerQ(const string& text, int answer, int points) : Question(text, points),  answer(answer){}
    int getAnswer() const {return answer;}
    void setAnswer(int numb) { answer = numb; }
    bool checkAnswer() const {
        int valasz;
        std::cin >> valasz;
        return valasz == answer ? true: false;
    }
};

class MCQ : public Question {
    vector<std::string> mcq_answer;
    int index;
 public:
    MCQ(const string& text, vector<std::string> answer, int index, int points) 
        : Question(text, points), mcq_answer(answer), index(index) {}

    int getAnswer() const {return index;}
    void setChoices(vector<std::string>& text, int indexx) {
        mcq_answer = text;
        index = indexx;
    }

    std::string getText() const  override {
        std::string output = Question::getText();
        for (size_t i = 0; i < mcq_answer.size(); i++){
            output += 'a' + i;
            output += ") " + mcq_answer[i] + "\n";
        }
        return output;
    }

    bool checkAnswer() const override {
        char bemenet;
        std::cin >> bemenet;
        return tolower(bemenet) == 'a' + index;
    }
};

ostream& operator<< (ostream& os, Question& q){
    return os << q.getText();
}

class Quiz{
    std::vector<Question*> quiz;
 public:
    void add(Question* q) {quiz.push_back(q);}
    int take() {
        int score = 0;
        for (auto& p : quiz) {
            std::cout << *p;
            IntegerQ* iq = dynamic_cast<IntegerQ*>(p);
            MCQ* mcq = dynamic_cast<MCQ*>(p);
            if (iq){
                std::cout << "Answer with a number:\n";
                if (iq->checkAnswer()) score += p->getPoints();
            } else if(mcq){
                std::cout << "Choose an answer:\n";
                if (mcq->checkAnswer()) score += p->getPoints();
            } 
        }
        return score;
    }
};


int main(int argc, char const *argv[])
{
    Quiz z;
    Question* q1 = new IntegerQ("How many bits are in a byte?", 8, 3);
    z.add(q1);
    cout << z.take() << " pts\n"; // 4 -> 0 pts
    q1->setText("How many bits are in an octet?");
    q1->setPoints(2);
    cout << z.take() << " pts\n"; // 8 -> 2 pts
    IntegerQ* iq2 = new IntegerQ("In which year was C++ standardized?", 98, 3);
    z.add(iq2);
    cout << z.take() << " pts\n"; // 8, 1998 -> 2 pts
    iq2->setAnswer(1998);
    iq2->setPoints(4);
    cout << z.take() << " pts\n"; // 8, 1998 -> 6 pts
    vector<string> answers = {"if", "else", "elif", "do"};
    MCQ* m1 = new MCQ("Which is not a keyword in C++?", answers, 2, 3);
    Question* q3 = m1;
    z.add(m1);
    cout << z.take() << " pts\n"; // 4, 98, A -> 0 pts
    Quiz z2;
    z2.add(q1);
    z2.add(iq2);
    q3->setText("Which one of these is not a keyword in C++?");
    answers = {"for", "foreach", "while"};
    cout << *m1;
    m1->setPoints(5);
    m1->setChoices(answers, 1);
    m1->setText("Which one is not a keyword in C++?");
    cout << *q3;
    cout << z.take() << " pts\n"; // 6, 1998, b -> 9 pts
    cout << z2.take() << " pts\n"; // 8, 1997 -> 2 pts
    z = z2;
    cout << z.take() << " pts\n"; // 8, 1998 -> 6 pts
    delete q1;
    delete iq2;
    delete q3;
    return 0;
}
