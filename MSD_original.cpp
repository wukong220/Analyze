//msd
//ave 
//files
//MSD of center of mass

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>  


int main() 
{
		

		
	//output 
	//cout << 1 * framestep * md_dt<< " " << msd[0][0][2]/count[0][1] << endl;
	ofstream fout(foutname);
	fout << "time ";
	cout << "time "; 
	output << "time ";
	for (int i = 0; i < files[1]; i++)
	{
		cout << "msd[" << filename[i][1] << "] ";
		output << "msd[" << filename[i][1] << "] ";
		fout << "msd[" << filename[i][1] << "] ";
		
	}
	cout << "ave\n";
	output << "ave\n";
	fout << "ave\n";	

	
	for (int iframe = 0; iframe < Max_frame; iframe++)
	{
		time = (iframe + 1) * framestep * md_dt;
		cout << time << " ";
		output << time << " ";
		fout << time << " ";
		
		for (int ifile = 0; ifile < files[1]; ifile++)
		{
			int j = ifile * dimension + 1; 
			for(int i = 0; i < Num_chains; i++)
			{	
				double MSD = msd[iframe][i][j] + msd[iframe][i][j+1];
				if (filename[ifile][1] == "000" && iframe >= frames[ifile][1])//suplement
				{
					cout << "nan ";
					output << "nan ";
					fout << "nan ";
				}
				else if (filename[ifile][1]!= "  ")
				{
					cout << MSD/(count[ifile+1][iframe])<< " ";
					output << MSD/(count[ifile+1][iframe])<< " ";
					fout << MSD/(count[ifile+1][iframe])<< " ";
				}
				//cout << msd[iframe][i][j] << " " << msd[iframe][i][j+1] << " ";
				if (ifile == files[1] - 1)
				{
					cout << msd[iframe][i][0] / count[0][iframe] << " ";
					output << msd[iframe][i][0] / count[0][iframe] << " ";
					if (files[1] != 1)
						fout << msd[iframe][i][0] / count[0][iframe] << " ";
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
	cout << "\"Writing\": " << foutname << endl << "\"Output\": " << outname << endl;
	output << "\"Writing\": " << foutname << endl << "\"Output\": " << outname << endl;
	output.close();
	
	return 0;
}