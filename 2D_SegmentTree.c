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

int finalResult(int max_size, int strip, int finalTree[][max_size], int qs, int qe, int si, int ss, int se) {
    
    if(qs <= ss && qe >= se)
        return finalTree[strip][si];
    
    else if(qs > se || qe < ss)
        return 0;
    
    else {
        
        int mid = (ss + se)/2;
        return finalResult(max_size, strip, finalTree, qs, qe, 2*si + 1, ss, mid) +
                    finalResult(max_size, strip, finalTree, qs, qe, 2*si + 2, mid + 1, se);
    }
}

int findFirstLevelTree(int cols, int max_size, int finalTree[][max_size], int y1, int y2, int qs, int qe, int si, int ss, int se) {
    
    if(qs <= ss && qe >= se) {
        
        return finalResult(max_size, si, finalTree, y1, y2, 0, 0, cols - 1);
    }
    else if(qs > se || qe < ss)
        return 0;
    
    else {
        
        int mid = (ss + se)/2;
        return findFirstLevelTree(cols, max_size, finalTree, y1, y2, qs, qe, 2*si + 1, ss, mid) +
               findFirstLevelTree(cols, max_size, finalTree, y1, y2, qs, qe, 2*si + 2, mid + 1, se);
    }
}

int updatedTrees() {
    
}

int main() {
	
	int rows, cols, queryNumber, queryType, x1, x2, y1, y2;
	
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
	
	printf("Enter number of queries\n");
	scanf("%d", &queryNumber);
	
	printf("Enter the queries\n");
	for(int i=0;i<queryNumber;i++) {
	    
	    printf("Enter query type and query coordinates in x1, x2, y1, y2 order\n");
	    scanf("%d", &queryType);
	    scanf("%d", &x1);
	    scanf("%d", &x2);
	    scanf("%d", &y1);
	    scanf("%d", &y2);
	    
	    if(queryType == 0)
	        printf("The sum of the sub matrix is : %d \n", findFirstLevelTree(cols, max_size, finalTree, y1, y2, x1, x2, 0, 0, rows - 1));
	    else if(queryType == 1) {
	        
	        if(updatedTrees()) {
	            
	            printf("value is updated\n");    
	        }
	        else
	            printf("Something went wrong. Couldn't updated the value\n");
	    }
	    else
	        printf("Wrong query type. Query type can be either 0 or 1\n");
	        
	}
	return 0;
}
