/** Copyright (c) 2010, University of Szeged
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* - Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
* - Neither the name of University of Szeged nor the names of its
* contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Author: Ali Baharev
*/

#include <fstream>

//#define USING_HESS_TYPE
#ifdef USING_HESS_TYPE
#include <hess_ari.hpp>     // Hessian differentiation arithmetic
using namespace cxsc;
typedef HessType T;
typedef HTvector TV;
typedef interval NT;
typedef ivector  NTV;
typedef imatrix  NTM;

#endif

//==============================================================================

#define USING_DOUBLE
#ifdef USING_DOUBLE
#include <iostream>
#include <iomanip>
using namespace std;

typedef double T;
typedef double* TV;
typedef double NT;

#endif

//==============================================================================

const int n_vars = 12;
				// R
T R_11(n_vars);
T R_12(n_vars);
T R_13(n_vars);

T R_21(n_vars);
T R_22(n_vars);
T R_23(n_vars);

T R_31(n_vars);
T R_32(n_vars);
T R_33(n_vars);
				// R0
T R0_11(n_vars);
T R0_12(n_vars);
T R0_13(n_vars);

T R0_21(n_vars);
T R0_22(n_vars);
T R0_23(n_vars);

T R0_31(n_vars);
T R0_32(n_vars);
T R0_33(n_vars);
				// Rn
T Rn_11(n_vars);
T Rn_12(n_vars);
T Rn_13(n_vars);

T Rn_21(n_vars);
T Rn_22(n_vars);
T Rn_23(n_vars);

T Rn_31(n_vars);
T Rn_32(n_vars);
T Rn_33(n_vars);
				// G
T G_11(n_vars);
T G_12(n_vars);
T G_13(n_vars);

T G_21(n_vars);
T G_22(n_vars);
T G_23(n_vars);

T G_31(n_vars);
T G_32(n_vars);
T G_33(n_vars);
				// A
NT A_11(n_vars);
NT A_12(n_vars);
NT A_13(n_vars);

NT A_21(n_vars);
NT A_22(n_vars);
NT A_23(n_vars);

NT A_31(n_vars);
NT A_32(n_vars);
NT A_33(n_vars);
				// C
T C_11(n_vars);
T C_12(n_vars);
T C_13(n_vars);

T C_21(n_vars);
T C_22(n_vars);
T C_23(n_vars);

T C_31(n_vars);
T C_32(n_vars);
T C_33(n_vars);
				// Cc
T Cc_11(n_vars);
T Cc_12(n_vars);
T Cc_13(n_vars);

T Cc_21(n_vars);
T Cc_22(n_vars);
T Cc_23(n_vars);

T Cc_31(n_vars);
T Cc_32(n_vars);
T Cc_33(n_vars);
				// b
NT b1(n_vars);
NT b2(n_vars);
NT b3(n_vars);
				// d
T d1(n_vars);
T d2(n_vars);
T d3(n_vars);
				// dc
T dc1(n_vars);
T dc2(n_vars);
T dc3(n_vars);
				// g
T gx(n_vars);
T gy(n_vars);
T gz(n_vars);
				// sum
T sx(n_vars);
T sy(n_vars);
T sz(n_vars);

//==============================================================================

T half(n_vars);
T one(n_vars);
T three(n_vars);
T dt(n_vars);
T g_ref(n_vars);

T* wx(0);
T* wy(0);
T* wz(0);

NT* ax(0);
NT* ay(0);
NT* az(0);

int N(-1);

void init(const char* filename) {

	half  = NT(0.5);
	one   = NT(1);
	three = NT(3);
	dt    = NT(10.0/2048.0);
	g_ref = NT(9.81);

	//--------------------------------------------------------------------------

	ifstream in(filename);

	if (!in.good())
		throw "Failed to open input file";

	in >> N;

	if (N<1)
		throw "Invalid length!";

	//--------------------------------------------------------------------------

	wx = new T[N];

	wy = new T[N];

	wz = new T[N];

#ifdef USING_HESS_TYPE

	for (int i=0; i<N; ++i)
		Resize(wx[i], n_vars);

	for (int i=0; i<N; ++i)
		Resize(wy[i], n_vars);

	for (int i=0; i<N; ++i)
		Resize(wz[i], n_vars);

#endif

	//--------------------------------------------------

	ax = new NT[N];
	ay = new NT[N];
	az = new NT[N];

	//---------------------------------------------------

	A_11 = NT(1.0);
	A_12 = NT(0.0);
	A_13 = NT(0.0);

	A_21 = NT(0.0);
	A_22 = NT(1.0);
	A_23 = NT(0.0);

	A_31 = NT(0.0);
	A_32 = NT(0.0);
	A_33 = NT(1.0);

	//----------------------------------------------

	Cc_11 = NT(1.0);
	Cc_12 = NT(0.0);
	Cc_13 = NT(0.0);

	Cc_21 = NT(0.0);
	Cc_22 = NT(1.0);
	Cc_23 = NT(0.0);

	Cc_31 = NT(0.0);
	Cc_32 = NT(0.0);
	Cc_33 = NT(1.0);

	//-----------------------------------------------

	b1 = NT(0.0);
	b2 = NT(0.0);
	b3 = NT(0.0);

	//-----------------------------------------------

	dc1 = NT(0.0);
	dc2 = NT(0.0);
	dc3 = NT(0.0);

	//---------------------------------------------------

	R0_11 = NT(1.0);
	R0_12 = NT(0.0);
	R0_13 = NT(0.0);

	R0_21 = NT(0.0);
	R0_22 = NT(1.0);
	R0_23 = NT(0.0);

	R0_31 = NT(0.0);
	R0_32 = NT(0.0);
	R0_33 = NT(1.0);

	//---------------------------------------------------

	double dummy(0.0);

	for (int i=0; i<N; ++i) {

		in >> ax[i];
		in >> ay[i];
		in >> az[i];

		in >> dummy; in >> dummy; in >> dummy; in >> dummy;


		in >> wx[i];
		in >> wy[i];
		in >> wz[i];

		if (!in.good())
			throw "Error reading input file";

	}

}

void set_sum_and_R0() {

	sx = NT(0);
	sy = NT(0);
	sz = NT(0);

	R_11 = R0_11; R_12 = R0_12; R_13 = R0_13;
	R_21 = R0_21; R_22 = R0_22; R_23 = R0_23;
	R_31 = R0_31; R_32 = R0_32; R_33 = R0_33;
}

void compute_G(int i, const TV& x) {

	C_11 = Cc_11 + x[1];
	C_12 = Cc_12 + x[2];
	C_13 = Cc_13 + x[3];

	C_21 = Cc_21 + x[4];
	C_22 = Cc_22 + x[5];
	C_23 = Cc_23 + x[6];

	C_31 = Cc_31 + x[7];
	C_32 = Cc_32 + x[8];
	C_33 = Cc_33 + x[9];

	d1 = dc1 + x[10];
	d2 = dc2 + x[11];
	d3 = dc3 + x[12];

	cout << endl;
	cout << "gyro x, y, z" << endl;
	cout << wx[i] << '\t' << wy[i] << '\t' << wz[i] << endl;

	T w_x = (C_11*wx[i]+C_12*wy[i]+C_13*wz[i]+d1)*dt;
	T w_y = (C_21*wx[i]+C_22*wy[i]+C_23*wz[i]+d2)*dt;
	T w_z = (C_31*wx[i]+C_32*wy[i]+C_33*wz[i]+d3)*dt;

	G_11 =  one;
	G_12 = -w_z;
	G_13 =  w_y;

	G_21 =  w_z;
	G_22 =  one;
	G_23 = -w_x;

	G_31 = -w_y;
	G_32 =  w_x;
	G_33 =  one;

	cout << endl;
	cout << "G_ij" << endl;
	cout << G_11 << '\t' << G_12 << '\t' << G_13 << endl;
	cout << G_21 << '\t' << G_22 << '\t' << G_23 << endl;
	cout << G_31 << '\t' << G_32 << '\t' << G_33 << endl;
}

void update_R() {

	Rn_11 = R_11*G_11+R_12*G_21+R_13*G_31;
	Rn_12 = R_11*G_12+R_12*G_22+R_13*G_32;
	Rn_13 = R_11*G_13+R_12*G_23+R_13*G_33;

	Rn_21 = R_21*G_11+R_22*G_21+R_23*G_31;
	Rn_22 = R_21*G_12+R_22*G_22+R_23*G_32;
	Rn_23 = R_21*G_13+R_22*G_23+R_23*G_33;

	Rn_31 = R_31*G_11+R_32*G_21+R_33*G_31;
	Rn_32 = R_31*G_12+R_32*G_22+R_33*G_32;
	Rn_33 = R_31*G_13+R_32*G_23+R_33*G_33;

	//---

	R_11 = Rn_11; R_12 = Rn_12; R_13 = Rn_13;
	R_21 = Rn_21; R_22 = Rn_22; R_23 = Rn_23;
	R_31 = Rn_31; R_32 = Rn_32; R_33 = Rn_33;

	return;
}

void normalize_R() {

#ifdef COMPUTE_ERROR
	T err11 = R_13*R_13+R_12*R_12+R_11*R_11 - one;
	T err12 = R_23*R_13+R_22*R_12+R_21*R_11;
	T err13 = R_33*R_13+R_32*R_12+R_31*R_11;

	T err21 = R_13*R_23+R_12*R_22+R_11*R_21;
	T err22 = R_23*R_23+R_22*R_22+R_21*R_21 - one;
	T err23 = R_33*R_23+R_32*R_22+R_31*R_21;

	T err31 = R_13*R_33+R_12*R_32+R_11*R_31;
	T err32 = R_23*R_33+R_22*R_32+R_21*R_31;
	T err33 = R_33*R_33+R_32*R_32+R_31*R_31 - one;
#endif

	T half_error = (R_11*R_21+R_12*R_22+R_13*R_23)*half;

	Rn_11 = R_11-half_error*R_21;
	Rn_12 = R_12-half_error*R_22;
	Rn_13 = R_13-half_error*R_23;

	Rn_21 = R_21-half_error*R_11;
	Rn_22 = R_22-half_error*R_12;
	Rn_23 = R_23-half_error*R_13;

	Rn_31 = Rn_12*Rn_23-Rn_13*Rn_22;
	Rn_32 = Rn_13*Rn_21-Rn_11*Rn_23;
	Rn_33 = Rn_11*Rn_22-Rn_12*Rn_21;

	T C1 = half*(three-(Rn_11*Rn_11+Rn_12*Rn_12+Rn_13*Rn_13));
	T C2 = half*(three-(Rn_21*Rn_21+Rn_22*Rn_22+Rn_23*Rn_23));
	T C3 = half*(three-(Rn_31*Rn_31+Rn_32*Rn_32+Rn_33*Rn_33));

	R_11 = C1*Rn_11;
	R_12 = C1*Rn_12;
	R_13 = C1*Rn_13;

	R_21 = C2*Rn_21;
	R_22 = C2*Rn_22;
	R_23 = C2*Rn_23;

	R_31 = C3*Rn_31;
	R_32 = C3*Rn_32;
	R_33 = C3*Rn_33;

#ifdef COMPUTE_ERROR
	T drr11 = R_13*R_13+R_12*R_12+R_11*R_11 - one;
	T drr12 = R_23*R_13+R_22*R_12+R_21*R_11;
	T drr13 = R_33*R_13+R_32*R_12+R_31*R_11;

	T drr21 = R_13*R_23+R_12*R_22+R_11*R_21;
	T drr22 = R_23*R_23+R_22*R_22+R_21*R_21 - one;
	T drr23 = R_33*R_23+R_32*R_22+R_31*R_21;

	T drr31 = R_13*R_33+R_12*R_32+R_11*R_31;
	T drr32 = R_23*R_33+R_22*R_32+R_21*R_31;
	T drr33 = R_33*R_33+R_32*R_32+R_31*R_31 - one;

	cout << scientific ;
	cout << err11 << "\t" << drr11 << endl;
	cout << err12 << "\t" << drr12 << endl;
	cout << err13 << "\t" << drr13 << endl;

	cout << err21 << "\t" << drr21 << endl;
	cout << err22 << "\t" << drr22 << endl;
	cout << err23 << "\t" << drr23 << endl;

	cout << err31 << "\t" << drr31 << endl;
	cout << err32 << "\t" << drr32 << endl;
	cout << err33 << "\t" << drr33 << endl;
#endif

	cout << endl;
	cout << "R_ij" << endl;
	cout << R_11 << '\t' << R_12 << '\t' << R_13 << endl;
	cout << R_21 << '\t' << R_22 << '\t' << R_23 << endl;
	cout << R_31 << '\t' << R_32 << '\t' << R_33 << endl;

	return;
}

void compute_g(int i) {

	gx = A_11*ax[i]+A_12*ay[i]+A_13*az[i]+b1;
	gy = A_21*ax[i]+A_22*ay[i]+A_23*az[i]+b2;
	gz = A_31*ax[i]+A_32*ay[i]+A_33*az[i]+b3;

	cout << endl;
	cout << "a(i)" << endl;
	cout << gx << '\t' << gy << '\t' << gz << endl;
}

void sum_Ri_gi() {

	T acc_x = R_11*gx+R_12*gy+R_13*gz;
	T acc_y = R_21*gx+R_22*gy+R_23*gz;
	T acc_z = R_31*gx+R_32*gy+R_33*gz;

#ifdef USING_DOUBLE

	cout << endl;
	cout << "R(i)*a(i)" << endl;
	cout << acc_x << ' ' << acc_y << ' ' << acc_z << endl;

#endif

	// TODO Scaling factor?
	sx = sx + acc_x;
	sy = sy + acc_y;
	sz = sz + acc_z;
	return;
}

T f(const TV& x)
{

	set_sum_and_R0();

	for (int i=1; i<N; ++i) {

		cout << setprecision(4);
		cout << fixed ;
		cout << "-----------------------------------------------------" << endl;
		cout << "Step #" << i << endl;

		compute_G(i-1, x);

		update_R(); // R(i)=R(i-1)*G(i-1)

		normalize_R();

		compute_g(i);

		sum_Ri_gi();

	}

	return sx*sx + sy*sy + (sz/N-g_ref)*(sz/N-g_ref);
}

int main (int argc, char* argv[])
{

	if (argc!=2)
		throw "Please specify input file!";

	init(argv[1]);

#ifdef USING_HESS_TYPE

	NT  fx;
	NTV x(n_vars), Gfx(n_vars);
	NTM Hfx(n_vars, n_vars);

	for (int i=1; i<=n_vars; ++i)
		x[i] = NT(0.0);

	fghEvalH(f,x,fx,Gfx,Hfx);

	cout << "x: " << endl << x << endl;
	cout << "f(x):	" << endl << fx << endl;
	cout << "Gf(x): " << endl << Gfx << endl;

#endif

#ifdef USING_DOUBLE

	TV x = new T[n_vars+1];

	for (int i=1; i<=n_vars; ++i)
		x[i] = T(0.0);

	T fx = f(x);

#endif

	return 0;
}
