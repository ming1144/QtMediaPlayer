//#define SNAKE_DIM 3 
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

#define AUTOADAPT_MAXLEN  16
#define AUTOADAPT  true
#define	AUTOADAPT_LOOP  10
#define	AUTOADAPT_MINLEN  8
#define	MAXITERATION  1000// double alpha=1.1, beta=1.2, gamma=1.5, delta=3.0;
// 


class Snake{
private:
	vector<POINT> snake;
	vector <POINT> newsnake;
 
	// Length of the snake (euclidean distance)
	double snakelength;
 
	// size of the image (and of the 2 arrays below)
	int width,height;
 
	// gradient value (modulus)
	double **gradient;
 
	// gradient flow (modulus)
	double **flow;
 
	// 3x3 neighborhood used to compute energies
	double e_uniformity[3][3];
	double e_curvature[3][3];
	double e_flow[3][3];
	double e_inertia[3][3];
 

	// coefficients for the 4 energy functions
public:
	bool step();
	void loop(vector <POINT> &Snake);
	double MIN(double a, double b, double c);
	void normalize(double array3x3[3][3]);
	double getsnakelength();
	double distance2D(POINT A, POINT B);
	double f_uniformity(POINT prev, POINT next, POINT p);
	double f_curvature(POINT prev, POINT p, POINT next);
	double f_gflow(POINT cur, POINT p);
	double f_inertia(POINT cur, POINT p);
	void rebuild(int space);
	void removeOverlappingPoints(int minlen);
	void addMissingPoints(int maxlen);

	void setwidth(int i);
	void setheight(int i);
	void setArray();
	void GradientFlow(CxImage *inputimage);
	void distance(CxImage *inputimage);

	void Initialization(CxImage *Image);
	~Snake();
	

	Snake()
	{
		snakelength = 0;
		width = 0,height = 0;
		gradient = NULL;
		flow = NULL;
	}
	
};

