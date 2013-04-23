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

int dimacs_arr[8][3] = {
{-1,2,3},
{1,3,4},
{1,3,-4},
{1,-3,4},
{1,-3,-4},
{-2,-3,4},
{-1,2,-3},
{-1,-2,3}};

// -1 represents complement, 0 represents doesn't exist
int in_arr[8][4] ={
{-1,1,1,0},
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
int indx_arr[8];	// index array, this will be sorted
int temp_arr[8];	// array that has occurence count

// Function to get watched variables from unsatisfied clauses
void update_watch_var(int row, int col)
{
for(int i = 0; i < row; i++)
{
	int cnt = 0;
	for(int j = 0; j < col; j++)
	{
		if(clause_stat[i] == 0)	// if status unsatisfiable
		{
			if(cnt == 2){break;}
			if((dimacs_arr[i][j] != 0)&&(cnt == 0)){watch_var1[i] = dimacs_arr[i][j]; cnt+=1; clause_stat[i] = 2; j+=1;}	// first watch var
			if((dimacs_arr[i][j] != 0)&&(cnt == 1)){watch_var2[i] = dimacs_arr[i][j]; cnt+=1; clause_stat[i] = 0;}		// second watch var
		}	
	}
}}


// Function to create the initial list
void create_list(int row,int col)
{
int x = 1;
for(int j = 0; j< 8; j+=2)
{
	indx_arr[j] = x;
	indx_arr[j+1] = -x;
	x+=1;
}
int s=0;
// count literal occurence
for(int p = 0; p < col; p++)
{
	int pos_cnt = 0;
	int neg_cnt = 0;
	for(int q = 0; q < row; q++)
	{
		if(in_arr[q][p] == 1){pos_cnt+=1;}
		if(in_arr[q][p] == -1){neg_cnt+=1;}
	}
	temp_arr[s] = pos_cnt;
	temp_arr[s+1] = neg_cnt;
	s+=2;
}}


// Sorting the array
void merge(int,int,int);
void mergesort(int low, int high)
{
int mid;
if(low<high)
{
	mid=(low+high)/2;
      	mergesort(low,mid);	//divide list into two parts
        mergesort(mid+1,high);
	merge(low,mid,high);	// sort the two parts, repeat
}}

void merge(int low, int mid, int high)
{
	int h,i,j,tmp[8],k;
	h =low;
	i = low;
	j = mid+1;
	while((h<=mid)&&(j<high))
	{
		if(temp_arr[h] <= temp_arr[j])
		{
			tmp[i]=indx_arr[h];
			h++;
		}
		else
		{
			tmp[i] = indx_arr[j];
			j++;
		}
		i++;
	}
	if(h>mid)
	{
		for(k=j;k<=high;k++)
		{
			tmp[i]=indx_arr[k];
			i++;
		}
	}
	else
	{
		for(k=h;k<=mid;k++)
		{
			tmp[i]=indx_arr[k];
			i++;
		}
	}
	for(k=low;k<=high;k++){indx_arr[k]=tmp[k];}
}


int main()
{
update_watch_var(m,n);
//for(int i = 0; i < m; i++){cout << "\t" << watch_var1[i] << "\t" << watch_var2[i] << "\n";}
create_list(m,n);
//for(int g = 0; g < 2*n; g++){cout<<"\n"<<temp_arr[g];}
mergesort(0,2*n);
for(int e = 0; e < 2*n; e++){cout<<"\n"<<indx_arr[e];}
return 0;
}

