/* Filename: knapsack.cpp
 * Description: The command line program knapsack.cpp takes in one parameter,
 *              an input file name. The input file specified by the input
 *		file name should describe an instance of the knapsack problem
 *		using the format
 *		[knapsack capacity][number of items]
 *		[value item 1][weight item 1]
 *		...
 *		The program solves the knapsack problem using dynamic 
 *		programming to cache solutions to subproblems.
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define IN_IDX 1
#define EXPECTED_ARGS 2

using namespace std;

// run dynamic programming knapsack algorithm
int knapsack(int W, vector<int>& values, vector<int>& weights) {

	// number of items
	unsigned int n = values.size(); 

	// dynamically allocate a (W+1) x 2 array
	int ** A = new int*[W+1];
	for(int i = 0; i < W+1; ++i) {
		A[i] = new int[2];
	}

	// Initialization
	for(int i = 0; i < W+1; ++i) {
		A[i][0] = 0;
	}

	// Memoization. For j = 1 to n, 
	// fill the second column of matrix.
	// Then copy it to the first column.
	// A[i,j] gives maximum value of a knapsack that
	// uses only first j items and has capacity at most i.
	// If item j is not in an optimal solution satisfying
	// these constraints, A[i,j] = A[i,j-1]. Otherwise,
	// A[i,j] = A[i-weights[j-1], j-1] + values[j-1].
	for(int j = 1; j <= n; ++ j) {
		for(int i = 0; i < W+1; ++i) {
			A[i][1] = ( (i-weights[j-1] >= 0) ? 
			  max(A[i][0], A[i-weights[j-1]][0] + values[j-1]) :
			  A[i][0] );
		}	

		// copy second column to first column
		for(int i = 0; i < W+1; ++i) {
			A[i][0] = A[i][1];
		}	
	}
	

	// save last entry of matrix
	int result = A[W][1];

	// no memory leaks here
	for(int i = 0; i < W+1; ++i) {
		delete [] A[i];
	}
	delete [] A;

	return result;

}

// get capacity, fill the values and weights vectors
bool loadFile(char* filename, int* W, vector<int>& values, 
		vector<int>& weights) {

	// input file stream
	ifstream * in = new ifstream(filename);

	// Raise an error if file can't be read
	if( in->eof() ){
		cerr << "Failed to read " << filename << endl;
		delete in;
		return false;
	}	

	// used to parse input file
	string line, temp;

	// used for parsing line
	stringstream ss;

	// used to check if we read file correctly
	unsigned int numItems;

	// store knapsack capacity and total number items
	getline(*in, line);
	ss << line; // storing line into stringstream
	ss >> temp; // extract knapsack capacity
	stringstream(temp) >> *W; // store knapsack capacity
	temp = ""; // clear temp
	ss >> temp; // extract number items
	stringstream(temp) >> numItems;
	temp = ""; // clear temp
	ss.str(""); // reset string stream to be empty
	ss.clear(); // reset error flags

	// store value and weights of all items
	while(getline(*in, line)) {
		ss << line; // storing line in stringstream
		ss >> temp; // extract value
		values.push_back(stoi(temp)); // store value
		temp = ""; // clear temp
		ss >> temp; // extract weight
		weights.push_back(stoi(temp)); // store weight

		// reset the string stream to be empty and
		// reset error flags
		ss.str("");
		ss.clear();
	}

	// check that you read in correct number items
	if( values.size() != numItems || weights.size() != numItems ) {
		cerr << "Incorrect Parse!" << endl;
		delete in;
		return false;
	}

	// no memory leaks here
	delete in;

	return true;

}

int main(int argc, char** argv) {

	// check for arguments
	if( argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments" << endl;
		return(-1);
	}

	// stores values of items
	vector<int> myValues;

	// stores weights of items
	vector<int> myWeights;

	// capacity of knapsack
	int capacity;

	// if we can correctly extract the knapsack's capacity and
	// the values and weights of all items from the input file,
	// perform dynamic programming algorithm and return the
	// maximum value of the knapsack
	if( loadFile(argv[IN_IDX], &capacity, myValues, myWeights) ){
		int knapValue = knapsack(capacity, myValues, myWeights);
		cout << "Knapsack Value: " << knapValue << endl;
	}	

}
