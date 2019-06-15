#include "ellipse.h"

ellipse::ellipse()
{
	m_center = vector<double> (2, 0);
	m_shape = vector<double> (3, 1);
	m_orient = vector<double> {0, 0, 0, 1};
	q2ax();
}

ellipse::ellipse(vector<double> shape, vector<double> orient, vector<double> center)
{
	m_center = center;
	m_shape = shape;
	m_orient = orient;
	q2ax();

}

ellipse::ellipse(vector<double> shape, double theta, vector<double> axis, vector<double> center)
{
	m_center = center;
	m_shape = shape;
	m_orient = {axis[0] * sin(theta/2.0), axis[1] * sin(theta/2.0), axis[2] * sin(theta/2.0), cos(theta/2.0)};
	m_theta = theta;
	cout << m_theta/3.1415 << "π" << endl;
	m_axis = axis;
}

ellipse::~ellipse()
{
	
}

void ellipse::q2ax()
{
	m_theta = 2 * acos(m_orient[3]);
	cout << m_theta/3.1415 << "π" << endl;
	double t =  sqrt(1 - m_orient[3] * m_orient[3]);
	m_axis = vector<double> {m_orient[0]/t, m_orient[1]/t, m_orient[2]/t};
}