#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
extern const vector<double> shape;
extern const double dCut;

class ellipse
{
	private:
		vector<double> m_center;
		vector<double> m_shape;
		vector<double> m_orient;
		double m_theta;
		vector<double> m_axis;
	public:
		ellipse();		//unit circle
		ellipse(vector<double> center, vector<double> s = shape, vector<double> orient = {0, 0, 0, 1});
		ellipse(vector<double> center, double theta, vector<double> s = shape, vector<double> axis = {0, 0, 1});
		~ellipse();
		void q2ax();
		
		vector<double> equa(double l = 0);	//equation of ellipses(l for enlarging): a, b, c, d, e,f
		vector<double> x2y(double x, double l = 0);		//y for given x: y0, y1, A, B, C, delt
		double distance(ellipse & eps, double cut = dCut);
		double cross(ellipse & eps1, double l = 0);  //judge the crosses: deltx, delty, Ax, Bx, Cx, Ay, By, Cy
		//vector<double> equ2();
		
};

vector<double> operator-(vector<double> vec1, vector<double> vec2);
vector<double> operator+(vector<double> vec1, vector<double> vec2);
ostream & operator<<(ostream & os, vector<double> &vec);


#endif