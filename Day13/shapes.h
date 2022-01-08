#include <iostream>
#include <vector>

class Shape{
    protected:
        double x;
        double y;
    public:
        Shape();
        Shape(double x, double y);

        virtual double area() = 0;
};

class Ellipse: public Shape{
    protected:
        const double PI = 3.14;
    public:
        Ellipse();
        Ellipse(double x, double y);

        Ellipse(const Ellipse& other);
        Ellipse(Ellipse&& other);

        Ellipse& operator = (const Ellipse& other);
        Ellipse& operator = (Ellipse&& other);

        double area();
        double major_diameter();
        double minor_diameter();
        double circumference();
};

class Circle: public Ellipse{
    public:
        Circle(double x);

        Circle(const Circle& other);
        Circle(Circle&& other);

        Circle& operator = (const Circle& other);
        Circle& operator = (Circle&& other);
    
        double area();
        double diameter();
        double circumference();
};

class Point{
    protected:
    public:
        double x, y;
        Point(double x, double y);
        double distance(Point a);
};

class Polygon: public Shape{
    protected:
        std::vector<Point> vec_p;
    public:
        Polygon(std::vector<Point> vec_p);
};

class Triangle: public Polygon{
    private:
        Point a, b, c;
    public:
        Triangle(std::vector<Point>& vp);
        
        double area();
        double perimeter();
};

class Quadrilateral: public Polygon{
    protected:
        Point a, b, c, d;
    public:
        Quadrilateral(std::vector<Point>& vp);
        
        double area();
        double perimeter();
};

class Trapezoid: public Quadrilateral{
    public:
        Trapezoid(std::vector<Point>& vp);
        
        double area();
};

class Parallelogram: public Quadrilateral{
    public:
        Parallelogram(std::vector<Point>& vp);

        double area();
};