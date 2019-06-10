#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const double mass = 1.0;
int Num_file = 2;

int N_chain = 15;									//Polarization of single chain
int Num_chains = 2;								//Number of the chains
int Num_beeds = N_chain * Num_chains; 			//Number of beeds
//vector<string> type{"1", "2"};								//atom types to read

vector<int> closefiles{};				//closefiles
string logname = "000";
string foutname = "000";
string finname ;//= "001";
ofstream output;

const double md_dt = 0.001;
const int framestep = 5000;	
int Num_frame = 1000;
int dNM = 300;
int Max_frame = Num_frame - dNM;


int main() 
{
			
	string str;
	stringstream ss;
	
	clock_t start = clock();		//start time
	//vector<string> filename = show(logname, finname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);		//for single file
	vector<string> filename = show(logname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);	//for serials files
	
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	vec_doub3 vecAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
	//msdCOM[iframe] [jchain] [0,x1,y1,z1,r1 ...]: 0 for average of Num files, (dimension+1)for sum
	vec_doub3 msdCOM(Max_frame, vector<vector<double> >(Num_chains, vector<double>((dimension + 1) * Num_file + 1, 0))); 	//msd of CM for each chain
	//msd[iframe] [jatom] [0,x1,y1,z1,r1 ...]: 0 for average of Num files, (dimension+1)for sum
	vec_doub3 msd(Max_frame, vector<vector<double> >(Num_beeds, vector<double>((dimension + 1) * Num_file + 1, 0)));	//msd of every atom
	//msdAVE[iframe] [jchain] [0, r1,r2,r3 ...]: 0 for average of N beeds	
	vec_doub3 msdAVE(Max_frame, vector<vector<double> >(Num_chains, vector<double>(N_chain + 1, 0))); 	//msd of CM for each chain

	//LmpFile infiles;
	LmpFile inFiles(filename);
	//cout << inFiles;
	//cin.get();
	
	int f = inFiles.files();
	string label = "com";
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	for(int ifile = 0; ifile < f; ifile++)
	{
		vecAtom = inFiles.read_data(ifile, output, Num_beeds);		//read atom data from files, exluding closefiles
		//cout << vecAtom;
		//rCM = inFiles.center(ifile, N_chain, vecAtom);			//positiion of CM from atom data of files
		//cout << "rCM: \n" << rCM;
		//inFiles.msd_point(ifile, rCM, msdCOM);
		//cout << "msd: \n" << msdCM;
		msdAVE = inFiles.msd(ifile, vecAtom, msdCOM, msd, label); // 
	}
	inFiles.out_msd(foutname, msdCOM, msdAVE, label);
	cout << endl << inFiles;		//necessary
	output << endl << inFiles;
	cout << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;
	output << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;	
	//time

	str = time(start);
	output << str << endl;
	output.close();
	return 0;
}