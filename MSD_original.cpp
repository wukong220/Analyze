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
		
		for (int i = 0; i < frames[ifile][0]; i++)			//position of the center of mass
		{
			for (int j = 0; j < Num_chains; j++)
			{
				for (int k = N_chain * j; k < N_chain * (j + 1); k++)
				{
					rCM[i][j][0] += atom[i][k][2];		//i frame j atom x or y
					rCM[i][j][1] += atom[i][k][3];
					//cout << atom[i][k][2] << " " << atom[i][k][3] << " " << endl;
				}
				rCM[i][j][0] /= N_chain;
				rCM[i][j][1] /= N_chain;
				//cout << rCM[i][j][0] << " " << rCM[i][j][1] << endl << endl;
			}
		}
		//cout << frames[ifile][0] << " " << frames[ifile][1] << " " << endl;
		for (dt = 1; dt <= frames[ifile][1]; dt++)
		{
			for(Tstart = 0; Tstart < min(frames[ifile][1], frames[ifile][0] - dt); Tstart++)
				{
					Tstop = Tstart + dt;
					
					for(int i = 0; i < Num_chains; i++)
					{
						int k = dimension * ifile + 1;
						count[ifile+1][dt-1]++;
						msd[dt-1][i][k] += (rCM[Tstop][i][0] - rCM[Tstart][i][0])*(rCM[Tstop][i][0] - rCM[Tstart][i][0]); 
						msd[dt-1][i][k+1] += (rCM[Tstop][i][1] - rCM[Tstart][i][1])*(rCM[Tstop][i][1] - rCM[Tstart][i][1]);
						if (filename[ifile][1] != "000")
							count[0][dt-1]++;
						if(Tstart == (min(Max_frame, Num_frame - dt)-1) && filename[ifile][1] != "000")
							msd[dt-1][i][0] += msd[dt-1][i][k] + msd[dt-1][i][k+1];
						/*cout << Tstart << " " << dt << " " << Tstop << " " 
						<< (rCM[Tstop][i][0] - rCM[Tstart][i][0])*(rCM[Tstop][i][0] - rCM[Tstart][i][0])+(rCM[Tstop][i][1] - rCM[Tstart][i][1])*(rCM[Tstop][i][1] - rCM[Tstart][i][1]) << " "
						<< msd[dt-1][i][2] << " " << msd[dt-1][i][2]/count[0][dt-1] << endl;*/
					}
				}
				//cout << msd[dt-1][0][2]/count[0][dt-1] << endl;
		}
		for (int i = 0; i < frames[ifile][0]; i++)
		{
			for (int j = 0; j < Num_chains; j++)
			{
				rCM[i][j][0] = 0;
				rCM[i][j][1] = 0;
			}
		}
	}
	if (files[2] == 0)
		files[2] = 1;								//single file
	
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
				if (filename[ifile][1] == "000" && iframe >= frames[ifile][1])
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