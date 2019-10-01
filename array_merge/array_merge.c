#include "array_merge.h"
#include "../mergesort/mergesort.h"
#include <stdlib.h>
#include <stdio.h>

int* de_dupe(int* ar, int size){
	//the present digit we want to remove copies of
	int present_digit = ar[0];
	//the index we are copying to, and thus the number of distinct elements
	//starts from one, as the first value is always unique so far
	int copy_index = 1;
	//We start from one, as we have already processed the zeroeth element
	for(int i=1; i<size; i++){
		//if this is not the digit we are ignoring, we need to change things
		if(ar[i] != present_digit){
			//as i is always greater than or equal to copy_index, we can use
			//ar[copy_index] as a scratch area
			//so first we get the new digit to ignore
			present_digit = ar[i];
			//now we make a copy in the start of the array
			ar[copy_index] = present_digit;
			//and update the count/offset
			copy_index++;
		}
	}
	//then we make our new array to return, size k+1
	int* return_array = (int *) calloc(copy_index+1, sizeof(int));
	return_array[0] = copy_index;
	//and now we copy over the digits and return
	for(int i=1; i<=copy_index; i++){
		return_array[i] = ar[i-1];
	}
	free(ar);
	return return_array;
}
int* array_merge(int num_arrays, int* sizes, int** values) {
  // This is obviously broken. It has the right type, though, eh?
	//number of numbers involved
	int total_count = 0;
	//add up the sizes
	for (int i=0; i < num_arrays; i++){
	total_count = total_count + sizes[i];
	}
	printf("Total count %d \n",total_count);
	if(total_count ==0){	
		int * return_array = (int *) calloc(0,sizeof(int));
		return return_array;
	}
	//make a new array to be returned, with the size k+1
	int* scratch_array =(int * ) calloc(total_count,sizeof(int));
	//if we have an empty list, we can't do anything more, so skip out early
	int copy_index = 0;
	//append all into the scratch array
	//by looping through every array
	for (int i=0; i < num_arrays; i++){
		//and every element
		for(int j=0; j<sizes[i]; j++){
			scratch_array[copy_index] = values[i][j];
			copy_index++;
		}
	}
	//and then we sort the large array
	mergesort(total_count, scratch_array);
	//then we depupe and count in a subfunction
	int* clean_array= de_dupe(scratch_array,total_count);	
	//our work here is done
	
	return clean_array;
}

