/* Author: Ali Khatai, May 2020
Constructing order 2 Carmichael numbers
*/
// main.pp used to test timings for the enumeration and order2primes function

#include <iostream>
#include <cmath>
#include "primality.h"
#include <vector>
#include "Factorization.h"
#include "enumeration.h"
#include<math.h>
using namespace std;
using namespace NTL;

// print function used to print contents of a vector
void printg(vector<ZZ> const& input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
}


int main() {

	// declare an instance of the factorization class and two vectors for its data members
    Factorization L; vector<ZZ> pr; vector<ZZ> pow;
	
	// add the prime factors and their powers to two vectors as ints. for this main
	// we have used L= 110683043236846080
	vector<int> prims = { 2,3,5,7,11,13,17,23,29,31,37,41};
	vector<int> powrs = { 9,4,1,1,1,1,1,1,1,1,1,1};
	
	// use a for loop to convert the int values in the previous two vectors to ZZ and add them
	// to the pr and pow ZZ vectors which will initiate an instance of the factorization class
	for (int k = 0; k < prims.size(); ++k) {
		pr.push_back(to_ZZ(prims.at(k)));
		pow.push_back(to_ZZ(powrs.at(k)));
	}


	// declare L with pr and pow
    L = Factorization(pr, pow);
	
	// use the factorProduct to assign the L value as a ZZ to a variable. also print it to ensure
	// the L value is correct
	ZZ l = L.factorProduct();
	cout <<"L= "<< l << "\n";

	// make a vector for the bound values
	vector<ZZ> bounds;

	// calculate the square root of L 
	ZZ y = SqrRoot(l);

	// append L and its square roots to the bounds vector
	bounds.push_back(l); bounds.push_back(y);

	// start a for loop to add values from 10^2 to 10^20 taking two steps for the power to the bounds vector
	// 
	for (long i = 2; i < 21; i += 2) {
        bounds.push_back(power_ZZ(10, i));
	}

    // use another loop to add sqrt(L)/(10^i) to the bounds. I starts from 2 and goes to 6.
	for (long i = 2; i < 7; i++) {
		bounds.push_back(y / power_ZZ(10, i));
	}
 
	//use another loop to add sqrt(L) * (10 ^ i) to the bounds.I starts from 2 and goes to 6.
	for (long i = 2; i < 7; i++) {
		bounds.push_back(y * power_ZZ(10, i));
	}

	// make a vector to save the list of primes 
    vector<ZZ> primes;
	
	// use a for loop that iterates through the bounds vector and test each bound
	for (int j = 0; j < bounds.size(); ++j) {
	
    // declare a double to sum the time for 5 runs to take average
	double time = 0;
	
	// use another loop to test the bound five times to get average of five runs
	for (int c = 0; c < 5; ++c) {
		// get the start time
		double t0 = GetTime();
		// construct divisors of L with the current bound
		vector<ZZ> lst = enumerate(L, bounds.at(j));
		// construct the list of primes
		primes = order2_primes(lst, L);
		// get the end time
		double t1 = GetTime();
		// calculate the run time
		double curtime = t1 - t0;
		// sum up time for average
		time = time + curtime;
	}
	
	// print the current bound
	cout << "bound=" << bounds.at(j)<<"\n";
	// calculate the average for 5 runs
	double avg_time = time / 5;
	
	// count the number of primes
	count(primes);
	// the the average time for 5 runs
	cout << "the average time of 5 runs:" << avg_time;
	cout << "______________________________________________________________________________________________________\n\n";
	}


}






