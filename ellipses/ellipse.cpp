#include "ellipse.h"

ellipse::ellipse()	//unit circle
{
	m_center = vector<double> (3, 0);
	m_shape = vector<double> (3, 1);
	m_orient = vector<double> {0, 0, 0, 1};
	q2ax();
}

ellipse::ellipse(vector<double> center, vector<double> shape, vector<double> orient)
{
	m_center = center;
	m_shape = shape;
	m_orient = orient;
	q2ax();

}

ellipse::ellipse(vector<double> center, vector<double> shape, double theta, vector<double> axis)
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

void ellipse::q2ax()		//
{
	m_theta = 2 * acos(m_orient[3]);
	cout << m_theta/3.1415 << "π "<< endl;
	double t =  sqrt(1 - m_orient[3] * m_orient[3]);
	m_axis = vector<double> {m_orient[0]/t, m_orient[1]/t, m_orient[2]/t};
}

vector<double> ellipse::equa(double l)
{
 	vector<double> eff(6, 0);	//a, b, c, d, e,f
	double ax = m_shape[0] + l;
	double ay = m_shape[1] + l;
	double x0 = m_center[0];
	double y0 = m_center[1];
	double theta = m_theta;
	
	//cout << ax << " " << ay << " " << x0 << " " << y0 << " " << endl;
	//equation of ellipse: A y*y + B * y + C = 0
	eff[0] = cos(theta) * cos(theta) /(ax * ax) + sin(theta) * sin(theta) / (ay * ay); 
	eff[1] = sin(theta) * sin(theta) / (ax * ax) + cos(theta) * cos(theta) / (ay * ay);
	eff[2] = sin(2 * theta) / (ax * ax) - sin(2 * theta) / (ay * ay);
	eff[3] = 2 * x0 * cos(theta) / (ax * ax) - 2 * y0 * sin(theta) / (ay * ay);
	eff[4] = 2 * x0 * sin(theta) / (ax * ax) + 2 * y0 * cos(theta) / (ay * ay);
	eff[5] = (x0 * x0) / (ax * ax) + (y0 * y0) / (ay * ay) - 1;

	return eff;
}

vector<double> ellipse::x2y(double x, double l)
{
	vector<double> eff = equa(l);
	vector<double> sol(6, 0);		//y0, y1, A, B, C, delt
	double a, b, c, d, e, f;
	double A, B, C;
	double delt;
	
	a = eff[0];
	b = eff[1];
	c = eff[2];
	d = eff[3];
	e = eff[4];
	f = eff[5];
	
	sol[2] = b;
	sol[3] = c * x + e;
	sol[4] = a * x * x + d * x + f;
	sol[5] = sol[3] * sol[3] - 4 * sol[2] * sol[4];
	
	//cout << "A B C delta\n" << A << " " << B << " " << C << " " << delt << " "<< endl;
	sol[0] = (-sol[3] + sqrt(sol[5])) / (2 * sol[2]);
	sol[1] = (-sol[3] - sqrt(sol[5]))/(2 * sol[2]);
	return sol;
}

vector<double> ellipse::cross(ellipse & eps1, double l)
{
	vector<double> eff1 = equa();
	vector<double> eff2 = eps.equa(l);
	vector<double> eff = eff1 - eff2;
	vector<double> sol(8, 0);		//deltx, delty, Ax, Bx, Cx, Ay, By, Cy
	double a, b, c, d, e, f;
	
	a = eff[0];
	b = eff[1];
	c = eff[2];
	d = eff[3];
	e = eff[4];
	f = eff[5];
	sol[2] = c * c - 4 * a * b;
	sol[3] = 2 * c * e - 4 * b * d;
	sol[4] = e * e - 4 * b * f;
	sol[0] = sol[3] * sol[3] - 4 * sol[2] * sol[4]; 
	
	sol[5] = c * c - 4 * a * b; 
	sol[6] = 2 * c * e - 4 * b * d;
	sol[7] = e * e - 4 * b * f;
	sol[1] = sol[6] * sol[6] - 4 * sol[5] * sol[7];
	
	return sol;
}


vector<double> operator-(vector<double> vec1, vector<double> vec2)
{
	int m = vec1.size();
	vector<double> vec0(m, 0);
	if (vec1.size() == vec2.size())
	{
		for (int i = 0; i < m; i++)
			vec0[i] = vec1[i] - vec2[i];
	}
	else 
	{
		cout << " Wrong size!" << endl;
		exit(1);
	}
	return vec0;
}

vector<double> operator+(vector<double> vec1, vector<double> vec2)
{
	int m = vec1.size();
	vector<double> vec0(m, 0);
	if (vec1.size() == vec2.size())
	{
		for (int i = 0; i < m; i++)
			vec0[i] = vec1[i] + vec2[i];
	}
	else 
	{
		cout << " Wrong size!" << endl;
		exit(1);
	}
	return vec0;
}