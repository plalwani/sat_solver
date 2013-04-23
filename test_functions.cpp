// Test function to update watch variables and create a sorted list of literals using merge sort

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

int dimacs_arr[8][3] = {{-1,2,3},
{1,3,4},
{1,3,-4},
{1,-3,4},
{1,-3,-4},
{-2,-3,4},
{-1,2,-3},
{-1,-2,3}};

// -1 represents complement, 0 represents doesn't exist
int in_arr[8][4] = {{-1,1,1,0},
{1,0,1,1},
{1,0,1,-1},
{1,0,-1,1},
{1,0,-1,-1},
{0,-1,-1,1},
{-1,1,-1,0},
{-1,-1,1,0}};

int m = 8; // num. of rows
int n = 4; // num. of cols

int clause_stat[8] = {0,0,0,0,0,0,0,0}; // unsatisfied initially
int watch_var1[8];	// watched variable 1
int watch_var2[8];	// watched variable 2

void update_watch_var(int row, int col)
{
for(int i = 0; i < m; i++)
{
	int cnt = 0;
	for(int j = 0; j < n; j++)
	{
		if(clause_stat[i] == 0)
		{
			if((dimacs_arr[i][j] != 0)&&(cnt == 0)){watch_var1[i] = dimacs_arr[i][j]; cnt+=1; clause_stat[i] = 2; j+=1;}
			if((dimacs_arr[i][j] != 0)&&(cnt == 1)){watch_var2[i] = dimacs_arr[i][j]; cnt+=1; clause_stat[i] = 0;}
			if(cnt == 2){break;}
		}	
	}
}}

int main()
{
update_watch_var(m,n);
for(int i = 0; i < 8; i++){cout << "\t" << watch_var1[i] << "\t" << watch_var2[i] << "\n";}
return 0;
}

