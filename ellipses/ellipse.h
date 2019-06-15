#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
class ellipse
{
	private:
		vector<double> m_center;
		vector<double> m_shape;
		vector<double> m_orient;
		vector<double> m_theta_b;	//theta, a, b
		vector<double> m_axis;
	public:
		ellipse();
		ellipse(vector<double> shape, vector<double> orient, vector<double> center = {0, 0, 0});
		ellipse(vector<double> shape, double theta, vector<double> axis = {0, 0, 1}, vector<double> center= {0, 0, 0});
		~ellipse();
		void q2ax();
		double x2y(doubel x);
		
};











#endif