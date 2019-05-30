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
	vector<vector<string> > m_fnamebel;	//filename[ifile][name,label]
	vector<vector<int> > m_frames;		//frames[ifile][Num_frame, Max_frame]
	
public:
	//constructors and destructors
	LmpFile();
	LmpFile(const vector<vector<string> >);
	LmpFile(const vector<vector<string> >, const int);
	LmpFile(const vector<vector<string> >, const vector<vector<int> >);
	~LmpFile();
	void show();
	int files(){return m_Files;};
	//ifile, atom, center
	vector<vector<vector<double> > > read_xyz(const int, const vector<int>);
	vector<vector<vector<double> > > center_mass(const vector<vector<vector<double> > >);	
	

};

#endif