#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const int Num_file = 2;

const double mass = 1.0;
const int N_chain = 3;									//Polarization of single chain
const int Num_chains = 1;								//Number of the chains
const int Num_beeds = N_chain * Num_chains; 			//Number of beeds
//vector<string> type{"1", "2"};								//atom types to read

vector<int> closefiles{};				//closefiles
string finname = "001";				//empty or single input file
string foutname = "test.txt";		
string logname = "test.log";


const double md_dt = 0.001;
const int Num_frame = 10000;
const int dNM = 5000;
const int Max_frame = Num_frame - dNM;
const int framestep = 5000;

int main()
{
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	vec_doub3 vecAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
	//center[iframe] [jchain] [x,y,z]
	vec_doub3 rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));	//each frame with centers of chain	
	//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average
	vec_doub3 msdCM(Max_frame, vector<vector<double> >(Num_chains, vector<double>((dimension + 1) * Num_file + 1, 0))); 	//mean squared displacement of each chain
	//count[0,ifile] [msd_frame]: 0 for sum of average
	
	//LmpFile infiles;
	LmpFile inFiles(finname);
	ofstream output(logname);
	int f = inFiles.files();
	
	//atom[iframe] [id] [id,type,xu,yu,zu...]
	for(int ifile = 0; ifile < f; ifile++)
	{
		//extern int Num_info; int framestep;
		vecAtom = inFiles.read_data(ifile, closefiles, output, Num_beeds);		//data from files, closefiles, atoms
		//cout << vecAtom;
		rCM = inFiles.center(ifile, N_chain, vecAtom);			//positiion of CM from atom data of files
		//cout << "rCM: \n" << rCM;
		inFiles.msd_ave(ifile, rCM, msdCM);
		//cout << "msd: \n" << msdCM;
		
	}
	inFiles.out_msd(foutname, msdCM);
	cout << endl << inFiles;
	cout << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << endl;
	output << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << endl;
	output.close();
	/*vec_doub3 vec0(3, vector<vector<double> >(3, vector<double>(3,1)));
	vec_doub3 vec1(vec0);
	cout << vec0;
	cout << vec1;
	vec0 += vec1;
	cout << vec0;*/
	//ifstream fin("test.text");

	return 0;
}