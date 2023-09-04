/***************************************************************
* Файл : geometry.h *
* Описание : заголовочный файл с описанием набора классов *
* для решения геометрических задач *
***************************************************************/
#include <iostream>
#include <string.h>
#include <iomanip>

#ifndef GEOMETRY_H
#define GEOMETRY_H



double InterDoubleTest();
wchar_t InterNaturTest();


// --------- Класс "Точка" ---------------
class Point {
    long double x, y; // координаты точки
public:
    Point();    //конструктор по умолчанию +зд.3 ...
    Point(long double X, long double Y); // конструктор класса
    long double getX(); // чтение поля X
    long double getY(); // чтение поля Y
};


// --------- Класс "Окружность" ----------
class Circle {
    Point center; // центр окружности
    double r; // радиус окружности
public:
    Circle(Point Center, double R); // конструктор класса
    Point getCenter(); // чтение поля Center
    double getR(); // чтение поля R
};

// --------- Класс "Прямая" --------------
class Line {
    long double A, B, C; // коэффициенты прямой
public:
    Line(double a, double b, double c); // конструктор класса
    Line(Point p1, Point p2); // еще один конструктор
    Point getIntersect(Line line); // найти точку пересечения с заданной прямой
    Line getPerpendicular(Point p); // найти перпендикулярную прямую,
// проходящую через заданную точку

    long double getA();
    long double getB();
    long double getC();
};

// --------- Класс "Отрезок" -------------
class Segment {
    long double x1, y1, x2, y2; // координаты концов отрезка
public:
    Segment(Point p1, Point p2); // конструктор класса
    Point getMidpoint(); // найти середину отрезка
    long double getLength(); // найти длину отрезка
};


// --------- Класс "Треугольник" -------------
class Triangle {
    Point A;
    Point B;
    Point C;
public:
    Triangle(Point A, Point B, Point C); // конструктор класса
    long double getSqare(); //площадь треугольника (по Герону)
    bool testInterPoint(Point S); //проверка на вхождение точки в треугольник
    long double getM();

};


// --------- Класс "Вектор" --------------
class Vector {
    double vx;
    double vy;
public:
    Vector(Point vp1, Point vp2);
    Vector(double vx, double vy);

    double getX();
    double getY();

    void printVec();

    Vector addVec(Vector vec2);
    Vector decVec(Vector vec2);
    double sclVec(Vector vec2);

};


std::ostream& operator << (std::ostream& stream, Point& point);
std::ostream& operator << (std::ostream& stream, Circle& circle);
std::ostream& operator << (std::ostream& stream, Vector& vector);
bool operator == (Point A, Point B);

#endif

// =============== конец заголовочного файла ==================

