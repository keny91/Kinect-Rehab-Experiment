#pragma once
class Spline

	/*
	Tricubic_Splines

The comments about the extensibility of 1d splines to 2d applies equally
well to 3d rectilinear grids.  So, too, do the comments about the method
of construction, the differentiability properties of the result, and 
the choice between the (faster) "explicit" representation requiring
64*Nx*Ny*Nz memory words, and the "compact" representation requiring
8*Nx*Ny*Nz memory words.

The input data for setup of a 3d spline are

  f(i,j,k) at x(i),i=1 to Nx, y(j), j=1 to Ny, z(k), i=1 to Nz.
           with x(i+1).gt.x(i),
                y(j+1).gt.y(j), and
                z(k+1).gt.z(k) required.

General boundary conditions are 1st or second derivative information
across a grid boundary plane, e.g. df/dx at (x(1),y(j),z(k)), an Ny x Nz
array of data.

Periodic and "not a knot" boundary conditions are again available.  For 
data given on a toroidal coordinate system, f(r,theta,phi), periodic 
boundary conditions in the theta and phi directions would be the 
preferred choice.

The storage requirement for the explicit 3d spline representation 
data set is 64*Nx*Ny*Nz.  The cost of evaluation is 21 computations 
of the form ((A*x+B)*x+C)*x+D (63 A*x+B type operations).  The storage
requirement for the compact representation is 8*Nx*Ny*Nz, and timing
tests (on a DEC alpha workstation) show the cost of evaluation to be
approximately 1.4 times greater than for the explicit representation.

The PSPLINE library offers three routines, with different boundary
condition option sets, for the setting up of tricubic spline data sets.
In addition, there is a scalar bicubic spline evaluation routine and
a vectorized spline evaluation routine.

Remarkably, standard mathematics software libraries (NAG, netlib) do not 
seem to include tricubic splines.  Yet this representation can be highly
efficient in practice -- the author has used a tricubic spline to replace
an optimized hybrid Fourier series & 1d spline representation of an 
actual physics model object, with a speedup in evaluation of a factor 
of nearly 100 on a DEC alpha workstation (although a substantial memory
cost is incurred).  See the "Case Study" (top level subtopic).

	*/


{
public:
	Spline();
	~Spline();
};

