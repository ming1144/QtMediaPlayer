//#define SNAKE_DIM 3 
#include "StdAfx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include<vector>
#include ".\CxImage\ximage.h"
#include "snakeList.h"
using namespace std;

/////////////////////////////AUTOADAPT_MAXLEN AUTOADAPT_MINLEN  case bu case
#define AUTOADAPT_MAXLEN  5       /////// 16 3
#define AUTOADAPT  true
#define	AUTOADAPT_LOOP  20        /////// 10
#define	AUTOADAPT_MINLEN  2       /////// 8 1
#define	MAXITERATION  1000


void Snake::Initialization(CxImage *Image)
{
	
	width = Image->GetWidth();
	height = Image->GetHeight();
	//

	setArray();

//	GradientFlow(Image);

	distance(Image);
	
}

Snake::~Snake()
{
	snake.clear();
	newsnake.clear();
	if (gradient)
	{
		for (int i = 0; i < height; i++) delete [] gradient[i];
		delete [] gradient;
	}

	if (flow)
	{
		for (int i = 0; i < height; i++) delete[] flow[i];
		delete[] flow;
	}

	

}

void Snake::loop(vector <POINT> &SnakeList) {
	int loop=0;
 

	snake.clear();
	POINT P;

	for (int i = 0; i < SnakeList.size(); i++)
	{
		P.x = SnakeList[i].x; P.y = height - SnakeList[i].y - 1;
		snake.push_back(P);
	}



	while (step() && loop < MAXITERATION)
	{
		
		if (AUTOADAPT && (loop%AUTOADAPT_LOOP)==0) 
		{
			removeOverlappingPoints(AUTOADAPT_MINLEN);
			addMissingPoints(AUTOADAPT_MAXLEN);
		}
		loop++;
	}


	///////////////////////////////***************研究它的功能
	if (AUTOADAPT) rebuild(AUTOADAPT_MAXLEN);

	SnakeList.clear();

	for (int i = 0; i < snake.size(); i++)
	{
		P.x = snake[i].x; P.y = height - 1 - snake[i].y;
		SnakeList.push_back(P);
	}

}


double alpha = 0.1, beta = 1.2, gamma = 100.0, delta = 3.0;
bool Snake::step() {

	bool changed=false;
	POINT p;
	p.x=0;p.y=0;

	int snakelength = snake.size();

	newsnake.clear();
	for(int i=0;i<snakelength ;i++) {
		POINT pp = snake[(i+snakelength-1)%snakelength];
		POINT cur  = snake[i];
		POINT next = snake[(i+1)%snakelength];
 
		for(int dy=-1;dy<=1;dy++) {
			for(int dx=-1;dx<=1;dx++) {
				p.x=cur.x+dx;p.y= cur.y+dy;
				e_uniformity[1+dy][1+dx] = f_uniformity(pp,next,p);
				e_curvature[1+dy][1+dx]  = f_curvature(pp,p,next);
				e_flow[1 + dy][1 + dx] =   flow[p.y][p.x]; //f_gflow(cur,p);
				e_inertia[1+dy][1+dx]    = f_inertia(cur,p);
			}
		}

		normalize(e_uniformity);
		normalize(e_curvature);
		normalize(e_flow);
		normalize(e_inertia);
 
		double emin = 10000 , e=0;
		int x=0,y=0;
		for(int dy=-1;dy<=1;dy++) {
			for(int dx=-1;dx<=1;dx++) {
				e = 0;
				e+= alpha * e_uniformity[1+dy][1+dx]; 
				e+= beta  * e_curvature[1+dy][1+dx]; 
     			e+= gamma * e_flow[1+dy][1+dx]; 
				e+= delta * e_inertia[1+dy][1+dx];
 
				if (e<emin) { emin=e; x=cur.x+dx; y=cur.y+dy; }
			}
		}
		if (x<1) x=1;
		if (x>=(width-1)) x=width-2;
		if (y<1) y=1;
		if (y>=(height-1)) y=height-2;
 
		if (x!=cur.x || y!=cur.y) changed=true;
        POINT PP; PP.x=x; PP.y=y;
		newsnake.push_back(PP);
	}
	for (int i = 0; i < snakelength; i++)
	    snake[i]=newsnake[i];
	return changed;
}
 
// normalize energy matrix
void Snake::normalize(double array3x3[3][3]) {
	double sum=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			sum+=abs(array3x3[i][j]);
 
	if (sum==0) return;
 
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			array3x3[i][j]/=sum;
}
 
double Snake::getsnakelength() {
	// total length of snake
	double length=0;
	for(unsigned int i=0;i<snake.size();i++) {
		POINT cur   = snake[i];
		POINT next  = snake[(i+1)%snake.size()];
		length+=distance2D(cur, next);
	}
	return length;
}
 
double Snake::distance2D(POINT A, POINT B) {
	int ux = A.x-B.x;
	int uy = A.y-B.y;
	double un = ux*ux+uy*uy;
	return sqrt(un);
}

double Snake::f_uniformity(POINT prev, POINT next, POINT p) {
 

	double un = distance2D(prev, p);
 

	double avg = snakelength /snake.size();
	double dun = abs(un-avg);
 
	return dun*dun;
}
 
double Snake::f_curvature(POINT prev, POINT p, POINT next) {
	int ux = p.x-prev.x;
	int uy = p.y-prev.y;
	double un = sqrt((double)ux*ux+uy*uy); 
 
	int vx = p.x-next.x;
	int vy = p.y-next.y;
	double vn = sqrt((double) vx*vx+vy*vy);

	if (un==0 || vn==0) return 0;
 
	double cx = (vx+ux)/(un*vn);
	double cy = (vy+uy)/(un*vn);
 
	double cn = cx*cx+cy*cy;
	return cn;
}
 
double Snake::f_gflow(POINT cur, POINT p) {

//	int dcur = flow[cur.x][cur.y];
//	int dp   = flow[p.x][p.y];
//  double dcur = flow[cur.y][cur.x];
// 	double dp   = flow[p.y][p.x];
// 	double d = dp-dcur;
//	return flow[p.y][p.x] - flow[cur.y][cur.x];
	return flow[p.y][p.x];
}
 
double Snake::f_inertia(POINT cur, POINT p) {
	double d = distance2D(cur, p);
	double g = gradient[cur.y][cur.x];
	double e = g*d;
	return e;
}

void Snake::rebuild(int space) {
 

	double *clength = new double[snake.size()+1];
	clength[0]=0;
	for(unsigned int i=0;i<snake.size();i++) {
		POINT cur   = snake[i];
		POINT next  = snake[(i+1)%snake.size()];
		clength[i+1]=clength[i]+distance2D(cur, next);
	}
	double total = clength[snake.size()];
	int nmb = (int)(0.5+total/space);
 
//	vector<POINT> newsnake;
	newsnake.clear();
	for(int i=0,j=0;j<nmb;j++) {
		double dist = (j*total)/nmb;
 
		while(! (clength[i]<=dist && dist<clength[i+1])) i++;
 
		POINT prev  = snake[(i+snake.size()-1)%snake.size()];
		POINT cur   = snake[i];
		POINT next  = snake[(i+1)%snake.size()];
		POINT next2  = snake[(i+2)%snake.size()];
 
		double t =  (dist-clength[i])/(clength[i+1]-clength[i]);
		double t2 = t*t, t3=t2*t;
		double c0 =  1*t3;
		double c1 = -3*t3 +3*t2 +3*t + 1;
		double c2 =  3*t3 -6*t2 + 4;
		double c3 = -1*t3 +3*t2 -3*t + 1;
		double x = prev.x*c3 + cur.x*c2 + next.x* c1 + next2.x*c0;
		double y = prev.y*c3 + cur.y*c2 + next.y* c1 + next2.y*c0;
		POINT newpoint;
		newpoint.x = (int)(0.5+x/6);newpoint.y = (int)(0.5+y/6);
		newsnake.push_back(newpoint);
	}
	snake.clear();
	for (unsigned int i = 0; i < newsnake.size();i++)
	    snake.push_back(newsnake[i]);

	newsnake.clear();
	delete [] clength;
}
 
 
void Snake::removeOverlappingPoints(int minlen) {
	for(unsigned int i=0;i<snake.size();i++) {
		POINT cur = snake[i];
 
		for(int di=1+snake.size()/2;di>0;di--) {
			POINT end  = snake[(i+di)%snake.size()];
			double dist = distance2D(cur,end);
 
			if ( dist>minlen ) continue;
 
			for(int k=0;k<di;k++) snake.erase( snake.begin()+(i+1) %snake.size() );
			break;
		}
	}
}
 
void Snake::addMissingPoints(int maxlen) {

	for(unsigned int i=0;i<snake.size();i++) {
		POINT prev  = snake[(i+snake.size()-1)%snake.size()];
		POINT cur   = snake[i];
		POINT next  = snake[(i+1)%snake.size()];
		POINT next2  = snake[(i+2)%snake.size()];

		if ( distance2D(cur,next)>maxlen ) {

			double c0=0.125/6.0, c1=2.875/6.0, c2=2.875/6.0, c3=0.125/6.0;
			double x = prev.x*c3 + cur.x*c2 + next.x* c1 + next2.x*c0;
			double y = prev.y*c3 + cur.y*c2 + next.y* c1 + next2.y*c0;
			POINT newpoint;
			newpoint.x =  (int)(0.5+x);newpoint.y = (int)(0.5+y);
			snake.emplace(snake.begin()+i+1,newpoint); i--;
		}
	}
}
void Snake::setwidth(int i)
{
	width = i;
}
void Snake::setheight(int i)
{
	height = i;
}
void Snake::setArray()
{
	gradient = new double*[height];
	for(int i = 0 ;i<height ; i++)gradient[i]= new double[width];
	flow = new double*[height];
	for(int i = 0 ;i<height ; i++)flow[i]= new double[width];
	for(int y = 0 ; y < height ; y++)
	{
		for(int x = 0 ; x < width ; x++)
		{
			gradient[y][x] = 0;
			flow[y][x] = 0;
		}
	}
}
void Snake::GradientFlow(CxImage *inputimage)
{
	double **temp, **fx,**fy, **u, **v,**Lu,**Lv;

	temp = new double*[height];
	fx = new double*[height];
	fy = new double*[height];
	u = new double*[height];
	v = new double*[height];

	Lu = new double*[height];
	Lv = new double*[height];

	for (int i = 0; i < height; i++)
	{   
		temp[i]= new double[width];
		fx[i] = new double[width];
		fy[i] = new double[width];
		u[i] = new double[width];
		v[i] = new double[width];
		Lu[i] = new double[width];
		Lv[i] = new double[width];
	}



	BYTE* buf = inputimage->GetBits() + (height - 1) * inputimage->GetEffWidth();
	int EffW = inputimage->GetEffWidth();
	for(int y=height-1;y>=0;y--, buf -= EffW)
	{
		for(int x=0,k=0;x<width;x++,k+=3)
		{
			double sum = 0;
			sum = (buf[k] + buf[k+1] + buf[k+2])/3;
			temp[y][x] = sum/255.0;
		}
	}


	for (int x = 0; x < width; x++)
	{
		gradient[0][x] = 0;	gradient[height - 1][x] = 0;
		fx[0][x] = 0;		fx[height - 1][x] = 0;
		fy[0][x] = 0;		fy[height - 1][x] = 0;
		Lu[0][x] = 0;		Lu[height - 1][x] = 0;
		Lv[0][x] = 0;		Lv[height - 1][x] = 0;
	}
	for (int y = 0; y < height; y++)
	{
		gradient[y][0] = 0;
		gradient[y][width - 1] =0;
		fx[y][0] = 0;		fx[y][width - 1] = 0;
		fy[y][0] = 0;		fy[y][width - 1] = 0;
		Lu[y][0] = 0;		Lu[y][width - 1] = 0;
		Lv[y][0] = 0;		Lv[y][width - 1] = 0;
	 
	}

	for(int y=1;y<height-1;y++)
	{
		for(int x=1;x<width-1;x++)
		{
			double Ix=0 , Iy=0 , total = 0;
			Ix = fx[y][x] =temp[y][x+1] - temp[y][x-1];
			Iy = fy[y][x] =temp[y+1][x] - temp[y-1][x];
			gradient[y][x] = Ix*Ix+Iy*Iy;
		}
	}


// 	double mu = 1;
// 	int ITER = 20;
// 	for (int y = 0; y < height; y++) {
// 		for (int x = 0; x < width; x++) {
// 			u[y][x] = 0;
// 			v[y][x] = 0;
// 		}
// 	}
// 
// 	for (int loop = 0; loop < ITER; loop++)
// 	{
// 		// compute laplacian of U and V
// 		for (int y = 1; y < (height - 1); y++) {
// 			for (int x = 1; x < (width - 1); x++) {
// 				Lu[y][x] = -u[y][x] + 0.25*(u[y - 1][x] + u[y + 1][x] + u[y][x - 1] + u[y][x + 1]);
// 				Lv[y][x] = -v[y][x] + 0.25*(v[y - 1][x] + v[y + 1][x] + v[y][x - 1] + v[y][x + 1]);
// 			}
// 		}
// 
// 		// update U and V
// 		mu = 4*mu;
// 		for (int y = 0; y < height; y++) {
// 			for (int x = 0; x < width; x++) {
// 				double gnorm2 = fx[y][x] * fx[y][x] + fy[y][x] * fy[y][x];
// 
// 				u[y][x] += mu * Lu[y][x] - (u[y][x] - fx[y][x])*gnorm2;
// 				v[y][x] += mu * Lv[y][x] - (v[y][x] - fy[y][x])*gnorm2;
// 			}
// 		}
// 	}


	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			flow[y][x] = -gradient[y][x];  // Lu[y][x] * Lu[y][x] + Lv[y][x] * Lv[y][x];
		}
	}


	for (int i = 0; i < height; i++)
	{
		delete[] temp[i];
		delete[] fx[i];
		delete[] fy[i];
		delete[] u[i];
		delete[] v[i];
		delete[] Lu[i];
		delete[] Lv[i];
	}

	delete[] temp;
	delete[] fx;
	delete[] fy;
	delete[] u;
	delete[] v;
	delete[] Lu;
	delete[] Lv;
}

double Snake::MIN(double a, double b, double c)
{
	double minnum;
	minnum = a;
	if( b<minnum )minnum=b;
	if( c<minnum )minnum=c;
	return minnum;
}

void Snake::distance(CxImage *inputimage)
{
	double result=0;
	int up, down, left, right;

	int w, h,w_1,h_1,EffWdith;
	unsigned char *color_img;
	w = inputimage->GetWidth();
	h = inputimage->GetHeight();
	w_1 = w - 1; h_1 = h - 1;
	EffWdith = inputimage->GetEffWidth();
	color_img = inputimage->GetBits() + (h-1) * EffWdith- EffWdith;

	int ix, iy;
	double maxGradient = 0;
	for(int y=1; y<h_1; y++,color_img -= EffWdith)			//edge detection
	{
		for(int x=1,k=3; x< w_1; x++,k+=3)
		{
			up    = (color_img[k+EffWdith] + color_img[k+1+EffWdith] + color_img[k+2+EffWdith]) /3;

			down = (color_img[k - EffWdith] + color_img[k + 1 - EffWdith] + color_img[k + 2 - EffWdith]) / 3;
			left = (color_img[k-3] + color_img[k -2] + color_img[k -3]) / 3;
			right = (color_img[k + 3] + color_img[k + 4] + color_img[k + 5]) / 3;
			ix = right - left; iy = up - down;
			result = ix * ix + iy *iy;
			gradient[h_1 - y][x] = result;
			if (result > maxGradient) maxGradient = result;
			if(result>3600)
			{
				flow[h_1-y][x] = 0;  // 做上下顛倒
			}
			else
			{
				flow[h_1-y][x] = 9999999;
			}
		}
	}


	for (int x = 0; x < width; x++)
	{
		flow[0][x] = 9999999;
		flow[h-1][x] = 9999999;
	}
	for (int y = 0; y < height; y++)
	{
		flow[y][0] = 9999999;
		flow[y][w - 1] = 9999999;
	}


	for(int y = 1 ; y < height ; y++ )
	{
		for(int x = 1 ; x < width ; x++ )
		{
			flow[y][x] = MIN(flow[y][x], flow[y - 1][x] + 1, flow[y][x - 1] + 1);
			
		}
	}


	for(int y = height - 2 ; y >= 0 ; y-- )
	{
		for(int x = width - 2 ; x >= 0 ; x-- )
		{
			flow[y][x] = MIN(flow[y][x], flow[y + 1][x] + 1, flow[y][x + 1] + 1);
		}
	}

	// combine distance transform and gradient together
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			flow[y][x] += (maxGradient - gradient[y][x]) / maxGradient;
		}
	}
}


