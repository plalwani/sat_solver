int low,int mid,int high)
{
 int h,i,j,temp[high],k;
  h=low;
   i=low;
    j=mid+1;

     while((h<=mid)&&(j<=high))
      {
        if(temp_arr[h]<=temp_arr[j])
	  {
	     b[i]=indx_arr[h];
	        h++;
		  }
		    else
		      {
		         b[i]=indx_arr[j];
			    j++;
			      }
			        i++;
				 }
				  if(h>mid)
				   {
				     for(k=j;k<=high;k++)
				       {
				          b[i]=indx_arr[k];
					     i++;
					       }
					        }
						 else
						  {
						    for(k=h;k<=mid;k++)
						      {
						         b[i]=indx_arr[k];
							    i++;
							      }
							       }
							        for(k=low;k<=high;k++) indx_arr[k]=b[k];
								}

