#include "analyser.h"
vec_doub3 operator+=(vec_doub3 &vec0, const vec_doub3 vec1)
{
	for (int i = 0; i < vec0.size(); i++){
		if (vec1.size() == vec0.size()){
			for (int j = 0; j < vec0[i].size(); j++){
				if (vec1[i].size() == vec0[i].size()){
					for (int k = 0; k < vec0[i][j].size(); k++){
						if (vec1[i][j].size() == vec0[i][j].size())
							vec0[i][j][k] += vec1[i][j][k];
						else 
							cout << "ERROR: Wrong length of vector += vector" << endl;
					}
				}
				else 
					cout << "ERROR: Wrong length of vector += vector" << endl;
			}
		}
		else 
			cout << "ERROR: Wrong length of vector += vector" << endl;
	}
	return vec0;
}

ostream & operator<<(ostream & os, vec_doub &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vec_doub2 &vec)
{
	for (int i = 0; i < vec.size(); i++)
		{
			//extern const int steps_frame
			os << i * md_dt * dstep << "th :" << endl;
			for (int j = 0; j < vec[i].size(); j++)
				{
					os << vec[i][j] << " ";
					os << endl;
				}		
			os << endl;
		}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vec_doub3 &vec)
{
	for (int i = 0; i < vec.size(); i++)
		{
			//extern const int steps_frame
			os << i * md_dt * dstep << "th :" << endl;
			for (int j = 0; j < vec[i].size(); j++)
				{
					for (int k = 0; k < vec[i][j].size(); k++)
						os << vec[i][j][k] << " ";
					os << endl;
				}		
			os << endl;
		}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<string> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if ( pCom[i] )
			os << vec[i] <<"[" << setw(3) << setfill('0') << Num_files << "][P" << setw(3) << setfill('0') << pCom[i] <<"]\t\t";
		else
			continue;
	}
		
	return os;
}
//os << vec
ostream & operator<<(ostream & os, vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

vector<string> show(string &logname, string &finname, vector<string> &label, string &foutname, int &Num_chains, int &N_chain, int &Num_beeds, int &Num_frames)
{
	string str;
	int num = 0;	//check for label and input filename
	vector<string> LABEL = {"com", "COM", "ave", "AVE", "all", "ALL", "\0"};
	cout << "\"Log file name( \'" << logname << ".MSD.log\' for default ): \" \n";
	//output << "\"Log file name( \'" << logname << ".MSD.log\' for default ): \" \n";
	//	if (!input(str))
	str = logname;
	logname = str + ".MSD.log";
	//cout << logname << endl;
	output.open(logname);
	cout << "\"Output txt file name( \'MSD." << foutname << ".txt\' for default ): \" \n";
	output << "\"Output txt file name( \'MSD." << foutname << ".txt\' for default ): \" \n";
	//	if(!input(str))
	str = foutname;
	foutname = "MSD." + str + ".txt";
	//cout << foutname << endl;
	
	cout << "\nLabel for MSD( \'" << label[0] << "\' for default & \'com or ave or all\'): \"\n";
	output << "\nLabel for MSD( \'" << label[0] << "\' for default & \'com or ave or all\'): \"\n";
	//	input(label[0]);
	for (int i = 0; i < LABEL.size(); i++)
		{
			if (label[0] == LABEL[i])
				{
					num = 1;
					break;
				}
		}
	if (!num)
		{
			cout << "Wrong Label!" << endl;
			exit(1);
		}
	cout << "Label for output( \'" << label[1] << "\' for default & \'cut or all\'): \"\n";
	output << "Label for output( \'" << label[1] << "\' for default & \'cut or all\'): \"\n";
	//	input(label[1]);
	
	cout << "\n\"Number of files( \'" << Num_files << "\' for default ): \"\n";
	output << "\n\"Number of files( \'" << Num_files << "\' for default ): \"\n";
	//	input(Num_file);
	vector<string> filename(Num_files); //constructor
	cout << "\"Input file name( \'" << finname << "\' for default & without \'u.lammpstrj\' ):\" \n";
	//read input finname
	for (num = 0; num < Num_files; num++)
		{
			//		if(!input(filename[num]))
			break;
		}
	
	//read default finname
	stringstream ss;
	if (num == 0)
		{
			ss << finname;
			while (ss >> filename[num])
				num++;
		}
	if (finname != "\0" && finname != "000")
		Num_files = num;
	filename.resize(Num_files);
	
	//LmpFile Files(filename);
	//cout << Files;
	//cin.get();
	
	cout << "\ndimension = " << dim << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nsteps per frame = " << steps_frame << ";\n\n"; //default information
	output << "\ndimension = " << dim << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nsteps_frame = " << steps_frame << ";\n\n";
	cout << "\"Number of chains( \'" << Num_chains << "\' for default ): \"\n";
	output << "\"Number of chains( \'" << Num_chains << "\' for default ): \"\n";
	//	input(Num_chains);
	cout << "\"Number of atoms( \'" << N_chain << "\' for single chain default ): \"\n";
	output << "\"Number of atoms( \'" << N_chain << "\' for single chain default ): \"\n";
	//	input(N_chain); 
	Num_beeds = N_chain * Num_chains;
	
	cout << "\n\"Number of frames( \'" << Num_frames << "\' for default ): \"\n";
	output << "\n\"Number of frames( \'" << Num_frames << "\' for default ): \"\n";
	//	input(Num_frame);
	//cout << "\"Frames to delete( \'" << dNM << "\' for default ): \"\n";
	//output << "\"Frames to delete( \'" << dNM << "\' for default ): \"\n";
	//input(dNM);
	//Num_frames = Num_frame - dNM;
	cout << "\n";
	output << "\n";
	return filename;
}

string read_atoms(ifstream &fin, int iframe, int nAtoms, vec_doub3 &vec)
{
	string temp;
	stringstream ss;
	string head;
	int Num_atoms = 1;
	int Num_obs = 1;
	
	for (int clear = 0; clear < 2; clear++)		//clear
	getline(fin, temp);
	ss << temp;
	ss >> Num_atoms;							//Number of atoms
	ss.clear();
	Num_obs = Num_atoms - nAtoms;				//for clearing obstacles
	if (Num_obs < 0)
		{
			cout << "Wrong atoms!" << endl;
			output << "Wrong atoms!" << endl;
			exit(1);
		}
	
	for (int clear = 0; clear < 5; clear++)			
		getline(fin, temp);
	head = temp;								//the head
	
	for (int j = 0; j < nAtoms; j++)
		{
			getline(fin, temp);
			ss << temp;
			//extern const int Num_info = 15
			for (int k = 0; k < Num_info; k++)
				ss >> vec[iframe][j][k];
			ss.clear();
		}
	
	for (int clear = 0; clear < Num_obs; clear ++)	//clear information of obstacles
	getline(fin, temp);
	return head;
}

vec_doub2 read_data(ifstream &fin, vec_doub2 &atom, int iframe)
{
	string temp;
	stringstream ss;
	string head;
	int timestep;
	int Num_obs = 1;
	int Num_atoms = 1;
	for (int clear = 0; clear < 2; clear++)			//the head
	getline(fin, temp);
	ss << temp;
	ss >> timestep;												//timestep
	/*if (timestep != iframe * steps_frame)		//extern const int steps_frame = 5000;
	{
	cout << "Current steps_frame: " << timestep/steps_frame << "->";
	cout << "Current Timestep: " << timestep << " != " << iframe * steps_frame << " (" << iframe << " * " << steps_frame << ")" << endl;
	}*/
	ss.clear();
	
	for (int clear = 0; clear < 2; clear++)		//clear
	getline(fin, temp);
	ss << temp;										//extern int Num_atoms = 1;
	ss >> Num_atoms;							//Number of atoms
	if( Num_atoms != nAtoms)
		{
			string error = "\"ERROR\": Num_atoms(dana.cpp:8) -> ";
			cout << "(Current Read) " << Num_atoms << " != " << nAtoms << " ( Setup ) " <<endl;
			output << "(Current Read) " << Num_atoms << " != " << nAtoms << " ( Setup ) " <<endl;
			exit(1);
		}
	ss.clear();
	
	Num_obs = Num_atoms - nAtoms;				//for clearing obstacles:
	if (Num_obs < 0)
		{
			cout << "Wrong atoms!" << endl;
			output << "Wrong atoms!" << endl;
			exit(1);
		}
	
	for (int clear = 0; clear < 5; clear++)			
		getline(fin, temp);
	head = temp;								//all the head
	//for cut
	for (int clear = 0; clear < cut[0] && timestep != iframe * dstep; clear++)
		{
			for (int clear = 0; clear < Num_atoms+2; clear++)	//clear information of obstacles
			getline(fin, temp);
			ss << temp;
			ss >> timestep;
			ss.clear();
			for (int clear = 0; clear < 7; clear++)	//clear information of obstacles
			getline(fin, temp);
		}
	if (timestep != iframe * steps_frame)		//extern const int steps_frame = 5000;
	{
		string error = "\"ERROR\": TIMESTEP/FRAME(dana.cpp:16) -> ";
		cout << error << timestep << " != " << iframe * steps_frame << " (" << iframe << " * " << steps_frame << ")" << endl;
		cout << "Current frame: " << iframe << endl;
		output << error << timestep << " != " << iframe * steps_frame << " (" << iframe << " * " << steps_frame << ")" << endl << "Current frame: " << iframe << endl;
		exit(1);
	}
	
	for (int j = 0; j < nAtoms; j++)
		{
			getline(fin, temp);
			ss << temp;
			//extern const int Num_info = 15
			for (int k = 0; k < Num_info; k++)
				ss >> atom[j][k];
			ss.clear();
			if (atom[j][0] != j+1)
				{
					cout << "Wrong atom ID!!\nCurrent frame: " << timestep/steps_frame << endl;
					output << "Wrong atom ID!!\nCurrent frame: " << timestep/steps_frame << endl;
					exit(1);
				}
		}
	for (int clear = 0; clear < Num_obs; clear++)	//clear information of obstacles
	getline(fin, temp);
	
	return atom;
	
}

// rcm[xyz]:para[012]
// vcm[xyz]:para[345]
// Rg,Re,Icm,theta:para[6789]
vector<double>  compute(const string label, const  vec_doub2 &atom)
{
	vector<double> temp(1,0);
	vector<double> a(dim,0);
	vector<double> b(dim,0);
	vector<double> c(dim,0);
	//cout << atom;exit(1);
	if(label == "MSD")
	{
		
	}
	else
	{
		for (int iAtoms = 1; iAtoms <= nAtoms; iAtoms++)
		{
			if (label == "Rg")
			{
				for (int k = 0; k < dim; k++)
				{
					double delta = atom[iAtoms][k] - atom[0][k];
					temp[0] += delta * delta;
				}
				/*double dx = atom[iAtoms][0] - atom[0][0];
				double dy = atom[iAtoms][1] - atom[0][1];
				temp[0] += dx * dx + dy * dy;	*/
			}
			
			else if (label == "Lcm")
				//L=r X v =x*vy - y*vx
				temp[0] += atom[iAtoms][0] * atom[iAtoms][4] - atom[iAtoms][1] * atom[iAtoms][3];			//Itotal
			else if (label == "Ang")
			{
				if ( iAtoms <= nAtoms - 2 )
				{
					for(int k = 0; k < dim; k++)
					{
						a[k] = atom[iAtoms][k];
						b[k] = atom[iAtoms+1][k];
						c[k] = atom[iAtoms+2][k];
					}
					temp[0] += rot2_angle(a, b, c);		//angle
				}
			}
			/*else if(label != "Re")
				{
					cout << "ERROR! Wrong label! -> analyse.cpp:23" << endl;	
					exit(1);
				}*/
			}
		//cout << " delta:" << temp[0] << endl;exit(1);
		if (label == "Rg")
		{
			temp[0] /= nAtoms;	
			temp[0] = sqrt(temp[0]);
		}
		else if (label == "Re")
		{
			for (int k = 0; k < dim; k++)
			{
				double delta = atom[1][k] - atom[nAtoms][k];
				temp[0] += delta * delta;
			}
			temp[0] = sqrt(temp[0]);
			/*double delx = atom[1][0] - atom[nAtoms][0];	
			double dely = atom[1][1] - atom[nAtoms][1];
			temp[0] = delx * delx + dely * dely;*/
		}
		else if (label == "Lcm")
			temp[0] -= atom[0][0] * atom[0][4] - atom[0][1] * atom[0][3];
		
		else if(label != "Ang")
		{
			cout << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
			output << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
			exit(1);
		}

	}
		return temp;
}

vec_doub2  compute(const string label, const vec_doub3 &atom)
{
	
	vec_doub2 vec_msd(max_frame+1, vec_doub(msd.size(),  0));
	if( label == "MSD")
	{
		for (int dt = 1; dt <= max_frame; dt++)	//cut[frames] [bits]
		{
			//msd
			for (int p = 0; p < msd.size(); p++)
			{
				int Tstart = 1;
				do{
					int Tstop = Tstart + dt;
					{
						for (int i = 0; i < dim; i++)
						{
							int imsd = msd[p];
							double delta = atom[Tstop][imsd][i] - atom[Tstart][imsd][i];
							vec_msd[dt][p] += delta * delta;
						}
					}
					Tstart++;
				} while ( Tstart < min ( max_frame, Num_frames - dt - 1 ) );
				vec_msd[dt][p] /= Tstart;
			}
		}
	}
	return vec_msd;
}
// rcm[xyz]:para[012]
// vcm[xyz]:para[345]
// Rg,Re,Icm,theta:para[6789]
vector<double> compute(string label, vec_doub2 atom, vector<double> para)
{
	vector<double> temp(1, 0);
	vector<double> a(2,0);
	vector<double> b(2,0);
	vector<double> c(2,0);
	for (int j = 0; j < nAtoms; j++)								
		{
			if (label == "Rg")
				{
					double dx = atom[j][0] - para[0];
					double dy = atom[j][1] - para[1];
					temp[0] += dx * dx + dy * dy;						//Rg
				}
			else if (label == "Lcm")
				temp[0] += atom[j][0] * atom[j][4] - atom[j][1] * atom[j][3];			//Itotal
			else if (label == "Ang")
				{
					if ( j < nAtoms - 2 )
						{
							for(int k = 0; k < 2; k++)
								{
									a[k] = atom[j][k];
									b[k] = atom[j+1][k];
									c[k] = atom[j+2][k];
								}
							temp[0] += rot2_angle(a, b, c);		//angle
						}
				}				
			else if(label != "Re")
				{
					cout << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
					output << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
					exit(1);
				}
		}
	
	if (label == "Rg")
		temp[0] /= nAtoms;								
	else if (label == "Re")
		{
			double delx = atom[0][0] - atom[nAtoms-1][0];	
			double dely = atom[0][1] - atom[nAtoms-1][1];
			temp[0] = delx * delx + dely * dely;
		}
	else if (label == "Lcm")
		temp[0] -= para[0] * para[4] - para[1] * para[3];		
	else if(label != "Ang")
		{
			cout << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
			output << "ERROR! Wrong label! -> dana.cpp:24" << endl;	
			exit(1);
		}
	return temp;
}

//angle of 2D
double rot2_angle(vector<double> a, vector<double> b, vector<double> c)
{
	int dim = 2;
	vector<double> ab(dim, 0);
	vector<double> bc(dim, 0);
	double dot = 0;
	double cross = 0;
	double mod_ab = 0;
	double mod_bc = 0;
	//if(a.size() != b.size() || a.size() != c.size() || a.size() != dim)
		//cout << "\n\"ERROR\": Dimension (\"analyser.h\":24) --> (Current Dimension) " << a.size() << " != " << dim << " ( Setup )" << endl;
	
	for (int i = 0; i < dim; i++)
	{
		ab[i] = b[i] - a[i];
		bc[i] = c[i] - b[i];
		dot += ab[i] * bc[i]; 
		mod_ab += ab[i]*ab[i];
		mod_bc += bc[i]*bc[i];
	}
	mod_ab = sqrt(mod_ab);
	mod_bc = sqrt(mod_bc);
	cross = ab[0]*bc[1] - ab[1]*bc[0];
	
	dot /= mod_ab * mod_bc;
	cross /= mod_ab * mod_bc;
	
	//return acos(dot);
	return asin(cross);
	
}

string time (string st, clock_t start)
{
	stringstream ss;
	string temp, str;
	clock_t stop = clock();		//#include <ctime>
	double Time = (double)(stop - start)/CLOCKS_PER_SEC;
	vector<int> inter(4,Time);
	inter[1] = inter[0]/3600;
	inter[2] = inter[0]/60%60;
	inter[3] = inter[0]%60;
	st = " \"" + st + "\": ";
	for (int i = 0; i < 3; i++)
	{
		ss << inter[i+1];
		ss >> str;  
		if (inter[i+1] < 10)
			st += "0" + str;    //using std::to_string;
		else
			st += str;
		if (i < 2)
			st += ":";
		ss.clear();
	}
	
	cout << st << " --> " << 1000 * md_dt * dstep * Num_frames/double(stop - start) << " Tau/ms" << endl;
	output << st << " --> " << 1000 * md_dt * dstep * Num_frames/double(stop - start) << " Tau/ms" << endl;
	return st;
}
