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
#include "paras.h"

using namespace std;

const double kB=1.3806485279*pow(10,-23);
const double PI=3.141592653;

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const double mass = 1.0;
int Num_file = 20;

const double md_dt = 0.001;
const int framestep = 5000;	
int Num_frame = 20000;
int dNM = 3000;
int Max_frame = Num_frame - dNM;

ofstream output;

bool sq();
bool sum();
bool squm();
bool input(int &x);
bool input(string &x);
bool theta();
void show();

int main()
{
	while (1)
	{
		if(!theta())
			break;
	};
	return 0;
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