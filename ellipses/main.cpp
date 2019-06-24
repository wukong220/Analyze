
#include "ellipse.h"
using namespace std;

int main() 
{
	ellipse eps;
	vector<double> y;
	y = eps.equa(sin(3.1415/3));
	cout << y[0] << " " << y[1] << endl;
	
	
	return 0;
}
