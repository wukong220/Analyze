#include <ctime>
#include "paras.h"
#include "files.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]
const int dimension = 2;
const double mass = 1.0;
int Num_file = 1;

int N_chain = 2;									//Polarization of single chain
int Num_chains = 1;								//Number of the chains
int Num_beeds = N_chain * Num_chains; 			//Number of beeds
//vector<string> type{"1", "2"};								//atom types to read

vector<int> closefiles{};				//closefiles
string finname;// = "001";				//empty or single input file
string foutname = "000";		
string logname = "000.";

const double md_dt = 1;
const int framestep = 1;	
int Num_frame = 10000;
int dNM = 1000;
int Max_frame = Num_frame - dNM;

void input(int &x);
void input(string &str);
string time (clock_t start);

int main() 
{
			
	string str;
	stringstream ss;
	clock_t start = clock();		//start time
	
	cout << "\"Log file name( \'" << logname << ".MSD.log\' for default): \" \n";
	//output << "\"Log file name( \'" << logname << ".MSD.log\' for default): \" \n";
	input(logname);
	logname += ".MSD.log";
	ofstream output(logname);
	
	cout << "\ndimension = " << dimension << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nframestep = " << framestep << ";\n\n"; //default information
	output << "dimension = " << dimension << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nframestep = " << framestep << ";\n\n";
	cout << "\"Number of chains( \'" << Num_chains << "\' for default): \"\n";
	output << "\"Number of chains( \'" << Num_chains << "\' for default): \"\n";
	input(Num_chains);
	cout << "\"Number of atoms( \'" << N_chain << "\' for single chain default): \"\n";
	output << "\"Number of atoms( \'" << N_chain << "\' for single chain default): \"\n";
	input(N_chain); 
	Num_beeds = N_chain * Num_chains;
	
	cout << "\n\"Number of files(\'" << Num_file << "\' for default): \"\n";
	output << "\n\"Number of files(\'" << Num_file << "\' for default): \"\n";
	input(Num_file);
	if (Num_file == 1)
	{
		cout << "\"Input file name(without \'u.lammpstrj\'):\" \n";
		output << "\"Input file name(without \'u.lammpstrj\'):\" \n";
		getline(cin, str);
		ss << str;
		ss >> finname;
	}
	cout << "\"Number of frames( \'" << Num_frame << "\' for default): \"\n";
	output << "\"Number of frames( \'" << Num_frame << "\' for default): \"\n";
	input(Num_frame);
	cout << "\"Frames to delete( \'" << dNM << "\' for default): \"\n";
	output << "\"Frames to delete( \'" << dNM << "\' for default): \"\n";
	input(dNM);
	Max_frame = Num_frame - dNM;
	
	cout << "\n\"Output txt file name( \'" << foutname << ".MSD.txt\' for default): \" \n";
	output << "\n\"Output txt file name( \'" << foutname << ".MSD.txt\' for default): \" \n";
	input(foutname);
	foutname += ".MSD.txt";

	//atom[iframe] [id] [id,type,xu,yu,zu...]
	vec_doub3 vecAtom(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
	//rCM[iframe] [jchain] [x,y,z]
	vec_doub3 rCM(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension + 1,0)));	//each frame with centers of chain	
	//msd[iframe] [jchain] [0,x,y,z]: 0 for sum of average, (dimension+1)for sum
	vec_doub3 msdCM(Max_frame, vector<vector<double> >(Num_chains, vector<double>((dimension + 1) * Num_file + 1, 0))); 	//msd of CM for each chain
	//cnt[0,ifile] [msd_frame]: 0 for sum of average; (Max_frame+1) for compare average 

	//LmpFile infiles;
	LmpFile inFiles(finname);

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
	cout << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << endl;
	output << "\"Writing\": " << foutname << endl << "\"Outputing\": " << logname << endl;	
	//time

	str = time(start);
	output << str << endl;
	output.close();
	return 0;
}

inline void input(int &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if(str != "\n")
	{
		ss << str;
		ss >> x;
	}
}

inline void input(string &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if(str != "\n")
	{
		ss << str;
		ss >> x;
	}
}

string time (clock_t start)
{
	stringstream ss;
	string str;
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
	return st;
}