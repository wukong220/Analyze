#ifndef PARAS_H
#define PARAS_H

#include <cmath>
#include <vector>
#include <iostream>						//for test #include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

extern const int Num_info;				//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]

extern const int N_chain;				//Polarization of single chain
extern const int Num_chains;			//Number of the chains
extern const int Num_beeds; 			//Number of beeds
extern vector<string> type;

extern const int dimension;
extern const int Num_file;
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

extern ofstream output;

//output for check
ostream & operator<<(ostream & os, vector<int> &vec);
ostream & operator<<(ostream & os, vector<double> &vec);
ostream & operator<<(ostream & os, vector<vector<int> > &vec);
ostream & operator<<(ostream & os, vector<vector<double> > &vec);
ostream & operator<<(ostream & os, vector<vector<string> > &vec);
//just for fun
ostream & operator<<(ostream & os, vector<vector<vector<double> > > &vec);	

//vector<vector<vector<double> > > center(vector<vector<vector<double> > > &a); 




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