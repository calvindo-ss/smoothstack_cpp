#include <iostream>
#include <math.h>
#include "shapes.h"

#define PI 3.14

// ################################ Shape Class ################################
Shape::Shape(){}

Shape::Shape(double x, double y): x(x), y(y){}

std::string Shape::get_call(){
    return call;
}

// ################################ Ellipse Class ################################
Ellipse:: Ellipse(): Shape(){}

Ellipse::Ellipse(double x, double y): Shape(x, y){}

//copy constructor
Ellipse::Ellipse(const Ellipse& other): Shape(other){
    x = other.x;
    y = other.y;
}

// move constructor
Ellipse::Ellipse(Ellipse&& other): Shape(other){
    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;
}

// copy assignment operator
Ellipse& Ellipse::operator = (const Ellipse& other){
    x = other.x;
    y = other.y;

    return *this;
}

// move assignment operator
Ellipse& Ellipse::operator = (Ellipse&& other){
    if(this == &other){
        return *this;
    }

    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;

    return *this;
}

double Ellipse::area(){
    call = "Ellipse";
    return PI * x * y;
}

double Ellipse::major_diameter(){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

double Ellipse::minor_diameter(){
    if(x < y){
        return x;
    }
    else{
        return y;
    }
}

double Ellipse::circumference(){
    return 2 * PI * sqrt((std::pow(major_diameter(), 2) + std::pow(minor_diameter(), 2))/2);
}
// ################################ Circle Class ################################
Circle::Circle(double x): Ellipse(x, 5){};

//copy constructor
Circle::Circle(const Circle& other): Ellipse(other){
    x = other.x;
    y = other.y;
}

// move constructor
Circle::Circle(Circle&& other): Ellipse(other){
    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;
}

// copy assignment operator
Circle& Circle::operator = (const Circle& other){
    x = other.x;
    y = other.y;

    return *this;
}

// move assignment operator
Circle& Circle::operator = (Circle&& other){
    if(this == &other){
        return *this;
    }
    
    x = other.x;
    y = other.y;

    other.x = 0;
    other.y = 0;

    return *this;
}

double Circle::area(){
    call = "Circle";
    double radius = x/2;
    return PI * pow(radius, 2);
}

double Circle::diameter(){
    return x;
}

double Circle::circumference(){
    return PI * x;
}

// ################################ Point Class ################################
Point::Point(double x, double y): x(x), y(y){};

double Point::distance(Point a){
    double dx = x - a.x;
    double dy = y - a.y;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

// ################################ Polygon Class ################################
Polygon::Polygon(std::vector<Point> vec_p): Shape(vec_p[3].x - vec_p[0].x, vec_p[1].y - vec_p[0].y), vec_p(vec_p){}

// ################################ Triangle Class ################################
Triangle::Triangle(std::vector<Point>& vp): Polygon(vp), a(vp[0]), b(vp[1]), c(vp[2]){}

double Triangle::area(){
    call = "Triangle";
    double ab = a.distance(b);
    double bc = b.distance(c);
    double ca = c.distance(a);

    double s1 = (ab + bc + ca) / 2;

    return sqrt(s1*(s1-ab)*(s1-bc)*(s1-ca));
}

double Triangle::perimeter(){
    return a.distance(b) + b.distance(c) + c.distance(a);
}

// ################################ Quadrilateral Class ################################
Quadrilateral::Quadrilateral(std::vector<Point>& vp): Polygon(vp), a(vp[0]), b(vp[1]), c(vp[2]), d(vp[3]){}

double Quadrilateral::area(){
    call = "Quadrilateral";
    double ab = this->a.distance(b);
    double bc = this->b.distance(c);
    double ca = this->c.distance(a);

    double ac = this->a.distance(c);
    double cd = this->c.distance(d);
    double da = this->d.distance(a);

    double s1 = (ab + bc + ca) / 2;
    double s2 = (ac + cd + da) / 2;

    double a1 = sqrt(s1*(s1-ab)*(s1-bc)*(s1-ca));
    double a2 = sqrt(s2*(s2-ac)*(s2-cd)*(s2-da));

    return a1 + a2;
}

double Quadrilateral::perimeter(){
    return a.distance(b) + b.distance(c) + c.distance(d) + d.distance(a);
}

// ################################ Trapezoid Class ################################
Trapezoid::Trapezoid(std::vector<Point>& vp): Quadrilateral(vp){}

double Trapezoid::area(){
    call = "Trapezoid";
    double a = this->b.distance(c);
    double b = this->a.distance(d);

    double h = this->b.y - this->a.y;

    return ((a+b)/2)*h;

}

// ################################ Parallelogram Class ################################
Parallelogram::Parallelogram(std::vector<Point>& vp): Quadrilateral(vp){}

double Parallelogram::area(){
    call = "Parallelogram";
    return x * y;
}
