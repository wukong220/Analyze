#include "ellipse.h"

ellipse::ellipse()	//unit circle
{
	m_center = vector<double> (3, 0);
	m_shape = shape;
	m_orient = vector<double> {0, 0, 0, 1};
	q2ax();
}

ellipse::ellipse(vector<double> center, vector<double> s, vector<double> orient)
{
	m_center = center;
	m_shape = s;
	m_orient = orient;
	q2ax();

}

ellipse::ellipse(vector<double> center, double theta, vector<double> s, vector<double> axis)
{
	m_center = center;
	m_shape = s;
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
	//eff[3] = 2 * x0 * cos(theta) / (ax * ax) - 2 * y0 * sin(theta) / (ay * ay);
	eff[3] = -2 * x0 * cos(theta) / (ax * ax) + 2 * y0 * sin(theta) / (ay * ay);
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

double ellipse::distance(ellipse & eps, double cut)
{
	double a = 0;
	double b = cut + abs(m_shape[0] - m_shape[1]) / 2.0;
	cout << cross(eps);
	cross(eps, b);
	return a;
}

/*double ellipse::distance2(ellipse & eps, double l)
{
	
}*/

double ellipse::cross(ellipse & eps, double l)
{
	vector<double> eff1 = equa();		//equation of ellipse A
	vector<double> eff2 = eps.equa(l);	//equation of ellipse B
	vector<double> eff(5, 0);		//a x^4 + b x^3 + c x^2 + d x + e = 0
	vector<double> sol(7, 0);		//delt, A, B, C, D, E, F, x1, x2, x3, x4
	

	double a1, b1, c1, d1, e1, f1;
	double a2, b2, c2, d2, e2, f2;
	double a, b, c, d, e, delt;
	double A, B, C, D, E;
	double A1, B1, C1, D1, E1, F1;
	//equation group
	a1 = eff1[0]; a2 = eff2[0];
	b1 = eff1[1]; b2 = eff2[1];
	c1 = eff1[2]; c2 = eff2[2];
	d1 = eff1[3]; d2 = eff2[3];
	e1 = eff1[4]; e2 = eff2[4];
	f1 = eff1[5]; f2 = eff2[5];
	//(B*x + D)*y = A * x^2 + C * x + E 
	A = a1 * b2 - a2 * b1;
	B = c1 * b2 - c2 * b1;
	C = d1 * b2 - d2 * b1;
	D = e1 * b2 - e2 * b1;
	E = f1 * b2 - f2 * b1;
	
	//a * x^4 + b * x^3 + c * x^2 + d * x + e = 0
	eff[0] = a = a1 * B * B + b1 * A * A + c1 * A * B;
	eff[1] = b = 2 * a1 * B * D + 2 * b1 * A * C + c1 * B * C + c1 * A * D + d1 * B * B + e1 * A * B;
	eff[2] = c = a1 * D * D + b1 * C * C + 2 * b1 * A * E + c1 * B * E + c1 * C * D + 2 * d1 * B * D + e1 * B * C + e1 * A * D + f1 * B * B;
	eff[3] = d = c1 * D * E + d1 * D * D + e1 * B * E + e1 * C * D + 2 * f1 * B * D + 2 * b1 * C * E;
	eff[4] = e = b1 * E * E + e1 * D * E + f1 * D * D;
	//delt, A, B, C, D, E, F, x1, x2, x3, x4
	if ( a == 0)
	{
		cout << " a = 0 !";
		exit(1);
	}
	sol[4] = D1 = 3 * b - 8 * a * c;
	sol[5] = E1 = -b + 4 * a * b * c - 8 * a * d;
	sol[6] = F1 = 3 * b + 16 * a * c - 16 * a * b * c + 16 * a * b * d - 64 * a * e;
	
	sol[1] = A1 = D1 - 3 * F1; 
	sol[2] = B1 = D1 * F1 - 9 * E1;
	sol[3] = C1 = F1 - 3 * D1 * E1;
	sol[0] = delt = B1 * B1 - 4 * A1 * C1;
	cout << "a x*x + b y*y + c x*y + d x + e y + f = 0\n" << eff1 << eff2 << endl 
	<< "(B*x + D)*y = A * x^2 + C * x + E \n" << B << " " << D << " " << A << " " << C << " " << E << " " << C * C - 4 * A * E << "\n\n" 
	<< "a * x^4 + b * x^3 + c * x^2 + d * x + e = 0\n" << eff << endl;
	cout << "delt A B C D E F\n" << sol << endl;
	return delt;
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

ostream & operator<<(ostream & os, vector<double> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}