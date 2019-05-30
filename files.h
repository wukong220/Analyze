#ifndef FILES_H
#define FILES_H

#include <vector>
#include <string>

using namespace std;

class LmpFile
{
private:
	int m_NumFile;
	int m_NumFrame;
	int m_Files;
	string m_head;
	vector<vector<string> > m_fnamebel;	//filename[ifile][name,label]
	vector<vector<int> > m_frames;		//frames[ifile][Num_frame, Max_frame]
	
public:
	//constructors and destructors
	LmpFile();
	LmpFile(const string &);
	LmpFile(const vector<vector<string> >);
	LmpFile(const vector<vector<string> >, const int);
	LmpFile(const vector<vector<string> >, const vector<vector<int> >);
	~LmpFile();
	friend ostream & operator<<(ostream & os, const LmpFile & file);
	int files(){return m_Files;};
	//ifile, atom, center
	vector<vector<vector<double> > > read(const int, const vector<int>);
	vector<vector<vector<double> > > center(const vector<vector<vector<double> > >);	

};

string read_atoms(ifstream &, int , int, vector<vector<vector<double> > > &); // fin, iframe, nAtoms, atom[i][j][k]


#endif