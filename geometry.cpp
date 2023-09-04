/***************************************************************
* Файл : geometry.cpp *
* Описание : модуль, содержащий реализацию методов классов *
* для решения геометрических задач *
***************************************************************/

#include <math.h>
#include "geometry.h"
#include <fstream>

#define LIMIT_DELTA 0.0000000000000 //0.8 точно для разницы площадей

//*******ЗАДАНИЕ 2***************************************************************************************
//----------------------------------------------------операторы
using namespace std;


// функция на проверку корректности вводимого числа
double InterDoubleTest() {
    //long double Res=0;t
    int n, count;
    bool fl_Negative = 0;
    bool fl_Point = 0;

    char* A = new char;
    cin >> A;

    n = strlen(A);//кол. символов

    //проверка на КОЛИЧ. символов (INT)
    if (
        (n > 11 && A[0] == '-')
        ||
        (n > 10 && A[0] != '-')
        ) {
        cout << "слишком больше число!\n";
        exit(1);
    }

    count = 0;//кол. допустимых символов
    int i = 0;

    //проверка на +-
    if (A[0] == '-') {
        bool fl_Negative = 1;
        i = 1;
        count++;

        // пре-проверка на точку (-.000)
        if (A[1] == '.') { cout << "\n---Не корректно \" -. \"-- - \n"; exit(4); }
    }
    //проверка на точку в начале (-.000)
    if (A[0] == '.') { cout << "\n---Не корректно \" .000 \"-- - \n"; exit(4); }

    //проход по массиву символов
    for (i; i < n; ++i) {

        //одинарная проверка на точку
        if (A[i] == '.' && fl_Point == 0) {
            fl_Point = 1;
            i += 1;
            count++;
        }

        //проверка на число(символ) 0-9
        for (int q = 0; q <= 9; ++q) {
            if (!(A[i] == '0' ||
                A[i] == '1' ||
                A[i] == '2' ||
                A[i] == '3' ||
                A[i] == '4' ||
                A[i] == '5' ||
                A[i] == '6' ||
                A[i] == '7' ||
                A[i] == '8' ||
                A[i] == '9')) {

                cout << "\n---лишний символ(-ы)---\n"; exit(4);
            }
        }
        count++;
    }
    setlocale(LC_ALL, "eng");

    //!!! !!! !!! atof работает не правильно если включен русский, а не англ. !!!

    return atof(A);
    setlocale(LC_ALL, "rus");

}

//
wchar_t InterNaturTest() {
    double Fn = InterDoubleTest();

    if (Fn != floor(Fn)) { cout << "NOO !Z"; exit(2); } //проверка ввода 3.215 NOT
    if (Fn <= 0) { cout << "NOO !N"; exit(1); }         //+-
    return Fn;
}





//вывод в поток ТОЧКИ
std::ostream& operator << (std::ostream& stream, Point& point) {
    stream << "x:" << point.getX() << " y:" << point.getY() << "\n";
    return stream;
}

// == ТОЧКИ
bool operator == (Point A, Point B) {
    if (A.getX() == B.getX() && A.getY() == B.getY())
        return 1;
    else
        return 0;
}

//вывод в поток ОКРУЖННОСТИ
std::ostream& operator << (std::ostream& stream, Circle& circle) {
    stream << "Центр окружности ("
        << circle.getCenter().getX() << ',' << circle.getCenter().getY()
        << "), радиус = " << circle.getR() << endl;
    return stream;
}

//вывод в поток ВЕКТОРА
std::ostream& operator << (std::ostream& stream, Vector& vector) {
    stream << "Вектор (" << vector.getX() << "," << vector.getY() << ")\n";
    return stream;
}





// -------------------------------------------------------------
// Методы класса "Точка"
// -------------------------------------------------------------

//конструктор по умолчанию
Point::Point() {
    this->x = 0;
    this->y = 0;
}

// конструктор: точка задается своими координатами
Point::Point(long double X, long double Y) {
    x = X; y = Y;
}

// прочитать координату Х
long double Point::getX() {
    return x;
}

// прочитать координату У
long double Point::getY() {
    return y;
}

// -------------------------------------------------------------
// Методы класса "Окружность"
// -------------------------------------------------------------

// конструктор: окружность задается центром и радиусом
Circle::Circle(Point Center, double R) :center(Center) {
    r = R;
}

// прочитать центр окружности
Point Circle::getCenter() {
    return center;
}

// прочитать радиус окружности
double Circle::getR() {
    return r;
}

// -------------------------------------------------------------
// Методы класса "Прямая"
// -------------------------------------------------------------

// конструктор: прямая задается своими коэффициентами
Line::Line(double a, double b, double c) {
    A = a; B = b; C = c;
}

// конструктор: прямая, которая проходит через две заданные точки
Line::Line(Point p1, Point p2) {
    A = p2.getY() - p1.getY();
    B = p1.getX() - p2.getX();
    C = -A * p1.getX() - B * p1.getY();
}

// найти точку пересечения с заданной прямой
Point Line::getIntersect(Line line) {
    double d = A * line.B - B * line.A,
        d1 = -(C * line.B - B * line.C),
        d2 = -(A * line.C - C * line.A);
    return Point(d1 / d, d2 / d);
}

// построить перпендикулярную прямую, проходящую через заданную точку
Line Line::getPerpendicular(Point p) {
    return Line(B, -A, -B * p.getX() + A * p.getY());
}


long double Line::getA() {
    return A;
}
long double Line::getB() {
    return B;
}
long double Line::getC() {
    return C;
}

// -------------------------------------------------------------
// Методы класса "Отрезок"
// -------------------------------------------------------------

// конструктор: отрезок задается двумя точками
Segment::Segment(Point p1, Point p2) {
    x1 = p1.getX(); y1 = p1.getY();
    x2 = p2.getX(); y2 = p2.getY();
}

// найти середину отрезка
Point Segment::getMidpoint() {
    return Point((x1 + x2) / 2, (y1 + y2) / 2);
}

// найти длину отрезка
long double Segment::getLength() {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// -------------------------------------------------------------
// Методы класса "Треугольник"
// -------------------------------------------------------------

// конструктор класса
Triangle::Triangle(Point A, Point B, Point C) {
    this->A = A;
    this->B = B;
    this->C = C;   

};

//площадь
long double Triangle::getSqare() {
    long double p;//полупереметр

    Segment a(A, B);
    Segment b(B, C);
    Segment c(C, A);


    p = (a.getLength() + b.getLength() + c.getLength()) / 2.0;

    return sqrt(
        p * (p - a.getLength()) * (p - b.getLength()) * (p - c.getLength())
    );
}

/*long double Triangle::getM() {


}*/


// -------------------------------------------------------------
// Методы класса "Вектор"
// -------------------------------------------------------------

//конструктор: вектор из 2-ух точек
Vector::Vector(Point vp1, Point vp2) {
    this->vx = vp2.getX() - vp1.getX();
    this->vy = vp2.getY() - vp1.getY();
}
//конструктор: сразу коорд.
Vector::Vector(double vx, double vy) {
    this->vx = vx;
    this->vy = vy;
}

double Vector::getX() {
    return vx;
}
double Vector::getY() {
    return vy;
}

void Vector::printVec() {
    cout << "(" << vx << "," << vy << ")\n";
}

//сложение
Vector Vector::addVec(Vector vec2) {
    double x = vx + vec2.getX();
    double y = vy + vec2.getY();
    Vector VEC(x, y);
    return VEC;
}

//вычитание
Vector Vector::decVec(Vector vec2) {
    double x = vx - vec2.getX();
    double y = vy - vec2.getY();
    Vector VEC(x, y);
    return VEC;
}

/*
//векторное произведение ??? 2D?
Vector Vector::VecVec(Vector vec2){
    double x = vx - vec2.getX();
    double y = vy - vec2.getY();
    Vector VEC(x,y);
    return VEC;
} */
//скалярное произведение
double Vector::sclVec(Vector vec2) {
    double S = vx * vec2.getX() + vy * vec2.getY();
    return S;
}

// ============== конец модуля =================================