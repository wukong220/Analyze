//msd
//ave 
//files

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

#define max(x, y)  ( x >= y? x : y )	//#include <cmath>
#define min(x, y)  ( x <= y? x : y )	

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]

const int N_chain = 30;									//Polarization of single chain
const int Num_chains = 1;								//Number of the chains
const int Num_beeds = N_chain * Num_chains; 			//Number of beeds


const int dimension = 2;
const int Num_file = 20;


//files
std::vector<int> closefiles{};				//closefiles
std::string foutname = "msd_001.txt";


const double md_dt = 0.001;
const int Num_frame = 1000;
const int Max_frame = Num_frame - 50;
const int framestep = 100000;

const int len = 2;
using namespace std;

int main() 
{
	//chain[i][j][k]: iframe, id , type,xu,yu,zu...
	vector<vector<vector<double> > > chain(Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0))); 
	
	//center[i][j][k]: iframe jchain centers x or y or z
	vector<vector<vector<double> > > center(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));			
	
	//position of end-to-end
	vector<vector<double> >end(2,vector<double>(dimension,0));
	
	//Re[i][j][k]: iframe jchain Re: x or y or z
	vector<vector<vector<double> > > Re(Num_frame, vector<vector<double> >(Num_chains, vector<double>(dimension,0)));			

	//count: 0 for msd; 1 for Re; 2 for Rg
	vector<vector<int> >count(4,vector<int>(Max_frame,0));		
	
	//mean squared displacement of each chain
	vector<vector<vector<double> > > msd(Max_frame, vector<vector<double> >(Num_chains, vector<double>(dimension*Num_file+1, 0))); 
	
	vector<string> filename(Num_file + 1);				//input filename
	vector<string> label(Num_file);						//label
	vector<int> files(3, Num_file);						//Num_file, max_file, files
	
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
	
	for (int i = 0; i < Num_file; i++)
	{

		if (i < 9)
		{
			ss << "00" << i + 1 << "u.lammpstrj";
			sl << "00" << i + 1;
		}
		else if (i >= 9)
		{
			ss << "0" << i + 1 << "u.lammpstrj";
			sl << "0" << i + 1;
		}
		ss >> filename[i];
		sl >> label[i];
		ss.clear();
		sl.clear();
	}
	
	//for output: single or average
	ofstream fout(foutname);	
	for (int i = 0; i < foutname.size(); i++)
	{
		if (foutname[i] >= '0' && foutname[i] <= '9')
		{
			filename[Num_file] += foutname[i];
			files[1] = 1;
			files[2] = 1;
		}
	}
	
	for(int ifile = 0; ifile < files[1]; ifile++)
	{
		//input
		ifstream fin;	
		if (filename[Num_file] != "\0")
		{
			filename[Num_file] += "u.lammpstrj";
			fin.open(filename[Num_file]);
			str = filename[Num_file];
		}
		else 
		{
			fin.open(filename[ifile]);
			str = filename[ifile];
		}
		
		for (int j = 0; j < closefiles.size(); j++)		//rule out the files
		{
			if(!fin.is_open())
				error = "\"ERROR\": Cannot open ";
			else if (ifile == closefiles[j] - 1)
				error = "\"CLOSE\": ";
				
			if(error != "Right")
			{
				cout << error << str << endl;
				files[2]--;
				label[ifile] = "000";		//for average
				break;
			}
		}
			
		if(error != "Right")
		{
			error = "Right";	//for next calculation
			continue;
		}
		cout << "Opening " << str << "……" << endl;
			
		int timestep = 0;
		for (int i =0; i < Num_frame; i++)
		{
			for (int clear = 0; clear < 2; clear++)			//celar the head
				getline(fin, temp);
			ss << temp;
			ss >> timestep;								//read Timestep
			if (timestep != i * framestep)
			{
				error = "\"ERROR\": TIMESTEP!";		//error timestep
				cout << error << endl;
				files[2]--;					//for average
				label[ifile] = "000";
				break;
			}
			ss.clear();
			
			for (int clear = 0; clear < 2; clear++)			//clear the head
				getline(fin, temp);
			ss << temp;
			ss >> Num_atoms;								//read Number of atoms
			Num_obs = Num_atoms - Num_beeds;		
			ss.clear();
			
			for (int clear = 0; clear < 5; clear++)			//clear the head
				getline(fin, temp);
			
			for (int j = 0; j < Num_beeds; j++)
				{
					getline(fin, temp);
					stringstream input(temp);
					for (int k = 0; k < Num_info; k++)
						input >> chain[i][j][k];
				}

			for (int clear = 0; clear < Num_obs; clear ++)	//clear the tail
				getline(fin, temp);
		}
		fin.close();
		
		//Rule out the errors
		if(error != "Right")
		{
			error = "Right";
			continue;
		}
		//cout << chain[0][0][2] << " " << chain[0][0][3] << " " << chain[0][0][4] << endl;
		
		//mean-squared end-to-end distance
		for (int i = 0; i < Num_frame; i++)
		{
			for (int j = 0; j < Num_chains; j++)
			{
				for (int dim = 0; dim < dimension; dim++)
				{
					end[0][dim] = chain[i][N_chain * j][dim + 2];
					end[1][dim] = chain[i][N_chain * (j + 1) - 1][dim + 2];
				}

			}
		}
		
		//position of the center of mass
		for (int i = 0; i < Num_frame; i++)			
		{
			for (int j = 0; j < Num_chains; j++)
			{
				for (int k = N_chain * j; k < N_chain * (j + 1); k++)	//positions of chains are in the same vector 
				{
					//center of position for: i frame j chain x or y
					for (int dim = 0; dim < dimension; dim++)
						center[i][j][dim] += chain[i][k][dim+2];
					//cout << chain[i][k][2] << " " << chain[i][k][3] << " " << endl;
				}
				//center = sum / N
				for (int dim = 0; dim < dimension; dim++)
					center[i][j][dim] /= N_chain;
				//cout << center[i][j][0] << " " << center[i][j][1] << endl << endl;
			}
		}
		
		//mean-squared displacement
		for (dt = 1; dt <= Max_frame; dt++)
		{
			for(Tstart = 0; Tstart < min(Max_frame, Num_frame - dt); Tstart++)
				{
					Tstop = Tstart + dt;
					count[0][dt-1]++;
					for(int i = 0; i < Num_chains; i++)
					{
						int k = dimension * ifile + 1;
						msd[dt-1][i][k] += (center[Tstop][i][0] - center[Tstart][i][0])*(center[Tstop][i][0] - center[Tstart][i][0]); 
						msd[dt-1][i][k+1] += (center[Tstop][i][1] - center[Tstart][i][1])*(center[Tstop][i][1] - center[Tstart][i][1]);
						if(Tstart == (min(Max_frame, Num_frame - dt)-1))
							msd[dt-1][i][0] += msd[dt-1][i][k] + msd[dt-1][i][k+1];
						/*cout << Tstart << " " << dt << " " << Tstop << " " 
						<< (center[Tstop][i][0] - center[Tstart][i][0])*(center[Tstop][i][0] - center[Tstart][i][0])+(center[Tstop][i][1] - center[Tstart][i][1])*(center[Tstop][i][1] - center[Tstart][i][1]) << " "
						<< msd[dt-1][i][2] << " " << msd[dt-1][i][2]/count[0][dt-1] << endl;*/
					}
				}
			
			//cout << msd[dt-1][0][2]/count[0][dt-1] << endl;
		}
		
		//initialization
		for (int i = 0; i < Num_frame; i++)
		{
			for (int j = 0; j < Num_chains; j++)
			{
				for (int dim = 0; dim < dimension; dim++)
					center[i][j][dim] = 0;
			}
		}
	}
	
	//output 
	//cout << 1 * framestep * md_dt<< " " << msd[0][0][2]/count[0][0] << endl;
	fout << "time ";
	cout << "time "; 
	for (int i = 0; i < files[1]; i++)
	{
		fout << "msd[" << label[i] << "] ";
		cout << "msd[" << label[i] << "] ";
	}
	fout << "ave\n";	
	cout << "ave\n";
	
	//output for msd
	for (int iframe = 0; iframe < Max_frame; iframe++)
	{
		time = (iframe + 1) * framestep * md_dt;
		fout << time << " ";
		cout << time << " ";
		for (int ifile = 0; ifile < files[1]; ifile++)
		{
			int j = ifile * dimension + 1; 
			for(int i = 0; i < Num_chains; i++)
			{	
				//if (label[ifile] != "000")
					//fout << files[2] * (msd[iframe][i][j] + msd[iframe][i][j+1])/(count[0][iframe])<< " ";
				//cout << msd[iframe][i][j] << " " << msd[iframe][i][j+1] << " " 
					cout << setw(len) << files[2] * (msd[iframe][i][j] + msd[iframe][i][j+1])/(count[0][iframe])<< " ";
				if (ifile == files[1] - 1)
				{
					fout << msd[iframe][i][0] / count[0][iframe] << " ";
					cout << setw(len) << msd[iframe][i][0] / count[0][iframe] << " ";
				}
			}
		}
		fout << endl;
		cout << endl;
	}
	fout.close();
}