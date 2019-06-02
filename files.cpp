#include "files.h"
#include "paras.h"


//extern const int Num_file, Num_frame
LmpFile::LmpFile()
{
	stringstream ss, sl;
	m_NumFile = Num_file;
	m_NumFrame = Num_frame;
	m_Files = m_NumFile;
	m_head = "none";
	m_fnamebel = vector<vector<string> > (m_NumFile, vector<string>(2));
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
	for (int i = 0; i < m_NumFile; i++)
	{
		if (i < 9)
		{
			ss << "00" << i + 1 << "u.lammpstrj";
			sl << "00" << i + 1;
		}
		else if (i >= 9 && i < 100)
		{
			ss << "0" << i + 1 << "u.lammpstrj";
			sl << "0" << i + 1;
		}
		ss >> m_fnamebel[i][0];
		sl >> m_fnamebel[i][1];
		ss.clear();
		sl.clear();
	}
}

LmpFile::LmpFile(const string & finname)
{
	m_head = "none";
	stringstream ss, sl;
	if (finname != "\0")
	{
		m_NumFile = 1;
		m_NumFrame = Num_frame;
		m_Files = 1;
		m_fnamebel = vector<vector<string> > (m_NumFile, vector<string>(2));
		m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
		m_fnamebel[0][0] = finname + "u.lammpstrj";
		m_fnamebel[0][1] = "000";
		
	}
	else
	{
		m_NumFile = Num_file;
		m_NumFrame = Num_frame;
		m_Files = m_NumFile;
		m_fnamebel = vector<vector<string> > (m_NumFile, vector<string>(2));
		m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
		
		for (int i = 0; i < m_NumFile; i++)
		{
			if (i < 9)
			{
				ss << "00" << i + 1 << "u.lammpstrj";
				sl << "00" << i + 1;
			}
			else if (i >= 9 && i < 100)
			{
				ss << "0" << i + 1 << "u.lammpstrj";
				sl << "0" << i + 1;
			}
			ss >> m_fnamebel[i][0];
			sl >> m_fnamebel[i][1];
			ss.clear();
			sl.clear();
		}
	}
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = Num_frame;
	m_Files = m_NumFile;
	m_head = "none";
	m_fnamebel = fnamebel;
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel, const int a)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = a;
	m_Files = m_NumFile;
	m_head = "none";
	m_fnamebel = fnamebel;
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel, const vector<vector<int> > frames)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = frames.size();
	m_Files = m_NumFile;
	m_head = "none";
	m_fnamebel = fnamebel;
	m_frames = frames;
}

LmpFile::~LmpFile()
{
	
}

ostream & operator<<(ostream & os, const LmpFile & file)
{
	//os.setf(ios::adjustfield);
	cout << "Information: \n";
	for(int i = 0; i < file.m_head.size(); i++)
	{
		if ((file.m_head[i] >= 'A' && file.m_head[i] <= 'Z')|| file.m_head[i] == ':')
			continue;
		else
			cout << file.m_head[i];
	}
	cout << "\n\n";
	
	cout << "Effective Files: " << file.m_Files << endl;
	os << setw(25) << left << "Name ";
	os << setw(5) << "Label";
	os << " ";
	os << setw(7) << left << "Num";
	os << " ";
	os << setw(7) << left << "Max" << endl;
	for (int i = 0; i < file.m_NumFile; i++)
	{
		os << setw(25) << left << file.m_fnamebel[i][0] << " ";
		os << setw(5) << file.m_fnamebel[i][1];
		for (int k = 0; k < file.m_frames[i].size(); k++)
			os << setw(7) << left << file.m_frames[i][k] << " ";
		os << endl;
	}
	os << endl;
	
	return os;
}

vec_doub3 LmpFile::read_data(const int ifile, const vector<int> closefiles, ofstream &output)
{
	//input	
	//extern const int Num_info = 15; Num_beeds = N_chain * Num_chains; 
	vec_doub3 atom(m_NumFrame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0)));
	string error = "Right";
	int timestep = 0;
	string temp;
	stringstream ss;
	int Num_atoms = 1;
	
	ifstream fin(m_fnamebel[ifile][0]);
	if (m_fnamebel[0][1] == "000")
		m_Files = 1;
	
	for (int j = 0; j < closefiles.size(); j++)
	{
		if (ifile == closefiles[j] - 1)
			error = "\"CLOSE\": ";
	}
	
	if(!fin.is_open())
		error = "\"ERROR\": Cannot open ";
	
	//error information
	if(error != "Right")
	{
		cout << error << m_fnamebel[ifile][0] << endl;
		output << error << m_fnamebel[ifile][0] << endl;		//for output
		
		m_Files--;
		m_fnamebel[ifile][1] = "  ";
		
		m_frames[ifile][0] = 0;
		m_frames[ifile][1] = 0;
		
		error = "Right";
		return atom;
	}
	else
	{
		cout << "\"Opening\": " << m_fnamebel[ifile][0] << "……" << endl;
		output << "\"Opening\": " << m_fnamebel[ifile][0] << "……" << endl;
	}
	
	
	for (int i = 0; i < m_NumFrame; i++)
	{
		for (int clear = 0; clear < 2; clear++)			//the head
			getline(fin, temp);
		ss << temp;
		ss >> timestep;
		if (timestep != i * framestep)		//extern const int framestep = 5000;
		{
			error = "\"ERROR\": TIMESTEP/FRAME(files.cpp:96) -> ";
			cout << error << timestep << " != " << i * framestep << " (" << i << " * " << framestep << ")" << endl;
			output << error << timestep << " != " << i * framestep << " (" << i << " * " << framestep << ")" << endl;
			m_Files--;	
			m_fnamebel[ifile][1]= "000";
			m_frames[ifile][0] = i - 1 ;					//frames[Num_frames, max_frames]
			//m_frames[ifile][1] = m_frames[ifile][0] - dNM;
			break;
		}
		ss.clear();
		
				//extern const Num_beeds = N_chain * Num_chains
		m_head = read_atoms(fin, i, Num_beeds, atom);
		//read_type(fin, i, type, atom);
	}
	fin.close();
	
	//extern const int dNM = 3000;
	m_frames[ifile][1] = m_frames[ifile][0] - dNM;	//frames[Num_frames, max_frames]
	if (m_Files == 0 && error == "Right")
		m_Files = 1;								//single file	
	//else if (error != "Right")					
	//	error = "Right";							//initialize of the error information
	return atom;
}

//calcucate position of the center of mass 
vec_doub3 LmpFile::center(const int ifile, const int nChain, const vec_doub3 &vec)
{
	//extern int dimension = 2
	//extern double mass = 1.0
	int NumChains = vec[0].size() / nChain;
	vec_doub3 rCM(m_NumFrame, vector<vector<double> >(NumChains, vector<double>(dimension + 1,0)));
	for (int i = 0; i < m_frames[ifile][0]; i++)			
	{
		for (int j = 0; j < NumChains; j++)
		{
			for (int k = nChain * j; k < nChain * (j + 1); k++)
			{
				rCM[i][j][0] += vec[i][k][2] * mass;		//rCm[iframe][jchain][x, y, z]
				rCM[i][j][1] += vec[i][k][3] * mass;
				rCM[i][j][2] += vec[i][k][4] * mass;	
				//cout << vec[i][k][2] << " " << vec[i][k][3] << " " << endl;
			}
			double TotMass = nChain * mass;
			rCM[i][j][0] /= TotMass;
			rCM[i][j][1] /= TotMass;
			rCM[i][j][2] /= TotMass;
			//cout << rCM[i][j][0] << " " << rCM[i][j][1] << " " << rCM[i][j][2] << endl << endl;
		}
	}
	
	return rCM;
}

vec_doub3 LmpFile::msd_ave(const int ifile, const vec_doub3 vec, vector<vector<int> > &count, vec_doub3 &msd)
{
	//extern int Max_frame; 
	//vec_doub3 msd(Max_frame, vector<vector<double> >(num, vector<double>((dimension + 1) * m_NumFile + 1, 0)));
	//Num_chains
	int num = vec[0].size();	//Num_chains
	for (int dt = 1; dt <= m_frames[ifile][1]; dt++)
	{
		for(int Tstart = 0; Tstart < min(m_frames[ifile][1], m_frames[ifile][0] - dt); Tstart++)
			{
				int Tstop = Tstart + dt;
				for(int i = 0; i < num; i++)
				{
					//extern int dimension = 2
					int j = (dimension + 1) * ifile + 1;
					count[ifile+1][dt-1]++;
					msd[dt-1][i][j] += (vec[Tstop][i][0] - vec[Tstart][i][0])*(vec[Tstop][i][0] - vec[Tstart][i][0]); 
					msd[dt-1][i][j+1] += (vec[Tstop][i][1] - vec[Tstart][i][1])*(vec[Tstop][i][1] - vec[Tstart][i][1]);
					msd[dt-1][i][j+2] = msd[dt-1][i][j] + msd[dt-1][i][j+1];
					if (m_fnamebel[ifile][1] != "000")
					{
						if (m_fnamebel[ifile][1] != "  ")
							count[0][dt-1]++;
						if (Tstart == (min(m_frames[ifile][1], m_frames[ifile][0] - dt)-1))
						{
							if (m_frames[ifile][1] == Max_frame && m_frames[ifile][0] == Num_frame)
							{	
								//just for test
								//msd[dt-1][i][(dimension + 1) * Num_file + 1] += msd[dt-1][i][j+2];
								//test++;
								msd[dt-1][i][j] /= count[ifile+1][dt-1];
								msd[dt-1][i][j+1] /= count[ifile+1][dt-1];
								msd[dt-1][i][j+2] = msd[dt-1][i][j] + msd[dt-1][i][j+1];
								msd[dt-1][i][0] = (msd[dt-1][i][0] * (count[0][Max_frame]) + msd[dt-1][i][j+2]) / (count[0][Max_frame] + 1);
							}
							if (dt == Max_frame)
								count[0][Max_frame]++;
						}
					}
					else if (m_fnamebel[ifile][1] != "  " && Tstart == (min(m_frames[ifile][1], m_frames[ifile][0] - dt)-1))
					{
						msd[dt-1][i][j] /= count[ifile+1][dt-1];
						msd[dt-1][i][j+1] /= count[ifile+1][dt-1];
						msd[dt-1][i][j+2] = msd[dt-1][i][j] + msd[dt-1][i][j+1];
					}
					
					/*if (m_fnamebel[ifile][1] != "000" && m_fnamebel[ifile][1] != "  ")
						count[0][dt-1]++;
					//extern int Max_frame; Num_frame
					if(Tstart == (min(Max_frame, Num_frame - dt)-1) && m_fnamebel[ifile][1] != "000")
					{
						msd[dt-1][i][0] += msd[dt-1][i][j] + msd[dt-1][i][j+1];
						
					}*/
						
					/*cout << Tstart << " " << dt << " " << Tstop << " " 
					<< (vec[Tstop][i][0] - vec[Tstart][i][0])*(vec[Tstop][i][0] - vec[Tstart][i][0])+(vec[Tstop][i][1] - vec[Tstart][i][1])*(vec[Tstop][i][1] - vec[Tstart][i][1]) << " "
					<< msd[dt-1][i][2] << " " << msd[dt-1][i][2]/count[0][dt-1] << endl;*/
				}
			}
			
			//cout << msd[dt-1][0][2]/count[0][dt-1] << endl;
	}
	return msd;
}

//output
void LmpFile::out_msd(const string foutname, const vector<vector<int> > count, const vec_doub3 vec)
{
	ofstream fout(foutname);
	fout << "time ";
	cout << "time "; 
	output << "time ";
	for (int i = 0; i < m_NumFile; i++)
	{
		cout << "msd[" << m_fnamebel[i][1] << "] ";
		output << "msd[" << m_fnamebel[i][1] << "] ";
		fout << "msd[" << m_fnamebel[i][1] << "] ";
		
	}
	cout << "ave test\n";
	output << "ave test\n";
	fout << "ave test\n";	
	
	double time;
	int num = vec[0].size();
	//extern int Max_frame = 20000;int framestep = 5000; double md_dt = 0.001;
	for (int dt = 1; dt <= Max_frame; dt++)
	{
		time = dt * framestep * md_dt;
		cout << time << " ";
		output << time << " ";
		fout << time << " ";
		
		for (int ifile = 0; ifile < m_NumFile; ifile++)
		{
			if (m_fnamebel[ifile][1] == "  ")
				break;
			for(int i = 0; i < num; i++)
			{	
				int j = (dimension + 1) * ifile + 1; 
				if (m_fnamebel[ifile][1] == "000" && dt >= m_frames[ifile][1])	//suplement
				{
					cout << "nan ";
					output << "nan ";
					fout << "nan ";
				}
				else
				{
					cout << vec[dt-1][i][j+2] << " ";
					output << vec[dt-1][i][j+2] << " ";
					fout << vec[dt-1][i][j+2] << " ";
				}	
				if (ifile == m_NumFile - 1)
				{
					cout << vec[dt-1][i][0];		// << " " << vec[dt-1][i][(dimension + 1) * Num_file + 1]/count[0][dt-1];
					output << vec[dt-1][i][0];		// << " " << vec[dt-1][i][(dimension + 1) * Num_file + 1]/count[0][dt-1];
					if (m_Files != 1)
						fout << vec[dt-1][i][0]; 	// << " " << vec[dt-1][i][(dimension + 1) * Num_file + 1]/count[0][dt-1];
				}
			}
		}
		cout << endl;
		output << endl;
		fout << endl;
	}
	fout.close();
	//reminding
	//files

}

//read atom information -> atom[iframe][jatom][kinfo]
string read_atoms(ifstream &fin, int i, int nAtom, vec_doub3 &vec)
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
	Num_obs = Num_atoms - nAtom;				//for clearing obstacles
	
	for (int clear = 0; clear < 5; clear++)			
		getline(fin, temp);
	head = temp;								//the head
	
	for (int j = 0; j < nAtom; j++)
	{
		getline(fin, temp);
		ss << temp;
		//extern const int Num_info = 15
		for (int k = 0; k < Num_info; k++)
			ss >> vec[i][j][k];
		ss.clear();
	}

	for (int clear = 0; clear < Num_obs; clear ++)	//clear information of obstacles
		getline(fin, temp);
	return head;
}
