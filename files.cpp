#include "files.h"
#include "paras.h"
#include <iostream>

LmpFile::LmpFile()
{
	m_NumFile = Num_file;
	m_NumFrame = Num_frame;
	m_Files = m_NumFile;
	m_fnamebel = vector<vector<string> > (m_NumFile, vector<string>(2));
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = Num_frame;
	m_Files = m_NumFile;
	m_fnamebel = fnamebel;
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel, const int a)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = a;
	m_Files = m_NumFile;
	m_fnamebel = fnamebel;
	m_frames = vector<vector<int> >(m_NumFile, vector<int>(2, m_NumFrame));
}

LmpFile::LmpFile(const vector<vector<string> > fnamebel, const vector<vector<int> > frames)
{
	m_NumFile = fnamebel.size();
	m_NumFrame = frames.size();
	m_Files = m_NumFile;
	m_fnamebel = fnamebel;
	m_frames = frames;
}

LmpFile::~LmpFile()
{
	
}

vector<vector<vector<double> > > LmpFile::read_xyz(const int ifile, const vector<int> closefiles)
{
	//input	
	//extern const int Num_info = 15; extern const int Num_beeds = N_chain * Num_chains; 
	vector<vector<vector<double> > > atom(m_Num_frame, vector<vector<double> >(Num_beeds, vector<double>(Num_info,0)));
	string error = "Right";
	int timestep = 0;
	string temp;
	stringstream ss;
	int Num_atoms = 1;
	int Num_obs = 1;
	
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
		cout << "\"Opening\": " << fnamebel[ifile][0] << "……" << endl;
		output << "\"Opening\": " << fnamebel[ifile][0] << "……" << endl;
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
			mfnamebel[ifile][1]= "000";
			m_frames[ifile][0] = i - 1 ;					//frames[Num_frames, max_frames]
			break;
		}
		ss.clear();
		//extern const int dNM = 3000;
		m_frames[ifile][1] = frames[ifile][0] - dNM;	//frames[Num_frames, max_frames]
		
		for (int clear = 0; clear < 2; clear++)			//the head
			getline(fin, temp);
		ss << temp;
		ss >> Num_atoms;								//Number of atoms
		Num_obs = Num_atoms - Num_beeds;				//clear information of the obstacles
		ss.clear();
		
		for (int clear = 0; clear < 5; clear++)			//the head
			getline(fin, temp);
		
		for (int j = 0; j < Num_beeds; j++)
			{
				getline(fin, temp);
				stringstream input(temp);
				for (int k = 0; k < Num_info; k++)
					input >> atom[i][j][k];
			}

		for (int clear = 0; clear < Num_obs; clear ++)	//the tail
			getline(fin, temp);
	}
	fin.close();
	

	if (m_Files == 0 && error == "Right")
		m_Files = 1;								//single file	
	//else if (error != "Right")					
	//	error = "Right";							//initialize of the error information

	return atom;
}

