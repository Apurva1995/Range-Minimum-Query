#include <stdio.h>
#include <math.h>

void preprocess(int n, int size, int arr[], int lookup[][size]) {
    
    //Initializing minimum for the intervals with length 1
    for(int i=0;i<n;i++)
        lookup[i][0] = i;
    
    //Computing minimum for smaller to bigger intervals
    for(int i=1;(1<<i)<=n;i++) {
        
        //Computing minimum for all intervals of size 2^j
        for(int j=0;(j+(1<<i)-1)<n;j++) {
            
            if(arr[lookup[j][i-1]] < arr[lookup[j+(1<<i-1)][i-1]])
                lookup[j][i] = lookup[j][i-1];
                
            else
                lookup[j][i] = lookup[j+(1<<i)-1][i-1];
        }
    }
}

int RMQ(int n, int size, int arr[], int lookup[][size], int l, int r) {
    
    int j = (int)log(r-l+1);
    
    if(arr[lookup[l][j]] < arr[lookup[r-(1<<j)+1][j]])
        return arr[lookup[l][j]];
    else
        return arr[lookup[r-(1<<j)+1][j]];
}

int main(void) {
	
	int arr[] = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    int n = sizeof(arr)/sizeof(arr[0]);
    int size = ceil(log(n));
    
    int lookup[n][size];
    
    preprocess(n, size, arr, lookup);
    
    printf("Minimum in the given range is : %d", RMQ(n, size, arr, lookup, 7, 8));
    
	return 0;
}

