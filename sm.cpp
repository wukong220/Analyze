#include "sm.h"

using namespace std;

//random number

//unwrap
double unwrap(double x)
{
	if (x > 2)
		cout << "ERROR!";
	else if (x > 1)
		x=x-1;
	return x;
}

//final cutoff
double cut(double x)
{
	if (x < 0)
		x = 0;
	else if (x >= 0.25)
		x = 0.25;
	return x;
}

ostream & operator<<(ostream & os, vector<double> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	cout << endl;
	return os;
}


//class chromo
chromo::chromo()
{
	int m = 23;
	int n = 23;
	inter = vector<double> (m);
	for (int i = 0; i < m; i++)
		inter[i] = i+1;
}

chromo::chromo(int _m, int _n)
{
	m = _m;
	n = _n;
	inter = vector<double> (m, 0);
	bool label = 0;
	for (int i =0; i < m; i++)
	{
		inter[i] = rand()%n + 1;
		for (int j = 0; j < i; j++)
		{
			if (inter[i] == inter[j])
			{
				inter[i] = rand()%n + 1;
				j = -1;
			}
		}	
	}
}

chromo::~chromo()
{
	
}

//output
void chromo::show()
{
	cout << "Chromosomes:\n" << inter << endl;
}
ostream & operator<<(ostream & os, chromo &ch)
{
	os << ch.inter << endl;
	return os;
}

double chromo::compare(const chromo& ch)
{
	vector<double> temp;
	for (int i = 0; i < size(); i++)
		for (int j = 0; j < ch.size(); j++)
		{
			if (inter[i] == ch.inter[j])
				temp.push_back(inter[i]);
		}
	//cout << "Cross:\n" << temp << endl;
	return temp.size()/double(n);
}

vector<double> compare(const chromo &a, const chromo &b)
{
	vector<double> temp;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
		{
			if (a.inter[i] == b.inter[j])
				temp.push_back(a.inter[i]);
		}
	cout << "Cross:\n" << temp << endl;
	return temp;
}