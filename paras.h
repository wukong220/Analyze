#ifndef PARAS_H
#define PARAS_H

#include <cmath>
#include <vector>
#include <iostream>						//for test #include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef vector<vector<vector<double> > > vec_doub3;

extern const int Num_info;				//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
extern const double mass;
extern const int Num_beeds; 			//Number of beed
extern const int dimension;
extern const int Num_file;

extern const double md_dt;
extern const int Num_frame;
extern const int dNM;
extern const int Max_frame;
extern const int framestep;

extern ofstream output;

vec_doub3 operator+=(vec_doub3 &vec0, const vec_doub3 vec1);
//output for check
ostream & operator<<(ostream & os, vector<int> &vec);
ostream & operator<<(ostream & os, vector<double> &vec);
ostream & operator<<(ostream & os, vector<vector<int> > &vec);
ostream & operator<<(ostream & os, vector<vector<double> > &vec);
ostream & operator<<(ostream & os, vector<vector<string> > &vec);
//just for fun
ostream & operator<<(ostream & os, vector<vector<vector<double> > > &vec);	




//for test
void forTest(vector<int> &files);

class Test
{
	private:
		vector<int> m_x;
	public:
		Test();
		~Test();
		
		void out();
};

#endif