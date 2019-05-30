/*
	The program is used to calculate the shape factor of polymer.
	The input data is read for polystat.xvg by gromacs
	1. 用g_polystat 命令生成 polystat.xvg 
	2. 编译此程序, g++ shape_factor.cpp -o shape_factor.exe
	3. 把shape_factor.exe复制到 文件名 polystat.xvg 所在文件夹内，并执行程序 ./shape_factor.exe
	4. 程序生成两个文件： shape_factor_every_frame.dat， shape_factor_average.dat 
 */

# include <stdio.h> 
# include <stdlib.h> 
# include <math.h> 
# include <iostream> 
# include <fstream> 
# include <string.h> 
# include <iomanip>
# include <vector>
# include <ctype.h>

using namespace std ; 

////////////////////////////////////
#define MAX_STR_LEN 256
#define UNIXRETURN ((char)10)
#define ERR_EXIT(a) {printf("Point %d error!\n",a);exit(0);}
#define MAX_DOUBLE 1.7e308
#define MIN_DOUBLE -1.7e308
#define MAX_BONDED_ATM 8
#define PI 3.141592653589793
static double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg * sqrarg)
///////////////////////////////////

#define NumLine 2000 //number of data line
//deal with char
bool substrcpy( char *str1, const char *str2, int from, int to )
{	
	//copy the sub str of str2's (from..to) to str1
	if( from < 0 || to < from || to > strlen(str2) || (to-from) >= MAX_STR_LEN )
		return false;

	int ndx = 0;
	while( *(str2 + from + ndx) == ' ' && ndx + from < to )
		ndx++;
	from += ndx;
	strcpy(str1, str2 + from);
	ndx = 0;
	while(*(str1 + to - from + ndx ) == ' ')
		ndx--;
	str1[to - from + ndx + 1] = '\0';
	return true;
}

bool substrcpy(char *str1, char *str2)
{	
	//to remove the str2's blank char
	return substrcpy(str1, str2, 0, strlen(str2));
}

//主程序 

int main ( ) 
{    
		
		// read data from polyvec.xvg 
		// time  xx xy xz yx yy yz zx zy zz
		int i, j, k = 0, numL = 0;
		// Gyration tensor 
		// Asphericity  delta = 1 - 3*<I_2>/<I_1^2>   
		double timestep, dend, rg;
		double *I1, *I2, *I3,*Ix, *Iy, *Iz, *SF; //I_x>Iy>Iz是椭球的三个轴 
		I1 = (double*)calloc(NumLine,sizeof(double));
		I2 = (double*)calloc(NumLine,sizeof(double));
		I3 = (double*)calloc(NumLine,sizeof(double));
		Ix = (double*)calloc(NumLine,sizeof(double));
		Iy = (double*)calloc(NumLine,sizeof(double));
		Iz = (double*)calloc(NumLine,sizeof(double));
		SF = (double*)calloc(NumLine,sizeof(double));
	   
		char id[MAX_STR_LEN];  
		char temp[MAX_STR_LEN];
		char head[MAX_STR_LEN];
		char mark[MAX_STR_LEN]="\n" ;
		//read data 
		cout<<"Reading File (polystat.xvg) ..."<<endl;
		ifstream fp("polystat.xvg");  
		if (fp)
		{
			while(!fp.eof())
			{
				//去掉文件头注释
				if(k==0) 
				{
					for(k = 0; k < 23; k ++)
					{
				 		 fp.getline( head, MAX_STR_LEN );
					 	 //fprintf(stderr,"%s\n",head);
					} 
				} 
				//开始读文件
			
			fp.getline(id, MAX_STR_LEN);
			//fprintf(stderr,"%s\n",id);
			if(strcmp(id, mark) < 0)
			{
			   //cout<<strcmp(id,mark)<<" check data"<<endl; 
			   break;	
			} 
			if( substrcpy( temp, id, 0, 9 ) )
			    timestep = atof( temp );
			else exit(1);		
			
			if( substrcpy( temp, id, 10, 18 ) )
				dend = atof( temp );
			else exit(1);
			
			if( substrcpy( temp, id, 19, 27 ) )
				rg = atof( temp );
			else exit(1);
			
			if( substrcpy( temp, id, 28, 36 ) )
				Ix[numL] = atof( temp );
			else exit(1);
			
			if( substrcpy( temp, id, 37, 45 ) )
				Iy[numL] = atof( temp );
			else exit(1);
			
			if( substrcpy( temp, id, 46, 54 ) )
				Iz[numL] = atof( temp );
			else exit(1);

			
			I1[numL] = Ix[numL] + Iy[numL] +Iz[numL];
			I2[numL] = Ix[numL]*Iy[numL] + Iy[numL]*Iz[numL] + Iz[numL]*Ix[numL];
			numL ++;
			
			//cout<<numL<<endl; 
			//fprintf(stderr,"%s\n",id);
			
			}
		}
		else 
				cout<<" The file does not exist!"<<endl;  
		fp.close();
		//---------------------------------------------------------------------
		// ensemble processing
		//---------------------------------------------------------------------
		
		double sf_bar, sf_var; 
		sf_bar =  sf_var = 0.0;
		
		double sf_xy_bar, sf_xy_var; 
		sf_xy_bar = sf_xy_var = 0.0;
		
		double sf_xz_bar, sf_xz_var; 
		sf_xz_bar = sf_xz_var = 0.0;
		
		double num_av = 0.0; 
		for(j = 0; j < numL; j ++)
		{     	
			SF[j] =  1.0 - 3.0 * I2[j] / (I1[j] * I1[j]);
		
			if( numL > 600 ? j > numL * 2.0 / 3.0 : 1) 
			{
						sf_bar += SF[j]; 
						sf_var += SF[j] * SF[j];  
						sf_xy_bar += Ix[j]/Iy[j]; 
						sf_xy_var += SQR(Ix[j]/Iy[j]);
						sf_xz_bar += Ix[j]/Iz[j]; 
						sf_xz_var += SQR(Ix[j]/Iz[j]);
						num_av ++; 
			}
		}
		
		cout<<"Total     Frame   : "<< numL << endl << "Frame for Average : " << num_av << endl;
		
		sf_bar /= num_av; 
		sf_var /= num_av; 
		sf_var -= sf_bar * sf_bar;
		sf_xy_bar /= num_av; 
		sf_xy_var /= num_av; 
		sf_xy_var -= sf_xy_bar * sf_xy_bar;
		sf_xz_bar /= num_av; 
		sf_xz_var /= num_av; 
		sf_xz_var -= sf_xz_bar * sf_xz_bar;

		cout<< "Outputing File of Shape Factor ...\nFile 1: shape_factor_every_frame.dat \nFile 2: shape_factor_average.dat" << endl;   
		 
		ofstream out1("shape_factor_every_frame.dat");
		for(j = 0; j < numL; j ++)
			out1 << setw(10) << setiosflags(ios::fixed) << setprecision(4) << j * 0.5 << "  " << SF[j] <<endl;
		out1.close(); 
	   
		ofstream out2("shape_factor_average.dat");
		out2<< "# a_av a_err  axy_av  axy_err  axz_av   axz_err "<<endl 
				<< sf_bar << "  " <<sqrt(sf_var/num_av) << "   "
				<<sf_xy_bar<<"  "<<sqrt(sf_xy_var/num_av)<<"  "
				<<sf_xz_bar<<"  "<<sqrt(sf_xz_var/num_av)<<endl;
		out2.close(); 

		free(I1);
		free(I2);
		free(I3);
		free(Iz);
		free(Ix);
		free(Iy); 
		free(SF);

	return(0);
}


