#include "paras.h"

vec_doub3 operator+=(vec_doub3 &vec0, const vec_doub3 vec1)
{
	for (int i = 0; i < vec0.size(); i++)
	{
		if (vec1.size() == vec0.size())
		{
			for (int j = 0; j < vec0[i].size(); j++)
			{
				if (vec1[i].size() == vec0[i].size())
				{
					for (int k = 0; k < vec0[i][j].size(); k++)
					{
						if (vec1[i][j].size() == vec0[i][j].size())
							vec0[i][j][k] += vec1[i][j][k];
						else 
							cout << "ERROR: Wrong length of vector += vector" << endl;
					}
				}
				else 
					cout << "ERROR: Wrong length of vector += vector" << endl;
			}
		}
		else 
			cout << "ERROR: Wrong length of vector += vector" << endl;
	}
	return vec0;
}

//os << vec
ostream & operator<<(ostream & os, vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<double> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

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

ostream & operator<<(ostream & os, vec_doub3 &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		//extern const int framestep
		os << i * framestep << " :" << endl;
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



//for test
void forTest(vector<int> &files)
{
	files[0] = 999;
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