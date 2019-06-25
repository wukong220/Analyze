/*************************************************************************
	> File Name: calculator.cpp
	> Author: 悟空
	> Mail: wusong220@outlook.com 
	> Created Time: 四  3/21 21:22:08 2019
 ************************************************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
//#include <cmath>
#include <ctime>
#include <string>
#include <cmath>
//#include "paras.h"
const double PI = 3.1415926;

using namespace std;


bool sq();
bool sum();
bool squm();
bool input(int &x);
bool input(string &x);
bool theta();
void show();
double angle_dot(vector<double> a, vector<double> b);
double angle_cross(vector<double> a, vector<double> b);
ofstream output;

int main()
{
	vector<double> a = {1, 2, 3, 4, 5};
	vector<double> b = {5, 4, 3, 2, 1};
	vector<double> c(5, 0);
	c = a + b;
	cout << c[0] << " " << c[3] << " " << c[4] << endl;
	cin.get();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*double phi = 60 / 180 * PI;
	double t;
	cout << "Please Input PHI: " << endl;
	cin >> t;
	t = t/ 180 * PI;
	vector<double> a = {cos(phi), sin(phi)};
	vector<double> b = {cos(phi + t), sin(phi + t)};
	vector<double> c = {cos(phi + t + PI), sin(phi + t + PI)};
	
	double x1, x2;
	x1 = angle_dot(a, b);
	x2 = angle_dot(a, c);
	cout << " dot : " << x1 << "π " << x2 << "π" << endl;
	
	double y1, y2;
	y1 = angle_cross(a, b);
	y2 = angle_cross(a, c);
	cout << " cross : " << y1 << "π " << y2 << "π"<< endl;
	*/
	/*while (1)
	{
		if(!theta())
			break;
	};*/
	
	return 0;
}

double angle_dot(vector<double> a, vector<double> b)
{
	double x;
	x = abs(a[0] * b[0] + a[1] * b[1]);
	return acos(x) / PI;
}

double angle_cross(vector<double> a, vector<double> b)
{
	double x;
	x = abs(a[0] * b[1] - a[1] * b[0]);
	return asin(x) / PI;
}


bool theta()
{
	double x;
	double theta;
	cout << "quataniam theta: " << endl;
	if (cin >> x)
	{
		theta = 2 * acos(x);
		cout << theta/3.1415 << "π" << endl;
	}
		
	else 
		return false;
	return true;
}

void show()
{
	output.open("test.txt");
	cout << " 0001\n";
	output << " 0001\n";
}

bool sq()
{
	cout << " Square: " << endl;
	string str;
	stringstream ss;
	vector<double> num(4);
	double dx;
	double dy=0;
	getline(cin, str);
	ss << str;
	ss >> num[0] >> num[1];
	ss.clear();
	getline(cin, str);
	ss << str;
	if (ss >> num[2] >> num[3])
	{
		dx = num[0] - num[2];
		dy = num[1] - num[3];
		cout << dx * dx + dy * dy << endl;
	}
	else 
		return false;
	return true;
}

bool squm()
{
	cout << " Square sum: " << endl;
	string str;
	stringstream ss;
	vector<double> num(4);
	double dx;
	getline(cin, str);
	ss << str;
	if(ss >> num[0] >> num[1])
		cout << num[0] * num[0] + num[1] * num[1] << endl;
	else 
	{
		return false;
	}
	return true;
}


bool ave()
{
	cout << " Average: " << endl;
	double sum = 0;
	double x;
	string str;
	stringstream ss;
	int i = 0;
	getline(cin,str);
	ss << str;
	while (ss >> x)
	{
		sum += x;
		i++;
		if (ss.eof())
		{
			cout << sum/i << endl << endl;
			return true;
		}
	}
		return false;
}

inline bool input(int &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if (str == "\0") 
	{
		return false;
	}
	else
	{
		ss << str;
		ss >> x;
		return true;
	}
	cout << "false";
	
	//cout << "Number: " << x << endl;
}

inline bool input(string &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if (str == "\0") 
	{
		return false;
	}
	else
	{
		ss << str;
		ss >> x;
		return true;
	}
	//cout << "String: " << x << endl;
}