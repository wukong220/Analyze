#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const double mass = 1.0;
int Num_file = 20;

int N_chain = 3;									//Polarization of single chain
int Num_chains = 1;								//Number of the chains
int Num_beeds = N_chain * Num_chains; 			//Number of beeds
//vector<string> type{"1", "2"};								//atom types to read

vector<int> closefiles{};				//closefiles
string logname = "000.test";
string foutname = "000.test";
string finname = "001";
ofstream output;

const double md_dt = 0.001;
const int framestep = 5000;	
int Num_frame = 10000;
int dNM = 5000;
int Max_frame = Num_frame - dNM;


int main() 
{
			
	string str;
	stringstream ss;
	
	clock_t start = clock();		//start time
	vector<string> filename = show(logname, finname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);		//for single file
	//vector<string> filename = show(logname, foutname, Num_chains, N_chain, Num_beeds, Max_frame);	//for serials files
	
	//vecAtom[iframe] [id] [id,type,xu,yu,zu...]
	vec_doub3 vecAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info, 0))); 
	//rCM[iframe] [jchain] [x,y,z]
	vec_doub3 rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension + 1,0)));	//each frame with centers of chain	
	//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average, (dimension+1)for sum
	vec_doub3 msdCOM(Max_frame, vector<vector<double> >(Num_chains, vector<double>((dimension + 1) * Num_file + 1, 0))); 	//msd of CM for each chain
	//cnt[0,ifile] [msd_frame]: 0 for sum of average; (Max_frame+1) for compare average 

	//rAtom[iframe] [jatom] [x,y,z]
	vec_doub3 rAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double> (dimension + 1, 0)));
	vec_doub3 msdDOT(Max_frame, vector<vector<double> >(Num_beeds, vector<double>((dimension + 1) * Num_file + 1, 0)));
	//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average, (dimension + 1)for sum
	vec_doub3 msdAVE(Max_frame, vector<vector<double> >(Num_chains, vector<double>(N_chain + 1, 0))); 	//msd of CM for each chain
	
	//LmpFile infiles;
	LmpFile inFiles(filename);
	//cout << inFiles;
	//cin.get();
	
	int f = inFiles.files();
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	for(int ifile = 0; ifile < f; ifile++)
	{
		vecAtom = inFiles.read_data(ifile, output, Num_beeds, closefiles);		//read atom data from files, exluding closefiles
		//cout << vecAtom;
		//inFiles.msd(ifile, vecAtom, msdCOM, msdAVE, "all");

		rCM = inFiles.center(ifile, N_chain, vecAtom);			//positiion of CM from atom data of files
		//cout << "rCM: \n" << rCM;
		inFiles.msd_point(ifile, rCM, msdCOM);
		//cout << "msd: \n" << msdCM;
		
		rAtom = read_data(vecAtom);		//read atom data from vectors
		//cout << "rAtom: \n" << rAtom;
		inFiles.msd_ave(ifile, rAtom, msdDOT, msdAVE);
		//cout << "msdAVG: \n" << msdAVG;
		
	}
	cin.get();
	//cout << "msdcom msdave\n" << msdCOM << " " << msdAVE;
	//inFiles.out_msd(foutname, msdCM, "com");
	inFiles.out_msd(foutname, msdCOM, msdAVE);
	
	cout << endl << inFiles;
	cout << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;
	output << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << "\n" << endl;	
	//time

	str = time(start);
	output << str << endl;
	output.close();
	return 0;
}