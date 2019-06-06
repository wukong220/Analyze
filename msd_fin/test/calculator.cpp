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
#include <cmath>
#include <ctime>
#include <string>
#include "paras.h"

using namespace std;
bool sq();
bool sum();
const int framestep = 5000;
const double kB=1.3806485279*pow(10,-23);
const double PI=3.141592653;
ofstream output;

void now(ofstream* fout);
bool input(int &x);
bool input(string &x);
int main()
{
	double N=207;
	double R0=10.0/2.0;
	double S=PI*R0*R0;
	double l=200;
	double phi=0.4;
	
	stringstream ss;	
	string str;
	
	vector<string> a(3,"000");
	vector<string> b = a;
	cout << b;
	
 // vector<string> str(2);
	/*while (1)
	{
		cout << " Square: " << endl;
		if(!sq())
			break;
	};
	
	while (1)
	{
		cout << " Sum: " << endl;
		if(!sum())
			break;
	};*/
	return 0;
}
bool sq()
{
	string str;
	stringstream ss;
	vector<double> num(2);
	double dx;
	getline(cin, str);
	ss << str;
	if (ss >> num[0] >> num[1])
	{
		dx = num[0] - num[1];
		cout << dx * dx << endl << endl;
	}
	else 
		return false;
	return true;
}

bool sum()
{
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