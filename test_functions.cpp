// test functions as well as ideas for DPLL, will be added to sat solver after testing

#include <iostream>
#include <cstdlib>
using namespace std;

/* using the example from lecture slides
F=
(a'+b+c)
(a+c+d)
(a+c+d')
(a+c'+d)
(a+c'+d')
(b'+c'+d)
(a'+b+c')
(a'+b'+c)
*/

// this is what the input parser is saving right now
int dimacs__arr[8][3] = 
{
	{-1,2,3},
	{1,3,4},
	{1,3,-4},
	{1,-3,4},
	{1,-3,-4},
	{-2,-3,4},
	{-1,2,-3},
	{-1,-2,3}
};

// need to convert it to this form
// -1 represents complement, 0 represents doesn't exist
int in_arr[8][4] = 
{
	{-1,1,1,0},
	{1,0,1,1},
	{1,0,1,-1},
	{1,0,-1,1},
	{1,0,-1,-1},
	{0,-1,-1,1},
	{-1,1,-1,0},
	{-1,-1,1,0}
};

/* Do a merge sort of all literals to make variable decision
Worst case : nlog(n)
worst case memory: n
n is the number of variables so it won't be very high anyways
*/

/*
end result should look like this :
{1,3,-3,-1,4,2,-2,-4}
*/

// count occurence of each literal and save it, sort the literals based on their occurence

int main()
{

// ASSIGNING VALUES TO LITERALS:
/*
start from the literal first in the list
assign literal=1(use in_arr to decrease computations)
e.g. 
for a = 0: 
	set all -1 entries in first column to a 0
	set all such rows as GREEN
	leave all other rows to default YELLOW

for c = 1:
	set all 1 entries to 0 in column 3 
	set all such rows as GREEN
	leave all other rows to defualt YELLOW

Note: just need to read one column depending upon the literal	
*/

// WATCH VARIABLES:
/*
read each row and save the first two non zero elements in memory
if two variables not available then that row is a unit clause and need to be tagged somehow
all unit clause rows need to be compared with each other, if any pairs exist then it is a conflictA

OR make next decision based on the unit clause rather than from the sorted list, if any row ends up being 0 then it is a conflict
*/

return 0;
}

