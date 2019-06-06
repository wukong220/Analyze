#include "paras.h"

inline bool input(int &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if (str == "\0") 
	{
		return false;
	}
	else
	{
		ss << str;
		ss >> x;
		return true;
	}
	//cout << "String: " << x << endl;
}

inline bool input(string &x)
{
	stringstream ss;
	string str;
	getline(cin, str);
	if (str == "\0") 
	{
		return false;
	}
	else
	{
		ss << str;
		ss >> x;
		return true;
	}
	//cout << "String: " << x << endl;
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

vec_doub3 operator+=(vec_doub3 &vec0, const vec_doub3 vec1)
{
	for (int i = 0; i < vec0.size(); i++)
	{
		if (vec1.size() == vec0.size())
		{
			for (int j = 0; j < vec0[i].size(); j++)
			{
				if (vec1[i].size() == vec0[i].size())
				{
					for (int k = 0; k < vec0[i][j].size(); k++)
					{
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

//os << vec
ostream & operator<<(ostream & os, vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<double> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<string> &vec)
{
	for (int i = 0; i < vec.size(); i++)
		os << vec[i] << " ";
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<int> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<double> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<vector<string> > &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			os << vec[i][j] << " ";
		os << endl;
	}
	os << endl;
	return os;
}

ostream & operator<<(ostream & os, vec_doub3 &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		//extern const int framestep
		os << i * framestep << " :" << endl;
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

//show information
vector<string> show(string &logname, string &foutname, int &Num_chains, int &N_chain, int &Num_beeds, int &Max_frame)
{	
	string str;
	int num;
	cout << "\"Log file name( \'MSD." << logname << ".log\' for default ): \" \n";
	//output << "\"Log file name( \'" << logname << ".MSD.log\' for default ): \" \n";
	input(str);
	logname = "MSD." + str + ".log";
	//cout << logname << endl;
	output.open(logname);
	
	cout << "\n\"Number of files( \'" << Num_file << "\' for default ): \"\n";
	output << "\n\"Number of files( \'" << Num_file << "\' for default ): \"\n";
	input(Num_file);
	vector<string> finname(Num_file); //constructor
	cout << "\"Input file name( \'***\' for default, without \'u.lammpstrj\' ):\" \n";
	for (num = 0; num < Num_file; num++)
	{
		if(!input(finname[num]))
			break;
	}
	if (num != 0)
		Num_file = num; 
	finname.resize(Num_file);
	cout << "Number of files: " << finname.size() << endl;
	
	//LmpFile Files(finname);
	//cout << Files;
	//cin.get();
	
	cout << "\n\"Output txt file name( \'MSD." << foutname << ".txt\' for default ): \" \n";
	output << "\n\"Output txt file name( \'MSD." << foutname << ".txt\' for default ): \" \n";
	input(str);
	foutname = "MSD." + str + ".txt";
	//cout << foutname << endl;
	
	cout << "\ndimension = " << dimension << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nframestep = " << framestep << ";\n\n"; //default information
	output << "dimension = " << dimension << ";\nmass =" << mass << ";\nmd_dt = " << md_dt << ";\nframestep = " << framestep << ";\n\n";
	cout << "\"Number of chains( \'" << Num_chains << "\' for default ): \"\n";
	output << "\"Number of chains( \'" << Num_chains << "\' for default ): \"\n";
	input(Num_chains);
	cout << "\"Number of atoms( \'" << N_chain << "\' for single chain default ): \"\n";
	output << "\"Number of atoms( \'" << N_chain << "\' for single chain default ): \"\n";
	input(N_chain); 
	Num_beeds = N_chain * Num_chains;
	
	cout << "\"Number of frames( \'" << Num_frame << "\' for default ): \"\n";
	output << "\"Number of frames( \'" << Num_frame << "\' for default ): \"\n";
	input(Num_frame);
	cout << "\"Frames to delete( \'" << dNM << "\' for default ): \"\n";
	output << "\"Frames to delete( \'" << dNM << "\' for default ): \"\n";
	input(dNM);
	Max_frame = Num_frame - dNM;
	
	return finname;
}
//for test