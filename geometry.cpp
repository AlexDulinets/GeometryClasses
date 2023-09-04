/***************************************************************
* ���� : geometry.cpp *
* �������� : ������, ���������� ���������� ������� ������� *
* ��� ������� �������������� ����� *
***************************************************************/

#include <math.h>
#include "geometry.h"
#include <fstream>

#define LIMIT_DELTA 0.0000000000000 //0.8 ����� ��� ������� ��������

//*******������� 2***************************************************************************************
//----------------------------------------------------���������
using namespace std;


// ������� �� �������� ������������ ��������� �����
double InterDoubleTest() {
    //long double Res=0;t
    int n, count;
    bool fl_Negative = 0;
    bool fl_Point = 0;

    char* A = new char;
    cin >> A;

    n = strlen(A);//���. ��������

    //�������� �� �����. �������� (INT)
    if (
        (n > 11 && A[0] == '-')
        ||
        (n > 10 && A[0] != '-')
        ) {
        cout << "������� ������ �����!\n";
        exit(1);
    }

    count = 0;//���. ���������� ��������
    int i = 0;

    //�������� �� +-
    if (A[0] == '-') {
        bool fl_Negative = 1;
        i = 1;
        count++;

        // ���-�������� �� ����� (-.000)
        if (A[1] == '.') { cout << "\n---�� ��������� \" -. \"-- - \n"; exit(4); }
    }
    //�������� �� ����� � ������ (-.000)
    if (A[0] == '.') { cout << "\n---�� ��������� \" .000 \"-- - \n"; exit(4); }

    //������ �� ������� ��������
    for (i; i < n; ++i) {

        //��������� �������� �� �����
        if (A[i] == '.' && fl_Point == 0) {
            fl_Point = 1;
            i += 1;
            count++;
        }

        //�������� �� �����(������) 0-9
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

                cout << "\n---������ ������(-�)---\n"; exit(4);
            }
        }
        count++;
    }
    setlocale(LC_ALL, "eng");

    //!!! !!! !!! atof �������� �� ��������� ���� ������� �������, � �� ����. !!!

    return atof(A);
    setlocale(LC_ALL, "rus");

}

//
wchar_t InterNaturTest() {
    double Fn = InterDoubleTest();

    if (Fn != floor(Fn)) { cout << "NOO !Z"; exit(2); } //�������� ����� 3.215 NOT
    if (Fn <= 0) { cout << "NOO !N"; exit(1); }         //+-
    return Fn;
}





//����� � ����� �����
std::ostream& operator << (std::ostream& stream, Point& point) {
    stream << "x:" << point.getX() << " y:" << point.getY() << "\n";
    return stream;
}

// == �����
bool operator == (Point A, Point B) {
    if (A.getX() == B.getX() && A.getY() == B.getY())
        return 1;
    else
        return 0;
}

//����� � ����� �����������
std::ostream& operator << (std::ostream& stream, Circle& circle) {
    stream << "����� ���������� ("
        << circle.getCenter().getX() << ',' << circle.getCenter().getY()
        << "), ������ = " << circle.getR() << endl;
    return stream;
}

//����� � ����� �������
std::ostream& operator << (std::ostream& stream, Vector& vector) {
    stream << "������ (" << vector.getX() << "," << vector.getY() << ")\n";
    return stream;
}





// -------------------------------------------------------------
// ������ ������ "�����"
// -------------------------------------------------------------

//����������� �� ���������
Point::Point() {
    this->x = 0;
    this->y = 0;
}

// �����������: ����� �������� ������ ������������
Point::Point(long double X, long double Y) {
    x = X; y = Y;
}

// ��������� ���������� �
long double Point::getX() {
    return x;
}

// ��������� ���������� �
long double Point::getY() {
    return y;
}

// -------------------------------------------------------------
// ������ ������ "����������"
// -------------------------------------------------------------

// �����������: ���������� �������� ������� � ��������
Circle::Circle(Point Center, double R) :center(Center) {
    r = R;
}

// ��������� ����� ����������
Point Circle::getCenter() {
    return center;
}

// ��������� ������ ����������
double Circle::getR() {
    return r;
}

// -------------------------------------------------------------
// ������ ������ "������"
// -------------------------------------------------------------

// �����������: ������ �������� ������ ��������������
Line::Line(double a, double b, double c) {
    A = a; B = b; C = c;
}

// �����������: ������, ������� �������� ����� ��� �������� �����
Line::Line(Point p1, Point p2) {
    A = p2.getY() - p1.getY();
    B = p1.getX() - p2.getX();
    C = -A * p1.getX() - B * p1.getY();
}

// ����� ����� ����������� � �������� ������
Point Line::getIntersect(Line line) {
    double d = A * line.B - B * line.A,
        d1 = -(C * line.B - B * line.C),
        d2 = -(A * line.C - C * line.A);
    return Point(d1 / d, d2 / d);
}

// ��������� ���������������� ������, ���������� ����� �������� �����
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
// ������ ������ "�������"
// -------------------------------------------------------------

// �����������: ������� �������� ����� �������
Segment::Segment(Point p1, Point p2) {
    x1 = p1.getX(); y1 = p1.getY();
    x2 = p2.getX(); y2 = p2.getY();
}

// ����� �������� �������
Point Segment::getMidpoint() {
    return Point((x1 + x2) / 2, (y1 + y2) / 2);
}

// ����� ����� �������
long double Segment::getLength() {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// -------------------------------------------------------------
// ������ ������ "�����������"
// -------------------------------------------------------------

// ����������� ������
Triangle::Triangle(Point A, Point B, Point C) {
    this->A = A;
    this->B = B;
    this->C = C;   

};

//�������
long double Triangle::getSqare() {
    long double p;//������������

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
// ������ ������ "������"
// -------------------------------------------------------------

//�����������: ������ �� 2-�� �����
Vector::Vector(Point vp1, Point vp2) {
    this->vx = vp2.getX() - vp1.getX();
    this->vy = vp2.getY() - vp1.getY();
}
//�����������: ����� �����.
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

//��������
Vector Vector::addVec(Vector vec2) {
    double x = vx + vec2.getX();
    double y = vy + vec2.getY();
    Vector VEC(x, y);
    return VEC;
}

//���������
Vector Vector::decVec(Vector vec2) {
    double x = vx - vec2.getX();
    double y = vy - vec2.getY();
    Vector VEC(x, y);
    return VEC;
}

/*
//��������� ������������ ??? 2D?
Vector Vector::VecVec(Vector vec2){
    double x = vx - vec2.getX();
    double y = vy - vec2.getY();
    Vector VEC(x,y);
    return VEC;
} */
//��������� ������������
double Vector::sclVec(Vector vec2) {
    double S = vx * vec2.getX() + vy * vec2.getY();
    return S;
}

// ============== ����� ������ =================================