#include <stdio.h>
#include <math.h>


int constructFirstLevelTree(int rows, int cols, int max_size, int mat[][cols], int firstLevelTree[][max_size], int strip, int si, int ss, int se) {
                                                
        if(ss == se) {
            
            firstLevelTree[strip][si] = mat[strip][ss];
            return firstLevelTree[strip][si];
        }
        else {
            
            int mid = (ss + se)/2;
            firstLevelTree[strip][si] = constructFirstLevelTree(rows, cols, max_size, mat , firstLevelTree, strip, 2*si + 1, ss, mid) +
                                        constructFirstLevelTree(rows, cols, max_size, mat, firstLevelTree, strip, 2*si + 2, mid + 1, se);
            return firstLevelTree[strip][si];
        }
}

void constructFinalTree(int max_size, int firstLevelTree[][max_size], int finalTree[][max_size], int si, int ss, int se) {
    
    if(ss == se) {
        
        for(int i=0;i<max_size;i++)
            finalTree[si][i] = firstLevelTree[ss][i];
    }
    else {
        
        int mid = (ss + se)/2;
        constructFinalTree(max_size, firstLevelTree, finalTree, 2*si + 1, ss, mid);
        constructFinalTree(max_size, firstLevelTree, finalTree, 2*si + 2, mid + 1, se);
        
        for(int i=0;i<max_size;i++)
            finalTree[si][i] = finalTree[2*si + 1][i] + finalTree[2*si + 2][i];
    }
    
}

int main() {
	
	int rows, cols;
	
	printf("Enter number of rows and columns\n");
	scanf("%d", &rows);
	scanf("%d", &cols);
	
	int mat[rows][cols];
	
	printf("Enter values in matrix\n");
	for(int i=0;i<rows;i++) {
	    
	    for(int j=0;j<cols;j++) {
	        
	        scanf("%d", &mat[i][j]);
	    }
	}
    
    int x = (int)(ceil(log2(cols))); 
    int max_size = 2*(int)pow(2, x) - 1;	
	
	int firstLevelTree[rows][max_size];
	int finalTree[max_size][max_size];
	
	for(int i=0;i<rows;i++)
	    constructFirstLevelTree(rows, cols, max_size, mat, firstLevelTree, i, 0, 0, cols-1);
	
	constructFinalTree(max_size, firstLevelTree, finalTree, 0, 0, rows - 1);
	for(int i=0;i<max_size;i++) {
	    
	    for(int j=0;j<max_size;j++) {
	        
	        printf("%d ", finalTree[i][j]);
	    }
	    printf("\n");
	}
	
	return 0;
}
