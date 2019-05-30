#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>
#include "paras.h"
#include "files.h"

#define max(x, y)  ( x >= y? x : y )	//#include <cmath>
#define min(x, y)  ( x <= y? x : y )	

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int N_chain = 30;									//Polarization of single chain
const int Num_chains = 1;								//Number of the chains
const int Num_beeds = N_chain * Num_chains; 			//Number of beeds: atoms to read
vector<string> type{1, 2};								//atom types to read

const int dimension = 2;
const int Num_file = 20;
vector<int> closefiles{};				//closefiles
string finname;// = "003";				//empty or single input file
string foutname = "MSD.000_0.4_2.5_1.0_3.0.txt";		
string outname = "MSD.000.log";
ofstream output(outname);

const double md_dt = 0.001;
const int Num_frame = 35000;
const int dNM = 3000;
const int Max_frame = Num_frame - dNM;
const int framestep = 5000;
//atom[iframe] [id] [id,type,xu,yu,zu...]
vector<vector<vector<double> > > atom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
//rCM[iframe] [jchain] [x,y,z]
vector<vector<vector<double> > > rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));	//each frame with centers of chain	
//count[0,ifile] [msd_frame]: 0 for sum of average
vector<vector<int> >count(Num_file + 1, vector<int>(Max_frame));		//count 000
//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average
vector<vector<vector<double> > > msd(Max_frame, vector<vector<double> >(Num_chains, vector<double>(dimension*Num_file+1, 0))); 	//mean squared displacement of each chain
//input filename
vector<vector<string> > fnamebel(Num_file, vector<string>(2));		//fnamebel[ifile][name,label,Num_info]
//Num_file, max_file, files, 
vector<int> files(3, Num_file);					                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//ifile: Num_frame, Max_frame
vector<vector<int> > frames(Num_file + 1, vector<int>(2, Num_frame));			

int main() 
{
	string str;


	int t = 0;
	int dt = 1;
	int max_dt = 0;
	int Tstart = 0;
	int Tstop = 0;
	double time;


	clock_t start = clock();		//start time

	//input filename
	//LmpFile file;
	LmpFile infiles(finname);		//fnamebel[ifile][name,label]; frames[ifile][Num_frame, Max_frame]
	
	for(int ifile = 0; ifile < infiles.files(); ifile++)
	{
		atom = infiles.read_xyz(ifile, closefiles);		//read data from files
		
	}
		
	






	//time
	clock_t stop = clock();		//#include <ctime>
	double Time = (double)(stop - start)/CLOCKS_PER_SEC;
	vector<int> inter(4,Time);
	inter[1] = inter[0]/3600;
	inter[2] = inter[0]/60%60;
	inter[3] = inter[0]%60;
	string st = "\"Time\": ";    //#include <string>
	for (int i = 0; i < 3; i++)
	{
		ss << inter[i+1];
		ss >> str;  
		if (inter[i+1] < 9)
			st += "0" + str;    //using std::to_string;
		else
			st += str;
		if (i < 2)
			st += ":";
		ss.clear();
	}
	cout << st << endl;
	output << st << endl;
	return 0;
}