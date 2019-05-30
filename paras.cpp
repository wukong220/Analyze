#include "paras.h"

//os << vec
ostream & operator<<(ostream & os, vector<vector<int> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<double> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<string> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<vector<double> > > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		os << i << " :" << endl;
		for (int j = 0; j < vec[i].size(); j++)
			{
				for (int k = 0; k < vec[i][j].size(); k++)
					os << vec[i][j][k] << " ";
				os << endl;
			}		
		os << endl;
	}
	os << endl;
	return os;
}

Test::Test()
{
	m_x = vector<int>(3,0);
}

Test::~Test()
{}

void Test::out()
{
	m_x[0] += 1;
	for(int i = 0; i < m_x.size(); i++)
		cout << m_x[i] << " ";
	cout << endl;
}