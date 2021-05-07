#include "./analyser.h"


int Num_files = 1;
const string fname = "000";						//eg. "001" -> 001u.lammpstrj
const string str = "Title";
const int Num_chain = 1;
const int nAtoms = 80;
const int dim = 3;
const double mass = 1.0;
int frames = 1000;						//tau = steps_frame * frames


vector<int> cut = {10,1560};	//cut[frames] [bits]
const double md_dt = 0.001;
const int steps_frame = 10000;
const int Num_frames = frames/cut[0];

const double dstep = cut[0] * steps_frame;
const int max_frame = Num_frames/2;

const int Num_info = 8;
vector<string> finname(Num_files);	//	filesname
vector<string> outdataA = {"Rg", "Re", "Lcm", "Ang"}; //per frame
vector<string> outdataB = {"MSD"};	 	//all frames
vector<string> outstyle = {"cut"};		//output style
vector<int> msd = {0};	//{0,1,nAtoms,nAtoms/2}
vector<int> pCom= {1,1,1,1};
vector<string> logname;	
ofstream fout[5];		//Rg, Re, Lcm, Ang
ofstream output;

clock_t start0 = clock();		//start time
string time (string st, clock_t start = start0);
#include "./analyser.cpp"
//0th information of all vector is RESERVED
int main() 
{
	string temp;
	stringstream ss;
	string head;
	int timestep;
	int Num_obs = 1;
	int Num_atoms = 1;
	//filename
	string logname =  "outdata." + str + ".log";
	output.open(logname);
	if (fname == "" || fname == "000")
		for (int i = 0; i < Num_files; i++)
		{
			ss << setw(3) << setfill('0') << i+1 << "u.lammpstrj";
			ss >> finname[i];
			ss.clear();
		}
	else
	{
		finname[0] = fname;
		Num_files = 1;
	}
	//Atom[ifile] [iframe+1] [iAtom+1] [x|y|z|...]   get  CM_info[rcm(3)|vcm(3)] while iAtom = 0
	vector<string> outdata = outdataA;
	vec_doub4 Atoms(Num_files, vec_doub3(Num_frames+1, vec_doub2(nAtoms+1, vec_doub(dim*2, 0))));
	vec_doub4 paraA;
	//[Rg|Re|Lcm|Ang] [jfile+1] [iframe+1] [Px|Py|Pz|...]  
	
	//paras for output

	outdata.insert(outdata.end(), outdataB.begin(), outdataB.end());
	if( outdataA.size() && outdataA.size() != pCom.size() ){
		cout << "\"ERROR\": outdataA is wrongly set !  -> analyser.h:44" << endl;
		output << "\"ERROR\": outdataA is wrongly set !  -> analyser.h:44" << endl;
		exit(1);
	}
	else if(!outdataB.size()){
		cout << "\"ERROR\": outdata is NULL  -> analyser.h:44,45" << endl;
		output << "\"ERROR\": outdataA is wrongly set !  -> analyser.h:44" << endl;
		exit(1);
	}
	

	for (int k = 0; k < outdata.size(); k++)
	{
		string foutname = outdata[k] + "." + str + ".txt";
		
		fout[k].open(foutname, ios::binary);
		fout[k] << "Analyse from dana.cpp: \n" << "Num_files = " << Num_files << "; nAtoms = " << nAtoms  << "; steps_frame  = " << steps_frame  << " * " << cut[0] << " (for cut[0])"  << "; \nmd_dt = "<< md_dt << "; RunTime = " << Num_frames << " * " << steps_frame  << " (Num_frames * steps_frame )" <<  endl;
		fout[k] << "time\t";
		
		if (k < outdataA.size())
		{
			paraA.push_back(vec_doub3(Num_files+1, vec_doub2(Num_frames+1,vector<double>(pCom[k],0))));
			for (int j = 0; j <= Num_files; j++)
			{
				for (int p = 0; p < pCom[k]; p++)
				{
					if (j == 0)
						fout[k] << outdata[k] << "[Fave][P" << setw(3) << setfill('0') << p <<"]\t" ;
					else 
						fout[k] << outdata[k] << "[F" << setw(3) << setfill('0') << j << "][P" << setw(3) << setfill('0') << p <<"]\t" ;
				}
			}
		}
		else
		{
			if(!msd.size())
				msd.push_back(0);
			paraA.push_back(vec_doub3(Num_files+1, vec_doub2(Num_frames+1,vector<double>(msd.size(),0))));
			for (int j = 0; j <= Num_files; j++)
			{
				for (int p = 0; p < msd.size(); p++)
				{
					if (j == 0)
						fout[k] << outdata[k] << "[Fave][P" << setw(3) << setfill('0') << msd[p] <<"]\t";
					else 
						fout[k] << outdata[k] << "[F" << setw(3) << setfill('0') << j << "][P" << setw(3) << setfill('0') << msd[p] <<"]\t" ;
				}
			}
		}
		fout[k] << endl; // << setiosflags(ios::left) << setw(10) << setfill(' ');
	}
	//information -> show()
	cout << "Special WARNNING: 0th information of all vector is RESERVED " << endl;
	cout << "Analyse from dana.cpp: \n" << "Num_files = " << Num_files << "; nAtoms = " << nAtoms  << "; steps_frame  = " << steps_frame  << " * " << cut[0] << " (for cut[0])"  << "; \nmd_dt = "<< md_dt << "; RunTime = " << Num_frames << " * " << steps_frame  << " (Num_frames * steps_frame )" <<  endl;
	output << "Special WARNNING: 0th information of all vector is RESERVED \nAnalyse from dana.cpp: \nNum_files = " << Num_files << "; nAtoms = " << nAtoms  << "; steps_frame  = " << steps_frame  << " * " << cut[0] << " (for cut[0])"  << "; \nmd_dt = "<< md_dt << "; RunTime = " << Num_frames << " * " << steps_frame  << " (Num_frames * steps_frame )" <<  endl;
	//style of output
	cout.setf(ios::left, ios::adjustfield); 
	cout.width(10);
	cout.fill(' ');
	
	for (int ifile = 0; ifile < Num_files; ifile++)
	{
		int jfile = ifile + 1;
		
		clock_t start = clock();
		ifstream fin(finname[ifile], ios::binary);
		cout << "\ndata from " << finname[ifile] << ": "<< endl;
		output << "\ndata from " << finname[ifile] << ": "<< endl;
		if ( outdataA.size() ){
			cout << "time(dt = " << dstep * md_dt << ")\t\t" << outdataA << endl;
			output << "time(dt = " << dstep * md_dt << ")\t\t" << outdataA << endl;
		}
			
		if(!fin.is_open()) 
		{
			cout << "\"ERROR\": Cannot open " << finname[ifile] << "--> analyse.cpp:22";
			output << "\"ERROR\": outdataA is wrongly set !  -> analyser.h:44" << endl;
			exit(1);
		}

		for (int iframe = 1; iframe <= Num_frames; iframe++)//for md_dt
		{
			//read_data
			for (int clear = 0; clear < 2; clear++)			//the head
			getline(fin, temp);
			auto pos = fin.tellg();
			ss << temp;
			ss >> timestep;
			ss.clear();

			if(iframe==1)
			{
				for (int clear = 0; clear < 2; clear++)		//clear
				getline(fin, temp);
				ss << temp;										
				ss >> Num_atoms;							//Number of atoms
				if( Num_atoms != nAtoms)
				{
					string error = "\"ERROR\": nAtoms(analyse.cpp:17) -> ";
					cout << error << "(Current Read) " << Num_atoms << " != " << nAtoms << " ( Setup ) " <<endl;
					output << error << "(Current Read) " << Num_atoms << " != " << nAtoms << " ( Setup ) " <<endl;
				}
				ss.clear();
				
				Num_obs = Num_atoms - nAtoms;				//for clearing obstacles:
				if (Num_obs < 0)
				{
					cout << "Wrong atoms!" << endl;
					output << "Wrong atoms!" << endl;
					exit(1);
				}
				
				for (int clear = 0; clear < 5; clear++)			
					getline(fin, temp);
				head = temp;								//all the head

				for (int clear = 0; clear < Num_atoms+2; clear++)	//clear information of cut[0]
				getline(fin, temp);
				cut[1] = fin.tellg() - pos - 2*Num_atoms;
				ss << temp;
				ss >> timestep;
				ss.clear();
			}

			//for cut[0]
			for (int clear = 0; clear < cut[0] && timestep != iframe * dstep; clear++)
			{
				fin.seekg(cut[1], ios::cur);
				fin.ignore(cut[1], 'P');
				getline(fin,  temp);
				getline(fin,  temp);
				ss << temp;
				ss >> timestep;
				ss.clear();
			}
			if (timestep != iframe * dstep)		//extern const int steps_frame  = 5000;
			{
				string error = "\"ERROR\": Timestep != iframe * steps_frame * cut[0] (analyser.h:35) -> ";
				cout << error << timestep << " != " << iframe * dstep << " (" << iframe << " * " << steps_frame  << " * " << cut[0]<< ")" << endl;
				cout << "Current frame: " << iframe << endl;
				output << error << timestep << " != " << iframe * dstep << " (" << iframe << " * " << steps_frame  << " * " << cut[0]<< ")" << endl;
				output << "Current frame: " << iframe << endl;
				exit(1);
			}
			
			for (int clear = 0; clear < 7; clear++)	//clear information of head
				getline(fin, temp);
			
			//Read data of atoms
			for (int iAtom = 1; iAtom <= nAtoms; iAtom++)
			{
				vector<int> ID(2, 0);
				getline(fin, temp);
				ss << temp;
				for (int k = 0; k < Num_info; k++)
					if( k < 2)
						ss >> ID[k];
					else
						ss >> Atoms[ifile][iframe][iAtom][k-2];
//					ss >> atom[iAtom-1][k-2];
				if (ID[0] != iAtom)
				{
					cout << "Wrong atom ID!!\nCurrent frame: " << timestep/steps_frame  << endl;
					output << "Wrong atom ID!!\nCurrent frame: " << timestep/steps_frame  << endl;
					exit(1);
				}
			}
			for (int clear = 0; clear < Num_obs; clear++)	//clear information of obstacles
			getline(fin, temp); 
			
			//rcm,vcm
			for (int i = 0; i < dim*2; i++)
			{
				for (int iAtom = 1; iAtom <= nAtoms; iAtom++)
//					v_cm[i] += atom[iAtom-1][i];
//				v_cm[i] /= nAtoms;
					Atoms[ifile][iframe][0][i] += Atoms[ifile][iframe][iAtom][i];
				Atoms[ifile][iframe][0][i] /= nAtoms;		//ave-> rcm,vcm
			}
			
			//compute
			if ( !outdataA.size() )
				break;
			else if ( ! (iframe % (Num_frames / 10) ) ){
				cout << iframe * dstep * md_dt<< "\t";// << timestep << endl;
				output << iframe * dstep * md_dt<< "\t";// << timestep << endl;
			}
				
			for (int k = 0; k < outdataA.size(); k++)
			{
				//Rg[],Re[],Lcm[],Ang[]
				//vec_doub atom(pCom[k]);
				paraA[k][jfile][iframe] = compute(outdata[k], Atoms[ifile][iframe]);
				//compute("func", atom, cm, iframe);
				//compute("gr", atom, cm, iframe);
				for (int p = 0; p < pCom[k]; p++)
				{
					paraA[k][0][iframe][p] += paraA[k][jfile][iframe][p];
					if ( ! (iframe % (Num_frames / 10) ) ){
						cout << paraA[k][jfile][iframe][p] << "  ";
						output << paraA[k][jfile][iframe][p] << "  ";
					}
						
				}
				// output average
				if (jfile == Num_files)
				{
					for (int p = 0; p < pCom[k]; p++)//
					{
						paraA[k][0][iframe][p]/=Num_files; 
						if ( ! (iframe % (Num_frames / 10) ) ){
							cout << "| " << paraA[k][0][iframe][p] << "(ave) \t";
							output << "| " << paraA[k][0][iframe][p] << "(ave) \t";
						}
							
					}
				}
			}
			if ( ! (iframe % (Num_frames / 10) ) ){
				cout << endl;
				output << endl;
			}
				
		}
		time("Rg* 4", start);start = clock();
		
		//msd
		for (int k = outdataA.size() ; k < outdata.size(); k++)
		{
			if(outdataB.size()){
				cout << "\ntime(dt = " << dstep * md_dt << ")\t\t" << outdataB << endl;
				output << "\ntime(dt = " << dstep * md_dt << ")\t\t" << outdataB << endl;
			}
				
			else
				break;
			//vec_doub2 msd(max_frame+1, msd.size());
			paraA[k][jfile] = compute(outdata[k], Atoms[ifile]);
			for (int dt = 1; dt <= max_frame; dt++)	//cut[frames] [bits]
			{
				if ( ! (dt % (max_frame / 10) ) ){
					cout << dt * dstep * md_dt<< " \t" ;
					output << dt * dstep * md_dt<< " \t" ;
				}
					
				for (int p = 0; p < msd.size(); p++)
				{
					paraA[k][0][dt][p] += paraA[k][jfile][dt][p];
					if ( ! (dt % (max_frame / 10) ) ){
						cout << paraA[k][jfile][dt][p] << "  ";
						output << paraA[k][jfile][dt][p] << "  ";
					}
					
				}
				if (jfile == Num_files)
				{
					for (int p = 0; p < msd.size(); p++)//
					{
						paraA[k][0][dt][p]/=Num_files; 
						if ( ! (dt % (max_frame / 10) ) ){
							cout << "| " << paraA[k][0][dt][p] << "(ave) \t";
							output << "| " << paraA[k][0][dt][p] << "(ave) \t";
						}
							
					}
				}
				if ( ! (dt % (max_frame / 10) ) ){
					cout << endl;
					output << endl;
				}
					
			}
		}
		fin.close();
		time("MSD", start); start = clock();
	}

	
	//outdata
	//average on time
	for ( int k = 0; k < outdataA.size(); k++)
	{
		fout[k] << "aot\t" ;
		for (int p = 0; p < pCom[k]; p++)
			for (int ifile = 0; ifile <= Num_files; ifile++)
				fout[k] << paraA[k][ifile][0][p] << " \t";
		fout[k] << endl;
	}
	
	// time and data[ifile][ipara]
	for ( int k = 0; k < outdata.size(); k++)
	{
		if ( k < outdataA.size())
		{
			for (int iframe = 1; iframe <= Num_frames; iframe++)
			{
				fout[k] << iframe * dstep * md_dt  << "\t";
				//cout << iframe * dstep * md_dt  << "\t";
				{
					for (int ifile = 0; ifile <= Num_files; ifile++)
						for (int p = 0; p < pCom[k]; p++)
						{
							//cout << paraA[k][ifile][iframe][p] << " \t";
							fout[k] << paraA[k][ifile][iframe][p] << " \t";
						}
					//cout << endl;
					fout[k] << endl;
				}
			}
		}
		else 
		{
				for (int iframe = 1; iframe <= max_frame; iframe++)
				{
					fout[k] << iframe * dstep * md_dt  << "\t";
					//cout << iframe * dstep * md_dt  << "\t";
					for (int ifile = 0; ifile <= Num_files; ifile++)
						for (int p = 0; p < msd.size(); p++)
						{
							//cout << paraA[k][ifile][iframe][p] << " \t";
							fout[k] << paraA[k][ifile][iframe][p] << " \t";
						}
					//cout << endl;
					fout[k] << endl;
			}
		}
	}
	//close files
	for (int k = 0; k < outdata.size(); k++)
		fout[k].close();
	//time("Output", start);
	cout << "\ntime(dt = " << dstep * md_dt << ")\t\t" << outdata << endl;
	output << "\ntime(dt = " << dstep * md_dt << ")\t\t" << outdata << endl;
	time("Total");
	return 0;
}