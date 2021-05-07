#ifndef SM_H
#define SM_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <vector>

using namespace std;
double unwrap(double x);
double cut(double x);
ostream & operator<<(ostream & os, vector<double> &vec);

class chromo
{
private:
	int m;
	int n;
	vector<double> inter;
public:
	chromo();
	chromo(int _m, int _n = 1000);
	~chromo();
	void show();
	int size() const {return inter.size();};
	friend ostream & operator<<(ostream & os, chromo &ch);
	double compare(const chromo& ch);
	friend vector<double> compare(const chromo &a, const chromo &b);
	
};

#endif