#include <iostream>
#include <math.h>
#include <vector>
#include <ostream>


class Point2D {
    int x;
    int y;
 public: 
    Point2D(int x, int y) : x(x), y(y) {}
    const double distance(Point2D a) const {
        double distance = sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
        return distance;
    }
    int getX() const {return x;}
    int getY() const {return y;}
};

class Shape {
 protected:
    Shape() {}
 public:
    virtual ~Shape() {}
    virtual Shape& operator=(const Shape&) = delete;
    virtual double area() const = 0;

    virtual bool isLargerThan(Shape* s) {
        if (area() > s->area()) {
            return true;
        }else return false;
    }
    virtual std::string printType() = 0;
};


class Rectangle : public Shape {
    Point2D bf;
    Point2D ba;
    Point2D ja;
    Point2D jf;
public:
    Rectangle(Point2D bf, Point2D ba, Point2D ja, Point2D jf) : bf(bf), ba(ba), ja(ja), jf(jf) {}
    Rectangle(const Rectangle&) = delete;
    double area() const override {
        return bf.distance(ba)*ba.distance(ja);
    }
    std::string printType() override {return "Teglalap";}
};

class Circle : public Shape {
    Point2D kozep;
    int sugar;
 public: 
    Circle(Point2D kozep, int sugar) : kozep(kozep), sugar(sugar) {}
    Circle(const Circle&) = delete;
    double area() const override {
        return sugar*sugar*3.14;
    }
    std::string printType() override {return "Kor";}
};

int getSarkokSzama(Shape* s) {
  return (dynamic_cast<Rectangle*>(s) ? 4 : 0);
}



int main() {
    Shape* s1 = new Rectangle(Point2D(10,1), Point2D(10,-5), Point2D(12,-5), Point2D(12,1));
    Shape* s2 = new Circle(Point2D(6, 9), 2);
    std::cout << "5-os jegyert:" << std::endl;
    std::cout << "A " << s1->printType() << " alakzatnak " << getSarkokSzama(s1) << " sarka van." << std::endl;
    std::cout << "A " << s2->printType() << " alakzatnak viszont " << getSarkokSzama(s2) << " sarka van.";
    delete s1;
    delete s2;
    return 0;
}