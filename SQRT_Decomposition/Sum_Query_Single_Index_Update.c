/*This code doesn't do input validations and query and updation ranges are hardcoded.*/

#include <stdio.h>
#include <math.h>

void decomposeArray(int decomposedArray[], int arr[], int n, int blckSize) {
    
    int count = -1;
    for(int i=0;i<n;i++) {
        
        if(i % blckSize == 0) {
            
            count++;
            decomposedArray[count] = 0;
        }
        
        decomposedArray[count] += arr[i];
    }
}

int findSum(int decomposedArray[], int arr[], int n, int l, int r, int blckSize) {
    
    int sum = 0;
    while(l%blckSize && l <= r) {
        
        sum += arr[l];
        l++;
    }
    
    while(l + blckSize <= r) {
        
        sum += decomposedArray[l/blckSize];
        l += blckSize;
    }
    
    while(l <= r) {
        
        sum += arr[l];
        l++;
    }
    
    return sum;
}

int main(void) {
	
	int n, blckSize, diff;
	
	printf("Enter size of array\n");
	scanf("%d", &n);
	
	blckSize = sqrt(n);
	
	int arr[n];
	int decomposedArray[blckSize + 1];
	
	printf("Enter elements in array\n");
	for(int i=0;i<n;i++) {
	    
	    scanf("%d", &arr[i]);
	}
	
	decomposeArray(decomposedArray, arr, n, blckSize);
	
	//Quering for the sum from 2 to 8
	printf("Sum of the elements in given range is : %d\n", findSum(decomposedArray, arr, n, 1, 10, blckSize));
	
	//Updating the value at index at 7 with 10
	diff = 10 - arr[7];
	arr[7] = 10;
	
	decomposedArray[(int)ceil(7/blckSize)] += diff;
	
	printf("Sum of the elements in given range is : %d\n", findSum(decomposedArray, arr, n, 2, 8, blckSize));
	
	return 0;
}

