#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const double mass = 1.0;
const int N_chain = 5;									//Polarization of single chain
const int Num_chains = 1;								//Number of the chains
const int Num_beeds = N_chain * Num_chains; 			//Number of beeds
vector<string> type{"1", "2"};								//atom types to read

const int dimension = 2;
const int Num_file = 2;
vector<int> closefiles{};				//closefiles
string finname = "001";				//empty or single input file
string foutname = "test.txt";		
string outname = "test.log";
ofstream output(outname);

const double md_dt = 0.001;
const int Num_frame = 5;
const int dNM = 1;
const int Max_frame = Num_frame - dNM;
const int framestep = 100000;
//atom[iframe] [id] [id,type,xu,yu,zu...]
vector<vector<vector<double> > > atom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
//center[iframe] [jchain] [x,y,z]
vector<vector<vector<double> > > rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));	//each frame with centers of chain	
//count[0,ifile] [msd_frame]: 0 for sum of average
vector<vector<int> >cnt(Num_file + 1, vector<int>(Max_frame));		//count 000
//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average
vector<vector<vector<double> > > msd(Max_frame, vector<vector<double> >(Num_chains, vector<double>(dimension*Num_file+1, 0))); 	//mean squared displacement of each chain
//input filename
vector<vector<string> > filename(Num_file, vector<string>(2));		//filename[ifile][name,label]
//Num_file, max_file, files, 
vector<int> files(3, Num_file);					                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//ifile: Num_frame, Max_frame
vector<vector<int> > frames(Num_file + 1, vector<int>(2, Num_frame));		

int main()
{
	stringstream ss;
	stringstream sl;
	string str;
	string temp;
	string error = "Right";
	int Num_atoms = 1;
	int Num_obs = 1;

	int t = 0;
	int dt = 1;
	int max_dt = 0;
	int Tstart = 0;
	int Tstop = 0;
	double time;
	//LmpFile infiles;
	LmpFile infiles(finname);
	int num = infiles.files();
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	for(int ifile = 0; ifile < num; ifile++)
	{
		atom = infiles.read_data(ifile, closefiles, output);		//read atom data from files, exluding closefiles
		rCM = infiles.center(ifile, N_chain, atom);			//positiion of CM from atom data of files
		msd = infiles.msd_ave(ifile, Num_chains, rCM, cnt);
	}
	cout << endl;
	cout << infiles;
	//cout << atom;
	cout << rCM;
	cout << msd;
	//ifstream fin("test.text");

	return 0;
}