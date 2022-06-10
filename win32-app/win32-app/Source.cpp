#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "myClass.h"

using namespace std;

// Hình tròn, hình ellipse, hình bán nguyệt, hình đa giác(lồi), hình chữ nhật, hình vuông, hình tam giác

//Solve the system of equations

Line::Line(Point a, Point b)
{
	s = a;		e = b;
}

void Line::Input(istream& inDevice)
{
	cout << "ax + by + c = 0" << endl;
	cout << "Enter a:";
	cin >> a;
	cout << "Enter b:";
	cin >> b;
	cout << "Enter c:";
	cin >> c;
	cout << "Input start point: " << endl;
	s.Input(cin);
	cout << "Input end point: " << endl;
	e.Input(cin);
}



bool Line::isCutByLine(Point p) {
	//return (pow(p.getX() - Center.getX(), 2) / Ra) + (pow(p.getY() - Center.getY(), 2) / Rb) <= 1;
	return true;
}

// Circle

Circle::Circle(Point a, float b = 0)
{
	O = a;
	R = b;
}

void Circle::Input(istream& inDevice)
{
	cout << "Enter the radius of the circle: " << endl;
	inDevice >> R;
	cout << "Enter center coordinates O: " << endl;
	O.Input(cin);
}

bool Intersect(int a, int b, int c, Point p, int radius) {
	int dist = (abs(a * p.getX() + b * p.getY() + c)) / sqrt(a * a + b * b);
	if (radius >= dist)
		return true;
	else return false;
}

bool Circle::isCutByLine(Line L) {
	if (Intersect(L.a, L.b, L.c, O, R)) {
		return true;
	}
	else return false;
}


// Elipse
Elipse::Elipse(float a = 0, float b = 0)
{
	Ra = a;		Rb = b;
}

void Elipse::Input(istream& inDevice)
{
	cout << "Input width: " << endl;
	inDevice >> Ra;
	cout << "Input height: " << endl;
	inDevice >> Rb;
	cout << "Enter center coordinates O: " << endl;
	Center.Input(cin);
}

bool Elipse::isCutByLine(Line L) {
	if (Intersect(L.a, L.b, L.c, Center, Rb / 2)) {
		return true;
	}
	else return false;

	//return (pow(p.getX() - Center.getX(), 2) / Ra) + (pow(p.getY() - Center.getY(), 2) / Rb) <= 1;
}

// Semi-Circle
SemiCircle::SemiCircle(Point a, Point b, float c = 0)
{
	start = a;
	end = b;
}

void SemiCircle::Input(istream& inDevice)
{
	cout << "Enter start point: " << endl;
	start.Input(cin);
	cout << "Enter end point: " << endl;
	end.Input(cin);
	cout << "Enter top center point: " << endl;
	topcenter.Input(cin);
}

bool SemiCircle::isCutByLine(Line L) {
	Point O;
	O.SetPoint((start.getX() + end.getX()) / 2, (start.getY() + end.getY()) / 2);
	if (doIntersect(L.a, L.b, O, topcenter) || doIntersect(L.a, L.b, start, end)) {
		return true;
	}
}

// Polygon
void Polygon::Input(istream& inDevice)
{
	cout << "Enter the number of vertices of the polygon: " << endl;
	inDevice >> n;
	for (int i = 0; i < n; i++) {
		cout << "Enter vertice number " << i + 1 << ": " << endl;
		p[i].Input(cin);
	}

}

bool Polygon::isCutByLine(Line L) {
	if (doIntersect(L.a, L.b, p[n - 1], p[0])) {
		return true;
	}
	for (int i = 0; i < n; i++) {
		if (doIntersect(L.a, L.b, p[i], p[i + 1])) {
			return true;
			break;
		}
	}
	return false;
}

// Rectangle
void Rectangle::setRectangle(Point rUpper, Point lLower) {
	RUpper = rUpper;
	LLower = lLower;
	width = abs(RUpper.getX() - LLower.getX());
	height = abs(RUpper.getY() - LLower.getY());
}

Rectangle::Rectangle(Point rUpper, Point lLower)
{
	setRectangle(rUpper, lLower);
}


void Rectangle::Input(istream& inDevice)
{
	cout << "Enter the coordinates of the right upper point: " << endl;
	RUpper.Input(cin);
	cout << "Enter the coordinates of the left lower point: " << endl;
	LLower.Input(cin);
}

bool Rectangle::isCutByLine(Line L) {
	Point RLower = (RUpper.getX(), LLower.getY());
	Point LUpper = (LLower.getX(), RUpper.getY());
	if (doIntersect(L.a, L.b, LUpper, RUpper) || doIntersect(L.a, L.b, RUpper, RLower) || doIntersect(L.a, L.b, LLower, RLower) || doIntersect(L.a, L.b, LUpper, LLower)) {
		return true;
	}
	else return false;
}

// Square
void Square::setSquare(Point rUpper, Point lLower) {
	RUpper = rUpper;
	LLower = lLower;
	width = abs(RUpper.getX() - LLower.getX());
}

Square::Square(Point rUpper, Point lLower)
{
	setSquare(rUpper, lLower);
}

void Square::Input(istream& inDevice)
{
	do {
		cout << "The distance between the right upper point and the left lower point must be equal to the length of the side of the square times the root of 2." << endl;
		cout << "Enter the coordinates of the right upper point: " << endl;
		RUpper.Input(cin);
		cout << "Enter the coordinates of the left lower point: " << endl;
		LLower.Input(cin);
	} while (sqrt(pow((RUpper.getX() - LLower.getX()), 2) + pow(RUpper.getY() - LLower.getY(), 2)) != sqrt(2) * (RUpper.getX() - LLower.getX()));
}

bool Square::isCutByLine(Line L) {
	Point RLower = (RUpper.getX(), LLower.getY());
	Point LUpper = (LLower.getX(), RUpper.getY());
	if (doIntersect(L.a, L.b, LUpper, RUpper) || doIntersect(L.a, L.b, RUpper, RLower) || doIntersect(L.a, L.b, LLower, RLower) || doIntersect(L.a, L.b, LUpper, LLower)) {
		return true;
	}
	else return false;
}

// Triangle
Triangle::Triangle(Point p1, Point p2, Point p3)
{
	setTriangle(p1, p2, p3);
}

void Triangle::setTriangle(Point p1, Point p2, Point p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	x1 = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
	x2 = sqrt(pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2));
	x3 = sqrt(pow(p2.getX() - p3.getX(), 2) + pow(p2.getY() - p3.getY(), 2));
}

void Triangle::Input(istream& inDevice)
{
	float x, y;
	cout << "Enter the coordinates of the first vertice: " << endl;

	cin >> x >> y;
	p1.SetPoint(x, y);
	cout << "Enter the coordinates of the second vertice: " << endl;

	cin >> x >> y;
	p2.SetPoint(x, y);
	cout << "Enter the coordinates of the third vertice: " << endl;

	cin >> x >> y;
	p3.SetPoint(x, y);
	Triangle(p1, p2, p3);
}

bool Triangle::isCutByLine(Line L) {
	if (doIntersect(L.a, L.b, p1, p2) || doIntersect(L.a, L.b, p2, p3) || doIntersect(L.a, L.b, p3, p1)) {
		return true;
	}
	else return false;
}

//Check if the line intersects the line

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r)
{
	if (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) && q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
	{
		return true;
	}

	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r)
{
	// for details of below formula. 
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0; // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}



//void main()
//{
//	Figure* f = new Figure[100];
//	vector<Circle> C;
//	vector<Elipse> E;
//	vector<SemiCircle> S;
//	vector<Polygon> P;
//	vector<Rectangle> R;
//	vector<Square> Q;
//	vector<Triangle> T;
//
//	int choose = -1;
//
//	Circle ctempt;
//	Elipse etempt;
//	SemiCircle stempt;
//	Polygon ptempt;
//	Rectangle rtempt;
//	Square qtempt;
//	Triangle ttempt;
//	Line L;
//
//	Point p1(0, 0);
//	Point q1(-1, 1);
//	Point p2(1, 0);
//	Point q2(0, 1);
//
//	if (doIntersect(p1, q1, p2, q2)) {
//		cout << "Co\n";
//	}
//	else cout << "Khong\n";
//
//
//	// Hình tròn, hình ellipse, hình bán nguyệt, hình đa giác(lồi), hình chữ nhật, hình vuông, hình tam giác
//	cout << "Select option create figure below: " << endl;
//	cout << "1. Circle " << endl;
//	cout << "2. Elipse " << endl;
//	cout << "3. Semi-Circle " << endl;
//	cout << "4. Polygon " << endl;
//	cout << "5. Rectangle " << endl;
//	cout << "6. Square " << endl;
//	cout << "7. Triangle " << endl;
//	cout << "0. Stop " << endl;
//	while (choose != 0) {
//		cout << "Your select -> ";
//		cin >> choose;
//		switch (choose) {
//		//Circle
//		case 1: {
//			ctempt.Input(cin);
//			C.push_back(ctempt);
//		}
//			  break;
//		//Elipse
//		case 2: {
//			etempt.Input(cin);
//			E.push_back(etempt);
//		}
//			  break;
//		//Semi-Circle
//		case 3: {
//			stempt.Input(cin);
//			S.push_back(stempt);
//		}
//			  break;
//		//Polygon
//		case 4: {
//			ptempt.Input(cin);
//			P.push_back(ptempt);
//		}
//			  break;
//		//Rectangle
//		case 5: {
//			rtempt.Input(cin);
//			R.push_back(rtempt);
//		}
//			  break;
//		//Square
//		case 6: {
//			qtempt.Input(cin);
//			Q.push_back(qtempt);
//		}
//			  break;
//		//Triangle
//		case 7: {
//			ttempt.Input(cin);
//			T.push_back(ttempt);
//		}
//			  break;
//
//		}
//	}
//
//	cout << "Input your start point and end point of your line: ";
//	L.Input(cin);
//
//
//	/*cout << "Input your check point coordinates (x, y): ";
//	Point check;
//	check.Input(cin);
//	for (auto& n : E)
//		if (n.isCutByLine(check))
//			cout << "Point is in side Elipse(" << n.Center.getX() << "," << n.Center.getY() << ")" << endl;
//	for (auto& n : R)
//		if (n.isCutByLine(check))
//			cout << "Point is in side Rectangle Left Lower(" << n.LLower.getX() << "," << n.LLower.getY() << "), Right Upper (" << n.RUpper.getX() << "," << n.RUpper.getY() << endl;
//	for (auto& n : T)
//		if (n.isCutByLine(check))
//			cout << "Point is in side Triangle p1(" << n.p1.getX() << "," << n.p1.getY() << "), p2(" << n.p2.getX() << "," << n.p2.getY() << "), p3(" << n.p3.getX() << "," << n.p3.getY() << ") " << endl;*/
//}