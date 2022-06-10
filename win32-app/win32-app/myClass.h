#ifndef PROJECT_h
#define PROJECT_h

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <win32-app.cpp>

using namespace std;

class Figure
{
public:
	virtual void Input(istream&) = 0;
};

class Point
{
private:
	float x, y;
public:
	Point(float a = 0, float b = 0) {
		x = a;	y = b;
	}
	void SetPoint(float a = 0, float b = 0) {
		x = a;	y = b;
	}
	void Input(istream& inDevice) {
		cout << "Nhap x: " << endl;
		inDevice >> x;
		cout << "Nhap y: " << endl;
		inDevice >> y;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

// Line
class Line : public Figure
{
public:
	int a, b, c;
	Point s, e;
	Line() {}
	Line(Point a, Point b);
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Point p);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

class Circle : public Figure
{
	float R;
public:
	Point O;
	Circle() {}
	Circle(Point O, float r);
	virtual void Input(istream& inDevice);
	virtual bool Draw(HDC hdc);
	virtual bool isCutByLine(Line L);
	friend bool Intersect(int a, int b, int c, Point p, int radius);
};

class Elipse : public Figure
{
protected:
	float Ra, Rb;
public:
	Point Center;
	Elipse(float a, float b);
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Line L);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

class SemiCircle : public Figure
{
public:
	Point start, end, topcenter;
	SemiCircle() {}
	SemiCircle(Point start, Point end, float r);
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Line L);
	friend bool Intersect(int a, int b, int c, Point p, int radius);
};

class Polygon : public Figure
{
	int n;
public:
	Point p[];
	Polygon() {}
	Polygon(Point p[], int n);
	virtual void Input(istream& inDevice);
	//virtual float Area();
	virtual bool isCutByLine(Line L);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

class Rectangle : public Figure
{
private:
	float width, height;
public:
	Rectangle() {}
	Point RUpper, LLower;
	Rectangle(Point rUpper, Point lLower);
	void setRectangle(Point rUpper, Point lLower);
	//virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Line L);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

class Square : public Figure
{
private:
	float width;
public:
	Square() {}
	Point RUpper, LLower;
	Square(Point rUpper, Point lLower);
	void setSquare(Point rUpper, Point lLower);
	//virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Line L);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

class Triangle : public Figure
{
private:
	float x1, x2, x3;
public:
	Triangle() {}
	Point p1, p2, p3;
	Triangle(Point p1, Point p2, Point p3);
	void setTriangle(Point p1, Point p2, Point p3);
	//virtual float Area();
	virtual void Input(istream& inDevice);
	virtual bool isCutByLine(Line L);
	friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};


#endif
