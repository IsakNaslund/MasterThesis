#include "stdafx.h"
#include "MatixTest.h"

#include "include/armadillo"

MatixTest::MatixTest()
{
	arma::mat A(3, 3);
	A(0, 0) = -3;
	A(0, 1) = 2;
	A(0, 2) = 4;
	A(1, 0) = 1;
	A(1, 1) = 2;
	A(1, 2) = 2;
	A(2, 0) = 4;
	A(2, 1) = 7;
	A(2, 2) = 1;
	A.print("A: ");

	arma::colvec b(3, arma::fill::ones);
	b(2) = 2;
	b.print("b: ");

	arma::mat x = arma::solve(A, b);
	x.print("x: ");
}


MatixTest::~MatixTest()
{
}
