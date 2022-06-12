#include "my_project.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdio.h>

// !MYCLASS_CPP
#include "framework.h"
#include "resource.h"

using namespace std;

// Hình tròn, hình ellipse, hình bán nguyệt, hình đa giác(lồi), hình chữ nhật, hình vuông, hình tam giác

// Solve quadratic equations
int giaiPT(double a, double b, double c) {
	double delta = b * b - 4 * a * c;
	if (delta < 0) {
		return 0;
	}
	else return 1;
}

void myLine::Draw(HDC hdc)
{
	POINT pt[2] = { s.getX(), s.getY(), e.getX(), e.getY() };
	Polygon(hdc, pt, 2);
}


//Check if the line intersects the line

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(myPoint p, myPoint q, myPoint r)
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
int orientation(myPoint p, myPoint q, myPoint r)
{
	// for details of below formula. 
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0; // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2)
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

// Circle

void myCircle::Draw(HDC hdc)
{
	Ellipse(hdc, O.getX() - R, O.getY() - R, R + O.getX(), O.getY() + R);
}

bool myCircle::isCutByLine(myLine L) {
	double a = ( - L.s.getY() + L.e.getY()) / (L.s.getX() - L.e.getX());
	double b = - L.s.getY() - a * L.s.getX();
	float x = O.getX();
	float y = - O.getY();
	double a1 = a * a + 1;
	double a2 = 2 * a * b - 2 * x - 2 * a * y;
	double a3 = b * b + 2 * b * y + x * x + y * y - pow(R, 2);
	if (giaiPT(a1, a2, a3) == 0) {
		return false;
	}
	else return true;
}


// Ellipse

void myEllipse::Draw(HDC hdc)
{
	Ellipse(hdc, Center.getX() - Ra, Center.getY() - Rb, Center.getX() + Ra, Center.getY() + Rb);
}

bool myEllipse::isCutByLine(myLine L) {
	double a = (-L.s.getY() + L.e.getY()) / (L.s.getX() - L.e.getX());
	double b = -L.s.getY() - a * L.s.getX();

	if (giaiPT(Rb * Rb + pow(Ra,2) * a * a, 2 * a * b * Ra * Ra, Ra * Ra * b * b - pow(Ra, 2) * pow(Rb, 2)) == 0) {
		return false;
	}
	else return true;

}

// Semi-Circle

void mySemiCircle::Draw(HDC hdc)
{
	if (Direct == 1) {
		Pie(hdc, Center.getX() - R1, Center.getY() - R2, Center.getX() + R1, Center.getY() + R2, Center.getX() + R1, Center.getY(), Center.getX() - R1, Center.getY());
	}
	else Pie(hdc, Center.getX() - R1, Center.getY() - R2, Center.getX() + R1, Center.getY() + R2, Center.getX() - R1, Center.getY(), Center.getY() + R2, Center.getY());
}

bool mySemiCircle::isCutByLine(myLine L) {
	double a = (-L.s.getY() + L.e.getY()) / (L.s.getX() - L.e.getX());
	double b = -L.s.getY() - a * L.s.getX();

	float x = Center.getX();
	float y = - Center.getY();

	if (Direct == 1) {
		if (giaiPT(pow(a, 2) + 1, 2 * a * b - 2 * y * a + 2 * x, pow(b, 2) - 2 * y * b + pow(y, 2) - pow(R1, 2) - pow(x, 2)) == 0) {
			return false;
		}
	}
	else return true;
}

// Polygon

void myPolygon::Draw(HDC hdc)
{
	int n = point.size();
	POINT* pt = new POINT[n];
	//POINT pt[1] = { 0,0 };
	for (int i = 0; i < n; i++) {
		int x = point[i].getX();
		int y = point[i].getY();
		pt[i] = { x, y };
	}
	Polygon(hdc, pt, n);
}

bool myPolygon::isCutByLine(myLine L) {
	int n = point.size();
	if (doIntersect(L.s, L.e, point[n - 1], point[0])) {
		return true;
	}
	for (int i = 0; i < n - 1; i++) {
		if (doIntersect(L.s, L.e, point[i], point[i + 1])) {
			return true;
			break;
		}
	}
	return false;
}

// Rectangle

void myRectangle::Draw(HDC hdc)
{
	Rectangle(hdc, LLower.getX(), LLower.getY(), RUpper.getX(), RUpper.getY());
}

bool myRectangle::isCutByLine(myLine L) {
	myPoint RLower = (RUpper.getX(), LLower.getY());
	myPoint LUpper = (LLower.getX(), RUpper.getY());
	if (doIntersect(L.s, L.e, LUpper, RUpper) || doIntersect(L.s, L.e, RUpper, RLower) || doIntersect(L.s, L.e, LLower, RLower) || doIntersect(L.s, L.e, LUpper, LLower)) {
		return true;
	}
	else return false;
}

// Square

void mySquare::Draw(HDC hdc)
{
	myPoint RLower = (RUpper.getX(), LLower.getY());
	myPoint LUpper = (LLower.getX(), RUpper.getY());
	Rectangle(hdc, LLower.getX(), LLower.getY(), RUpper.getX(), RUpper.getY());
}

bool mySquare::isCutByLine(myLine L) {
	myPoint RLower = (RUpper.getX(), LLower.getY());
	myPoint LUpper = (LLower.getX(), RUpper.getY());
	if (doIntersect(L.s, L.e, LUpper, RUpper) || doIntersect(L.s, L.e, RUpper, RLower) || doIntersect(L.s, L.e, LLower, RLower) || doIntersect(L.s, L.e, LUpper, LLower)) {
		return true;
	}
	else return false;

}

// Triangle

void myTriangle::Draw(HDC hdc)
{
	POINT pt[3] = { p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY() };
	Polygon(hdc, pt, 3);
}

bool myTriangle::isCutByLine(myLine L) {
	if (doIntersect(L.s, L.e, p1, p2) || doIntersect(L.s, L.e, p2, p3) || doIntersect(L.s, L.e, p3, p1)) {
		return true;
	}
	else return false;
}
