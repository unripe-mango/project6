#ifndef MY_PROJECT_H
#define MY_PROJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "framework.h"

using namespace std;

class myPoint
{
private:
	float x, y;
public:
	myPoint(float a = 0, float b = 0) {
		x = a;	y = b;
	}
	void SetPoint(float a = 0, float b = 0) {
		x = a;	y = b;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	//virtual void Draw(HDC hdc) {};
	//friend bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};

// Line : y = ax + b
class myLine
{
public:
	myPoint s, e;

	float a = (- s.getY() + e.getY()) / (s.getX() - e.getX());
	float b = - s.getY() - a * s.getX();

	myLine(float tx, float ty, float aa, float bb) {

		//int a = 0, b = 0, c = 0;
		s = myPoint(tx, ty);
		e = myPoint(aa, bb);

	};
	//myLine(myPoint a, myPoint b);
	//virtual bool isCutByLine(myPoint p);
	virtual void Draw(HDC hdc);
	friend bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2);
};

class myFigure
{

public:
	virtual bool isCutByLine(myLine L) = 0;
	virtual void Draw(HDC hdc) = 0;
};

class myEllipse : public myFigure
{
protected:
	float Ra, Rb;
	myPoint Center;
public:
	myEllipse(float tx, float ty, float aa, float bb) {
		Center = myPoint(tx, ty);
		Ra = aa;
		Rb = bb;
	}
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
};

class myCircle : public myEllipse
{
	float R;
public:
	myPoint O;
	myCircle(float tx, float ty, float r) :myEllipse(tx, ty, r, r) {
		O = myPoint(tx, ty);
		R = r; 
	}
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
};

class mySemiCircle : public myFigure
{
	float R1, R2;
	myPoint Center;
	int Direct = 1;
public:
	mySemiCircle(float tx, float ty, float r1, float r2, int direct = 1) :Center(tx, ty), R1(r1), R2(r2), Direct(direct) {
		Center = myPoint(tx, ty);
		R1 = r1;
		R2 = r2;
		Direct = direct;
	}
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
};

class myPolygon : public myFigure
{
public:
	vector<myPoint> point;
	//myPolygon() {}
	myPolygon(vector<myPoint> pnt) {
		point = pnt;
	}
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
	friend bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2);
};

class myRectangle : public myFigure
{
private:
	float width, height;
public:
	//myRectangle() {}
	myPoint RUpper, LLower;
	myRectangle(float tx, float ty, float tz, float tt) {
		RUpper = myPoint(tx, ty);
		LLower = myPoint(tz, tt);
	}
	//myRectangle(myPoint rUpper, myPoint lLower);
	//void setRectangle(myPoint rUpper, myPoint lLower);
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
	friend bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2);
};

class mySquare : public myFigure
{
private:
	float width;
public:
	//mySquare() {}
	myPoint RUpper, LLower;
	mySquare(float tx, float ty, float tz, float tt) {
		RUpper = myPoint(tx, ty);
		LLower = myPoint(tz, tt);
	}
	//mySquare(myPoint rUpper, myPoint lLower);
	//void setSquare(myPoint rUpper, myPoint lLower);
	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
	friend bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2);
};

class myTriangle : public myFigure
{
private:
	float x1, x2, x3;
public:
	myPoint p1, p2, p3;
	//myTriangle() {}
	//myTriangle(myPoint p1, myPoint p2, myPoint p3);
	//void setTriangle(p3);

	myTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
		p1 = myPoint(x1, y1);
		p2 = myPoint(x2, y2);
		p3 = myPoint(x3, y3);
	}

	virtual void Draw(HDC hdc);
	virtual bool isCutByLine(myLine L);
	friend bool doIntersect(myPoint p1, myPoint q1, myPoint p2, myPoint q2);
};

#endif
