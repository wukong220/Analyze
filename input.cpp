#include "input.h"

void input()
{
	for(int ifile = 0; ifile < files[1]; ifile++)
	{
		//input	
		ifstream fin(filename[ifile]);
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
			cout << error << filename[ifile] << endl;
			output << error << filename[ifile] << endl;
			files[2]--;
			label[ifile] = "  ";
			frames[ifile][0] = 0;
			frames[ifile][1] = 0;
			error = "Right";
			continue;
		}
		else
		{
			cout << "\"Opening\": " << filename[ifile] << "……" << endl;
			output << "\"Opening\": " << filename[ifile] << "……" << endl;
		}
			
			
		int timestep = 0;
		for (int i = 0; i < Num_frame; i++)
		{
			for (int clear = 0; clear < 2; clear++)			//the head
				getline(fin, temp);
			ss << temp;
			ss >> timestep;
			//cout << temp << " !!! ";
			if (timestep != i * framestep)
			{
				//cout << temp << "!!!";
				error = "\"ERROR\": TIMESTEP/FRAME(Line:123) -> ";
				//fout << error << endl;
				cout << error << timestep << " != " << i * framestep << " (" << i << " * " << framestep << ")" << endl;
				output << error << timestep << " != " << i * framestep << " (" << i << " * " << framestep << ")" << endl;
				files[2]--;	
				label[ifile] = "000";
				frames[ifile][0] = i - 1 ;					//frames
				break;
			}
			ss.clear();
			
			for (int clear = 0; clear < 2; clear++)			//the head
				getline(fin, temp);
			ss << temp;
			ss >> Num_atoms;								//Number of atoms
			Num_obs = Num_atoms - Num_beeds;		
			ss.clear();
			
			for (int clear = 0; clear < 5; clear++)			//the head
				getline(fin, temp);
			
			for (int j = 0; j < Num_beeds; j++)
				{
					getline(fin, temp);
					stringstream input(temp);
					for (int k = 0; k < Num_info; k++)
						input >> chain[i][j][k];
				}

			for (int clear = 0; clear < Num_obs; clear ++)	//the tail
				getline(fin, temp);
		}
		fin.close();
		
		if (files[2] == 0 && error == "Right")
			files[2] = 1;								//single file	
		else if (error != "Right")					
		{
			error = "Right";
			//continue;
		}
		frames[ifile][1] = frames[ifile][0] - dNM;
}

