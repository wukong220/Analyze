#include "paras.h"

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