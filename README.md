# Knapsack_Big

## Usage
To compile, type "g++ -o knapsack_big knapsack_big.cpp". To run, type "./knapsack_big knapsack_big.txt"

## Introduction
The command line program knapsack_big.cpp takes in one parameter,
an input file name. The input file specified by the input
file name should describe an instance of the knapsack problem
using the format

[knapsack capacity][number of items]

[value item 1][weight item 1]
 
...

The program solves the knapsack problem using dynamic 
programming to cache solutions to subproblems.

The main difference between this program and knapsack.cpp
is that we only use a 2 column array to cache the solutions
to subproblems.
