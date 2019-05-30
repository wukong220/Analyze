#ifndef HEAD_H
#define HEAD_H

#include <fstream>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.1415926535897
#define SR2 1.4142135623731
#define Type_chain 1
#define Type_obs 2

int number(double phi, double l, double r);			//Number of the obstacles
//Setting box
const double L_box = 200.0;							//Lengh of the box

const double rad = 0.5;					//radius of the chain
const double Sigma = 2 * rad;			//2  *  radius of the chain  *  2
const int N_chain = 50;					//polarization of single chain
const int Num_chains = 1;				//Number of the chains

const double rad_obs = 5.0;								//radius of the obstacle
const double R_obs = 2  *  rad_obs ;					//2  *  radius of the obstacle  *  2
const double Phi_obs = 0.6;								//Area density of the obstacles
const double inter = Sigma+2.5 * rad_obs;				//Minimal distace between beeds and obstacles
const int Num_obs = number(Phi_obs, L_box, rad_obs);	//Number of the obstacles

#define max(x, y)  ( x >= y? x : y )
#define min(x, y)  ( x <= y? x : y )

//Number of the obstacles
inline int number(double phi, double l, double r)
{
	double s = PI * r * r;
	double S = l * l;
	double num = phi * S/s;
	return int(num);
}