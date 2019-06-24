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

vector<double> ellipse::equa(double x, double l)
{
 	vector<double> eff(8, 0);	//y0, y1, a, b, c, d, e,f
	double Ay, By, Cy;
	double a, b, c, d, e, f;
	double delt;
	double ax = m_shape[0] + l;
	double ay = m_shape[1] + l;
	double x0 = m_center[0];
	double y0 = m_center[1];
	double theta = m_theta;
	
	//cout << ax << " " << ay << " " << x0 << " " << y0 << " " << endl;
	//equation of ellipse: A y*y + B * y + C = 0
	eff[2] = a = cos(theta) * cos(theta) /(ax * ax) + sin(theta) * sin(theta) / (ay * ay); 
	eff[3] = b = sin(theta) * sin(theta) / (ax * ax) + cos(theta) * cos(theta) / (ay * ay);
	eff[4] = c = sin(2 * theta) / (ax * ax) - sin(2 * theta) / (ay * ay);
	eff[5] = d = 2 * x0 * cos(theta) / (ax * ax) - 2 * y0 * sin(theta) / (ay * ay);
	eff[6] = 2 * x0 * sin(theta) / (ax * ax) + 2 * y0 * cos(theta) / (ay * ay);
	eff[7] = (x0 * x0) / (ax * ax) + (y0 * y0) / (ay * ay) - 1;
	
	Ay = b;
	By = c * x + e;
	Cy = a * x * x + d * x + f;
	delt = By * By - 4 * Ay * Cy;
	
	//cout << "A B C delta\n" << A << " " << B << " " << C << " " << delta << " "<< endl;
	eff[0] = (-By + sqrt(delty)) / (2 * Ay);
	eff[1] = (-By - sqrt(delty))/(2 * Ay);
	return eff;
}

double ellipse::deltx(vector<double> eff)
{
	double a, b, c, d, e, f;
	double Ax, Bx, Cx;
	double delt;
	a = eff[0];
	b = eff[1];
	c = eff[2];
	d = eff[3];
	e = eff[4];
	f = eff[5];
	Ax = c * c - 4 * a * b;
	Bx = 2 * c * e - 4 * b * d;
	Cx = e * e - 4 * b * f;
	delt = Bx * Bx - 4 * Ax * Cx; 
	return delt;
}