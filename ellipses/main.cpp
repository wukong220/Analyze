#include "ellipse.h"

const vector<double> shape = {2, 1, 1};
const double dCut = 5;	//distace cutoff
int main() 
{
	ellipse eps[2] = {ellipse(), ellipse({5, 0, 0})};
	vector<double> sol;
	double c;
	c = eps[0].cross(eps[1], 1);	//
	cout << c << endl;

	
	return 0;
}
