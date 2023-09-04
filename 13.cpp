//* Дано : Координаты вершин треугольника. *
//* Найти : Описанную около этого треугольника окружность. *

#include <windows.h>
#include "geometry.h"

//#define DEBUG


using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
#ifndef DEBUG //ОТЛАДКА

	// ----- ввод исходных данных -----
	cout << "Введите точки треугольника и искомую\n";
	double x1, y1, x2, y2, x3, y3, xm, ym;
	cout << "Введите координаты первой точки ===> ";
	x1 = InterDoubleTest(); y1 = InterDoubleTest();
	setlocale(LC_ALL, "rus");
	cout << "Введите координаты второй точки ===> ";
	x2 = InterDoubleTest(); y2 = InterDoubleTest();
	setlocale(LC_ALL, "rus");
	cout << "Введите координаты третьей точки ==> ";
	x3 = InterDoubleTest(); y3 = InterDoubleTest();
	setlocale(LC_ALL, "rus");
	
	
	// ----- создание точек - вершин треугольника -----

	Point A = Point(x1, y1),
		B = Point(x2, y2),
		C = Point(x3, y3);
		
#else
	Point A = Point(1, 1),
		B = Point(5, 1),
		C = Point(3, 6);
		
#endif	

	cout << A << B << C; //+зд.2-ok

	


// ----- создание прямых, проходящих через стороны треугольника -----
	Line line1 = Line(A, B),
		line2 = Line(B, C),
		line3 = Line(C, A);


	//проверки 1- на 1 noTrig       2- на прямую

	if (A == B | B == C | C == A) {
		cout << "это не треугольник!";
		exit(1);
	}


	if (
		(line1.getA() * line2.getB() - line1.getB() * line2.getA() == 0) ||
		(line2.getA() * line3.getB() - line2.getB() * line3.getA() == 0) ||
		(line3.getA() * line1.getB() - line3.getB() * line1.getA() == 0)
		) {
		cout << "это прямая!";
		exit(1);
	}
//------------ТОЧКА ПЕРЕСЕЧЕНИЯ МЕДИАН----------------
	xm = (A.getX() + B.getX() + C.getX())/3;
	ym = (A.getY() + B.getY() + C.getY())/3;

	Point M = Point(xm, ym);

	cout <<"Координаты точки пересечения медиан: "<< M;
//------------ТОЧКА ПЕРЕСЕЧЕНИИЯ ВЫСОТ-------------

	Line perp1 = line3.getPerpendicular(B);
	Line perp2 = line1.getPerpendicular(C);
	Point o = perp1.getIntersect(perp2);
	cout << "Координаты точки пересечения высот: " << o;
	//Point O = midperpendicular1.getIntersect(midperpendicular2);
	/*Triangle trigS = Triangle(A, B, C);

	cout << fixed << setprecision(10) << "\n";

	if (trigS.testInterPoint(S) == 1) {
		cout << "\nточка внутри треугольника\n";
	}
	else {
		cout << "точка снаружи треугольника\n";
	}

	cout << setprecision(0) << "\n";*/




	// ----- создание отрезков - сторон треугольника -----
	Segment Otrezok1 = Segment(A, B),
		Otrezok2 = Segment(B, C);

	// ----- создание точек - середин сторон треугольника -----
	Point S1 = Otrezok1.getMidpoint(),
		S2 = Otrezok2.getMidpoint();



	// ----- ... и серединных перепндикуляров к этим сторонам ... -----
	Line	midperpendicular1 = line1.getPerpendicular(S1),
		midperpendicular2 = line2.getPerpendicular(S2);

	// ----- нахождение точки пересечения серединных перпендикуляров -----
	Point O = midperpendicular1.getIntersect(midperpendicular2);

	// ----- создание отрезка - радиуса -----
	Segment Radius = Segment(O, A);

	// ----- создание окружности с заданным центром и радиусом -----
	Circle circle = Circle(O, Radius.getLength());

	// ----- вывод результата -----+зд.2-ok
	cout << circle;


	cout << "ВЕКТОР:\n";

	Vector vector(A, B), vector2(B, C);
	cout << vector << vector2;

	Vector vector3 = vector.addVec(vector2);
	cout << "сложение V:"; vector3.printVec();
	vector3 = vector.decVec(vector2);
	cout << "вычитание V:"; vector3.printVec();
	cout << "скалярное произведение S:" << vector.sclVec(vector2);


	return 0;
}

// ================= конец программы ===========================