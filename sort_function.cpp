// Function to create the sorted list
void sort_index()
{

int size = 2*((P->getVar())-(level)); // twice the size of unsatisifiable variables
int temp_arr[size];	// temp array to store the varaible occurence

// create unsorted index array
int x = 1;
for(int j = 0; j< size; j+=2)
{
	indx_arr[j] = x;
	indx_arr[j+1] = -x;
	x+=1;
}

int s=0;
// count literal occurence
for(int p = 0; p < (size/2); p++)	//loop over all columns
{
	int pos_cnt = 0;
	int neg_cnt = 0;
	for(int q = 0; q < num_active; q++)	// loop over remaining rows
	{
		int rw = activeClauses[q];	//current row
		if(in_arr[rw][p] == 1){pos_cnt+=1;}
		if(in_arr[rw][p] == -1){neg_cnt+=1;}
	}
	temp_arr[s] = pos_cnt;
	temp_arr[s+1] = neg_cnt;
	s+=2;
}

int temp;
for(int i = 0; i < size; i++)
{
	for(int j = 0; j < size-1; j++)
	{
		if(temp_arr[j] < temp_arr[j+1])
		{
			//sort temp_arr
			temp = temp_arr[j];
			temp_arr[j] = temp_arr[j+1];
			temp_arr[j+1] = temp;

			// sort indx_arr
			temp = indx_arr[j];
			indx_arr[j] = indx_arr[j+1];
			indx_arr[j+1] = temp;
		}
	}
}}
