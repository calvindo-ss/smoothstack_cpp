#include <iostream>
#include <cassert>

#include "shapes.h"

int main(void){
    Ellipse e(6, 10);
    Ellipse e1(2, 4);
    std::cout << "Ellipse major diameter: " << e.major_diameter() << std::endl;
    std::cout << "Ellipse minor diameter: " << e.minor_diameter() << std::endl;
    std::cout << "Ellipse area: " << e.area() << std::endl;
    std::cout << "Ellipse circumference: " << e.circumference() << std::endl << std::endl;

    assert(e.get_call() == "Ellipse"); // checks that correct virtual method is called

    e = e1;
    std::cout << "Copying e = e1" << std::endl;
    std::cout << "Ellipse major diameter: " << e.major_diameter() << std::endl;
    std::cout << "Ellipse minor diameter: " << e.minor_diameter() << std::endl;
    std::cout << "Ellipse area: " << e.area() << std::endl;
    std::cout << "Ellipse circumference: " << e.circumference() << std::endl << std::endl;

    assert(e.get_call() == "Ellipse"); // checks that correct virtual method is called

    Circle c(6);
    std::cout << "Circle area: " << c.area() << std::endl;
    std::cout << "Circle diameter: "  << c.diameter() << std::endl;
    std::cout << "Circle circumference: "  << c.circumference() << std::endl << std::endl;

    assert(c.get_call() == "Circle"); // checks that correct virtual method is called

    e = Circle(10);
    std::cout << "Copying a Circle to an Ellipse" << std::endl;
    std::cout << "Ellipse major diameter: " << e.major_diameter() << std::endl;
    std::cout << "Ellipse minor diameter: " << e.minor_diameter() << std::endl;
    std::cout << "Ellipse area: " << e.area() << std::endl;
    std::cout << "Ellipse circumference: " << e.circumference() << std::endl << std::endl;

    assert(e.get_call() == "Ellipse"); // checks that correct virtual method is called

    Point ap(0,0), bp(1,1), cp(2,1), dp(3, -1);
    std::vector<Point> vec_t { ap, bp, cp};
    Triangle t(vec_t);
    std::cout << "Triangle area: "  << t.area() << std::endl;
    std::cout << "Triangle perimeter: "  << t.perimeter() << std::endl << std::endl;

    assert(t.get_call() == "Triangle"); // checks that correct virtual method is called

    std::vector<Point> vec_q { ap, bp, cp, dp };
    Quadrilateral q(vec_q);
    std::cout << "Quadrilateral area: "  << q.area() << std::endl;
    std::cout << "Quadrilateral perimeter: "  << q.perimeter() << std::endl << std::endl;

    assert(q.get_call() == "Quadrilateral"); // checks that correct virtual method is called

    Point ap1(6, 7), bp1(12, 28), cp1(34, 28), dp1(53, 7);
    std::vector<Point> vec_trap {ap1, bp1, cp1, dp1};
    Trapezoid trap(vec_trap);
    std::cout << "Trapezoid area: "  << trap.area() << std::endl;
    std::cout << "Trapezoid perimeter: "  << trap.perimeter() << std::endl << std::endl;

    assert(trap.get_call() == "Trapezoid"); // checks that correct virtual method is called

    Point ap2(0, 0), bp2(10, 10), cp2(20, 10), dp2(10, 0);
    std::vector<Point> vec_parallel {ap2, bp2, cp2, dp2};
    Parallelogram parallel(vec_parallel);
    std::cout << "Parallelogram area: "  << parallel.area() << std::endl;
    std::cout << "Parallelogram perimeter: "  << parallel.perimeter() << std::endl << std::endl;

    assert(parallel.get_call() == "Parallelogram"); // checks that correct virtual method is called
}