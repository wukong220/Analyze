#ifndef PARAS_H
#define PARAS_H

#include <cmath>
#include <vector>
#include <iostream>						//for test #include <iostream>
#include <fstream>

using namespace std;

extern const int Num_info;				//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]

extern const int N_chain;				//Polarization of single chain
extern const int Num_chains;			//Number of the chains
extern const int Num_beeds; 			//Number of beeds

extern const int dimension;
extern int Num_file;
extern vector<int> closefiles;		//closefiles -> #include <vector>
extern string finname;				//empty or single input file -> #include <string>
extern string foutname;		
extern string outname;
extern ofstream output;

extern const double md_dt;
extern const int Num_frame;
extern const int dNM;
extern const int Max_frame;
extern const int framestep;

//iframe, id , type,xu,yu,zu...
extern vector<vector<vector<double> > > atom; 

//each frame with centers of chain
extern vector<vector<vector<double> > > center;				

extern vector<vector<int> >count;		//count 000

//mean squared displacement of each chain
extern vector<vector<vector<double> > > msd; 	

extern vector<vector<string> > filename;				//input filename

extern vector<string> label;						//label

//Num_file, max_file, files, Num_frames
extern vector<int> file;						

//ifile: Num_frame, Max_frame
extern vector<vector<int> > frames;	

#define max(x, y)  ( x >= y? x : y )
#define min(x, y)  ( x <= y? x : y )

extern ofstream output;

//vector<vector<int> > test(vector<vector<int> > &a);				//for test
//vector<vector<vector<double> > > center(vector<vector<vector<double> > > &a); 

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