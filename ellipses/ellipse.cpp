#include "ellipse.h"

ellipse::ellipse()
{
	m_center = vector<double> (3, 0);
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
	cout << theta/3.1415 << "π" << endl;
	m_axis = axis;
}

ellipse::~ellipse()
{
	
}

void ellipse::q2ax()
{
	m_theta = 2 * acos(m_orient[3]);
	cout << m_theta/3.1415 << "π "<< endl;
	double t =  sqrt(1 - m_orient[3] * m_orient[3]);
	m_axis = vector<double> {m_orient[0]/t, m_orient[1]/t, m_orient[2]/t};
}

vector<double> ellipse::x2y(double x)
{
 	vector<double> y(2, 0);
	double B1, B2, C1, C2;
	double A, B, C;
	double delta;
	double ax = m_shape[0];
	double by = m_shape[1];
	double x0 = m_center[0];
	double y0 = m_center[1];
	//cout << ax << " " << by << " " << x0 << " " << y0 << " " << endl;
	A = sin(m_theta) * sin(m_theta) / (ax * ax) + cos(m_theta) * cos(m_theta) / (by * by);
	B1 = 2 * sin(m_theta) * (x0 + x * cos(m_theta))/(ax * ax);
	B2 = 2 * cos(m_theta) * (y0 - x * sin(m_theta))/(by * by);
	B = B1 + B2;
	C1 = (x * x * cos(m_theta) * cos(m_theta) + 2 * x0 * cos(m_theta) * x + x0 * x0) / (ax * ax);
	C2 = (x * x * sin(m_theta) * sin(m_theta) - 2 * y0 * sin(m_theta) * x + y0 * y0) / (by * by);
	C = C1 + C2 - 1;
	delta = B * B - 4 * A * C;
	//cout << "A B C delta\n" << A << " " << B << " " << C << " " << delta << " "<< endl;
	y[0] = (-B + sqrt(delta)) / (2 * A);
	y[1] = (-B - sqrt(delta))/(2 * A);
	return y;
}