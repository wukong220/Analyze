#include <iostream>
#include <string>

#include "paras.h"

const int Num_info = 15;		//id type xu yu zu vx vy vz c_orient[1] c_orient[2] c_orient[3] c_orient[4] c_shape[1] c_shape[2] c_shape[3]

const int N_chain = 30;									//Polarization of single chain
const int Num_chains = 1;								//Number of the chains
const int Num_beeds = N_chain * Num_chains; 			//Number of beeds

const int dimension = 2;
const int Num_file = 20;
std::vector<int> closefiles{};				//closefiles
std::string finname;// = "003";				//empty or single input file
std::string foutname = "MSD.000_0.4_2.5_1.0_3.0.txt";		
std::string outname = "MSD.000.log";

const double md_dt = 0.001;
const int Num_frame = 35000;
const int dNM = 3000;
const int Max_frame = Num_frame - dNM;
const int framestep = 5000;

vector<int> files(3, Num_file);	

int main()
{
	output();
	return 0;
}