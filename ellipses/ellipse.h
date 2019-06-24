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
		static vector<double> m_shape;
		vector<double> m_orient;
		double m_theta;
		vector<double> m_axis;
	public:
		ellipse();
		ellipse(vector<double> shape, vector<double> orient = {0, 0, 0, 1}, vector<double> center = {0, 0, 0});
		ellipse(vector<double> shape, double theta, vector<double> axis = {0, 0, 1}, vector<double> center= {0, 0, 0});
		~ellipse();
		void q2ax();
		vector<double> equa(double x, double l = 0);
		double deltx(vector<double> eff);
		vector<double> equ2();
		
};






#endif