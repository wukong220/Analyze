#ifndef PARAS_H
#define PARAS_H

#include <cmath>
#include <vector>
#include <iostream>						//for test #include <iostream>

using namespace std;

extern const int Num_info;				//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]

extern const int N_chain;				//Polarization of single chain
extern const int Num_chains;			//Number of the chains
extern const int Num_beeds; 			//Number of beeds

extern const int dimension;
extern const int Num_file;
extern vector<int> closefiles;		//closefiles -> #include <vector>
extern string finname;				//empty or single input file -> #include <string>
extern string foutname;		
extern string outname;

extern const double md_dt;
extern const int Num_frame;
extern const int dNM;
extern const int Max_frame;
extern const int framestep;

//extern vector<vector<vector<double> > > chain(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); //iframe, id , type,xu,yu,zu...
//vector< vector<double> > position(Num_beeds, vector<double>(3, 0));			//xu, yu, zu

//extern vector<vector<vector<double> > > center(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));			//each frame with centers of chain
	
//extern vector<vector<int> >count(Num_file + 1, vector<int>(Max_frame));		//count 000
//extern vector<vector<vector<double> > > msd(Max_frame, vector<vector<double> >(Num_chains, vector<double>(dimension*Num_file+1, 0))); //mean squared displacement of each chain
	
//extern vector<string> filename(Num_file + 1);				//input filename
//extern vector<string> label(Num_file);						//label
extern vector<int> files;						//Num_file, max_file, files, Num_frames
	
//extern vector<vector<int> > frames(Num_file + 1, vector<int>(2, Num_frame));			//ifile: Num_frame, Max_frame

void output();				//for test
#endif