#include "files.h"
#include "paras.h"
#include <iostream>
#include <iomanip>

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
	cout << "Information: \n";
	for(int i = 0; i < file.m_head.size(); i++)
	{
		if ((file.m_head[i] >= 'A' && file.m_head[i] <= 'Z')|| file.m_head[i] == ':')
			continue;
		else
			cout << file.m_head[i];
	}
	cout << endl;
	return os;
}

vector<vector<vector<double> > > LmpFile::read(const int ifile, const vector<int> closefiles)
{
	//input	
	//extern const int Num_info = 15; Num_beeds = N_chain * Num_chains; 
	vector<vector<vector<double> > > atom(m_NumFrame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0)));
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
			break;
		}
		ss.clear();
		
		//extern const int dNM = 3000;
		m_frames[ifile][1] = m_frames[ifile][0] - dNM;	//frames[Num_frames, max_frames]
		//extern const Num_beeds = N_chain * Num_chains
		m_head = read_atoms(fin, i, Num_beeds, atom);
		//read_type(fin, i, type, atom);
	}
	fin.close();

	if (m_Files == 0 && error == "Right")
		m_Files = 1;								//single file	
	//else if (error != "Right")					
	//	error = "Right";							//initialize of the error information

	return atom;
}

//calcucate the center of mass 
vector<vector<vector<double> > > center(const vector<vector<vector<double> > >)























//read atom information -> atom[iframe][jatom][kinfo]
string read_atoms(ifstream &fin, int i, int nAtom, vector<vector<vector<double> > > &atom)
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
			ss >> atom[i][j][k];
		ss.clear();
	}

	for (int clear = 0; clear < Num_obs; clear ++)	//clear information of obstacles
		getline(fin, temp);
	return head;
}
