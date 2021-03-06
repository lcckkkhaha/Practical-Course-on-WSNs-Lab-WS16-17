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

#include <iostream>
#include "GradTypeDyn.hpp"
#include "ObjectiveEvaluator.hpp"
#include "DataIO.hpp"
#include "InputData.hpp"

using namespace std;

using namespace gyro;

typedef GradType T;

void test() {

	const Input* data = read_file("oldal6.txt");

	ObjEval<T> obj(*data, cout, false);

	/*const double x[] = {
			0.001,
			0.002,
			0.003,
			-0.001,
			-0.001,
			0.002,
			-0.003,
			0.001,
			0.002,
			0.001,
			-0.001,
			0.002
	};*/

	const double x[] = {
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000,
			0.000
	};

	T vars[12];

	init_vars(vars, x);

	T sum = obj.f(vars);

	cout << obj.s_x() << endl << obj.s_y() << endl << obj.s_z() << endl;

	cout << endl;

	cout << "objective: " << sum << endl;

	return;

}

int main() {

	set_number_of_variables(12);

	test();

	return 0;
}
