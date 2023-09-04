/***************************************************************
* ���� : geometry.h *
* �������� : ������������ ���� � ��������� ������ ������� *
* ��� ������� �������������� ����� *
***************************************************************/
#include <iostream>
#include <string.h>
#include <iomanip>

#ifndef GEOMETRY_H
#define GEOMETRY_H



double InterDoubleTest();
wchar_t InterNaturTest();


// --------- ����� "�����" ---------------
class Point {
    long double x, y; // ���������� �����
public:
    Point();    //����������� �� ��������� +��.3 ...
    Point(long double X, long double Y); // ����������� ������
    long double getX(); // ������ ���� X
    long double getY(); // ������ ���� Y
};


// --------- ����� "����������" ----------
class Circle {
    Point center; // ����� ����������
    double r; // ������ ����������
public:
    Circle(Point Center, double R); // ����������� ������
    Point getCenter(); // ������ ���� Center
    double getR(); // ������ ���� R
};

// --------- ����� "������" --------------
class Line {
    long double A, B, C; // ������������ ������
public:
    Line(double a, double b, double c); // ����������� ������
    Line(Point p1, Point p2); // ��� ���� �����������
    Point getIntersect(Line line); // ����� ����� ����������� � �������� ������
    Line getPerpendicular(Point p); // ����� ���������������� ������,
// ���������� ����� �������� �����

    long double getA();
    long double getB();
    long double getC();
};

// --------- ����� "�������" -------------
class Segment {
    long double x1, y1, x2, y2; // ���������� ������ �������
public:
    Segment(Point p1, Point p2); // ����������� ������
    Point getMidpoint(); // ����� �������� �������
    long double getLength(); // ����� ����� �������
};


// --------- ����� "�����������" -------------
class Triangle {
    Point A;
    Point B;
    Point C;
public:
    Triangle(Point A, Point B, Point C); // ����������� ������
    long double getSqare(); //������� ������������ (�� ������)
    bool testInterPoint(Point S); //�������� �� ��������� ����� � �����������
    long double getM();

};


// --------- ����� "������" --------------
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

// =============== ����� ������������� ����� ==================

