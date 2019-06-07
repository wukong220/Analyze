#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const double mass = 1.0;
int Num_file = 20;

int N_chain = 30;									//Polarization of single chain
int Num_chains = 1;								//Number of the chains
int Num_beeds = N_chain * Num_chains; 			//Number of beeds
//vector<string> type{"1", "2"};								//atom types to read

vector<int> closefiles{};				//closefiles
string logname = "000";
string foutname = "000";
string finname = "001";
ofstream output;

const double md_dt = 0.001;
const int framestep = 5000;	
int Num_frame = 20000;
int dNM = 3000;
int Max_frame = Num_frame - dNM;


int main() 
{
			
	string str;
	stringstream ss;
	
	clock_t start = clock();		//start time
	vector<string> filename = show(logname, finname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);		//for single file
	//vector<string> filename = show(logname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);	//for serials files
	
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	vec_doub3 vecAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
	//rCM[iframe] [jchain] [x,y,z]
	vec_doub3 rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension + 1,0)));	//each frame with centers of chain	
	//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average, (dimension+1)for sum
	vec_doub3 msdCM(Max_frame, vector<vector<double> >(Num_chains, vector<double>((dimension + 1) * Num_file + 1, 0))); 	//msd of CM for each chain
	//cnt[0,ifile] [msd_frame]: 0 for sum of average; (Max_frame+1) for compare average 

	//LmpFile infiles;
	LmpFile inFiles(filename);
	cout << inFiles;
	cin.get();
	
	int f = inFiles.files();
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	for(int ifile = 0; ifile < f; ifile++)
	{
		vecAtom = inFiles.read_data(ifile, closefiles, output, Num_beeds);		//read atom data from files, exluding closefiles
		//cout << vecAtom;
		rCM = inFiles.center(ifile, N_chain, vecAtom);			//positiion of CM from atom data of files
		//cout << "rCM: \n" << rCM;
		inFiles.msd_ave(ifile, rCM, msdCM);
		//cout << "msd: \n" << msdCM;
	}
	inFiles.out_msd(foutname, msdCM);
	cout << endl << inFiles;
	cout << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;
	output << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;	
	//time

	str = time(start);
	output << str << endl;
	output.close();
	return 0;
}