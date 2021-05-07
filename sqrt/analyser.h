#ifndef ANALYSER_H
#define ANALYSER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>


using namespace std;
typedef vector<double> vec_doub;
typedef vector<vec_doub>  vec_doub2;
typedef vector<vec_doub2> vec_doub3;
typedef vector<vec_doub3> vec_doub4;


vec_doub3 operator+=(vec_doub3 &vec0, const vec_doub3 vec1);
ostream & operator<<(ostream & os, vec_doub &vec);
ostream & operator<<(ostream & os, vec_doub2 &vec);
ostream & operator<<(ostream & os, vec_doub3 &vec);
ostream & operator<<(ostream & os, vector<string> &vec);
ostream & operator<<(ostream & os, vector<int> &vec);

//show information
vector<string> show(string &logname, string &finname, vector<string> &label, string &foutname, int &Num_chains, int &N_chain, int &Num_beeds, int &Num_frames);
string read_atoms(ifstream &, int, int, vec_doub3 &); 	// fin, iframe, nAtoms, atom[i][j][k]closefile[i]
vec_doub2 read_data(ifstream &fin, vec_doub2 &atom, int iframe);
vector<double>  compute(const string label, const vec_doub2 &atom);
vec_doub2 compute(const string label, const vec_doub3 &atom);
double rot2_angle(vector<double> a, vector<double> b, vector<double> c);


class out
{
private:
	vector<string> m_para;
	vector<int> m_pCom;
	vector<int> m_outstyle;
	
public:
	out();
	out(vector<string> &outdata);
	~out();
	vector<string> paras(){return m_para;};
	vector<int> component(){return m_pCom;};
	friend ostream & operator<<(ostream & os, const out & file);
	//void output();
	void show();
	
};



#endif
