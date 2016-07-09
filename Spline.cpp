#include "Spline.h"



Spline::Spline()
{
}

Spline::Spline(double*xi, double*yi)
{
	size = sizeof(x) / sizeof(x[0]);
	x = xi; 
	y = yi;
}

/*
public HSpline (java.util.Vector L)
{
size=L.size();
x=new double[size];
y=new double[size];
for (int k=0;k<size;k++)
{
Point2D p=(Point2D)L.get(k);
x[k]=p.getX(); y[k]=p.getY();
}
this.x=x; this.y=y;
}
*/


Spline::~Spline()
{
}


void Spline::run()
{
	// System.err.println(size);

	// support arrays
	double*gamma = new double[size];
	double*deltax = new double[size];
	double*deltay = new double[size];

	// first derivatives
	double*Dx = new double[size];
	double*Dy = new double[size];

	// calculate gamma values
	gamma[0] = 0.5;
	for (int i = 1; i<size - 1; i++)
		gamma[i] = 1 / (4 - gamma[i - 1]);
	gamma[size - 1] = 1 / (2 - gamma[size - 2]);

	// calculate deltax values
	deltax[0] = 3 * (x[1] - x[0])*gamma[0];
	for (int i = 1; i<size - 1; i++)
		deltax[i] = (3 * (x[i + 1] - x[i - 1]) - deltax[i - 1])*gamma[i];
	deltax[size - 1] = (3 * (x[size - 1] - x[size - 2]) - deltax[size - 2])*gamma[size - 1];

	// calculate deltax values
	deltay[0] = 3 * (y[1] - y[0])*gamma[0];
	for (int i = 1; i<size - 1; i++)
		deltay[i] = (3 * (y[i + 1] - y[i - 1]) - deltay[i - 1])*gamma[i];
	deltay[size - 1] = (3 * (y[size - 1] - y[size - 2]) - deltay[size - 2])*gamma[size - 1];

	// calculate Dx values
	Dx[size - 1] = deltax[size - 1];
	for (int i = size - 2; i >= 0; i--)
		Dx[i] = deltax[i] - gamma[i] * Dx[i + 1];

	// calculate Dy values
	Dy[size - 1] = deltay[size - 1];
	for (int i = size - 2; i >= 0; i--)
		Dy[i] = deltay[i] - gamma[i] * Dy[i + 1];

	// calculate coefficients
	coeffx = new Coeff[size];
	coeffy = new Coeff[size];
	for (int i = 0; i<size; i++)
	{
		coeffx[i] =  Coeff();
		coeffy[i] =  Coeff();
	}
	for (int i = 0; i<size - 1; i++)
	{
		coeffx[i].a = x[i]; coeffx[i].b = Dx[i];
		coeffx[i].c = 3 * (x[i + 1] - x[i]) - 2 * Dx[i] - Dx[i + 1];
		coeffx[i].d = 2 * (x[i] - x[i + 1]) + Dx[i] + Dx[i + 1];

		coeffy[i].a = y[i]; coeffy[i].b = Dy[i];
		coeffy[i].c = 3 * (y[i + 1] - y[i]) - 2 * Dy[i] - Dy[i + 1];
		coeffy[i].d = 2 * (y[i] - y[i + 1]) + Dy[i] + Dy[i + 1];
	}

	return;
}


