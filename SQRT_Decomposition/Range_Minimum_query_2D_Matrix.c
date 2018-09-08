/*This code doesn't do input validations and the range for queries as well as index for updation are hard coded.*/

#include <stdio.h>
#include <math.h>
#include <limits.h>
#define MAX_SIZE 100


int createFirstLevelMat(int firstSize, int MAX_SIZE, int rows, int cols, int firstLevelMat[][MAX_SIZE], int matrix[][cols]) {
    
    int count;
    
    for(int i=0;i<rows;i++) {
        
        count = -1;    
        for(int j=0;j<cols;j++) {
            
            if(j%firstSize == 0) {
                
                count++;
                firstLevelMat[i][count] = INT_MAX;
            }
            
            if(firstLevelMat[i][count] > matrix[i][j]) {
                
                firstLevelMat[i][count] = matrix[i][j];
            }
        }
    }
    
    return count;
}

int createFinalLevelMat(int secondSize, int MAX_SIZE, int MAX_SIZE, int rows, int finalFirstLevelSize, int finalSecondLevelSize, int firstLevelMat[][MAX_SIZE], int finalLevelMat[][MAX_SIZE]) {
    
    int count;
    
    for(int i=0;i<=finalFirstLevelSize;i++) {
        
        count = -1;
        for(int j=0;j<rows;j++) {
            
            if(j % secondSize == 0) {
                
                count++;
                finalLevelMat[count][i] = INT_MAX;
            }
            if(finalLevelMat[count][i] > firstLevelMat[j][i]) {
                
                finalLevelMat[count][i] = firstLevelMat[j][i];
            }
        }
    }
    
    return count;
}

int getMin(int x1, int x2, int y1, int y2, int firstSize, int secondSize, int MAX_SIZE, int cols, int matrix[][cols], int firstLevelMat[][MAX_SIZE], int finalLevelMat[][MAX_SIZE]) {
    
    int min = INT_MAX;
    int tempY1 = y1;
    
    while(x1 % secondSize != 0 && x1 <= x2) {
        
        while(tempY1 % firstSize != 0 && tempY1 <= y2) {
            
            if(min > matrix[x1][tempY1])
                min = matrix[x1][tempY1];
            
            tempY1++;
        }
        
        while(tempY1 + firstSize-1 <= y2) {
            
            if(min > firstLevelMat[x1][tempY1/firstSize])
                min = firstLevelMat[x1][tempY1/firstSize];
            
            tempY1 += firstSize;
        }
        
        while(tempY1 <= y2) {
            
            if(min > matrix[x1][tempY1])
                min = matrix[x1][tempY1];
            
            tempY1++;
        }
        
        x1++;
    }
    
    tempY1 = y1;
    while(x1 + secondSize-1 <= x2) {
        
        while(tempY1 % firstSize != 0 && tempY1 <= y2) {
            
            int temp = x1;
            int minTemp = INT_MAX;
            
            while(temp <= x2) {
                
                if(minTemp > matrix[temp][tempY1])
                    minTemp = matrix[temp][tempY1];
                
                temp++;
            }
            
            if(min > minTemp)
                min = minTemp;
            
            tempY1++;
        }
        
        while(tempY1 + firstSize-1 <= y2) {
            
            if(min > finalLevelMat[x1/secondSize][tempY1/firstSize])
                min = finalLevelMat[x1/secondSize][tempY1/firstSize];
                
            tempY1 += firstSize;
        }
        
        while(tempY1 <= y2) {
            
            int temp = x1;
            int minTemp = INT_MAX;
            
            while(temp <= x2) {
                
                if(minTemp > matrix[temp][tempY1])
                    minTemp = matrix[temp][tempY1];
                
                temp++;
            }
            
            if(min > minTemp)
                min = minTemp;
            
            tempY1++;
        }
        
        x1 += secondSize;
    }
    
    tempY1 = y1;
    while(x1 <= x2) {
        
        while(tempY1 % firstSize != 0 && tempY1 <= y2) {
            
            if(min > matrix[x1][tempY1])
                min = matrix[x1][tempY1];
            
            tempY1++;
        }
        
        while(tempY1 + firstSize-1 <= y2) {
            
            if(min > firstLevelMat[x1][tempY1/firstSize])
                min = firstLevelMat[x1][tempY1/firstSize];
            
            tempY1 += firstSize;
        }
        
        while(tempY1 <= y2) {
            
            if(min > matrix[x1][tempY1])
                min = matrix[x1][tempY1];
            
            tempY1++;
        }
        
        x1++;
    }
    
    return min;
}


void update(int x, int y, int val, int cols, int firstSize, int secondSize, int MAX_SIZE, int matrix[][cols], int firstLevelMat[][MAX_SIZE], int finalLevelMat[][MAX_SIZE]) {
    
    matrix[x][y] = val;
    
    int start = y/firstSize;
    start *= firstSize;
    int min = matrix[x][start];
    
    for(int i=start + 1;i< start + firstSize;i++) {
        
        if(min > matrix[x][i])
            min = matrix[x][i];
    }
  
    firstLevelMat[x][y/firstSize] = min;
        
    start = x/secondSize;
    start *= secondSize;
    min = firstLevelMat[start][y/firstSize];
    
    for(int i=start + 1;i< start + secondSize;i++) {
        
        if(min > firstLevelMat[i][y/firstSize])
            min = firstLevelMat[i][y/firstSize];
    }
    
    finalLevelMat[x/secondSize][y/firstSize] = min;
}

int main(void) {
	
	int rows, cols, firstLevelSize, secondLevelSize, firstSize, secondSize, finalFirstLevelSize, finalSecondLevelSize;
	
	printf("Enter number of rows and cols\n");
	scanf("%d", &rows);
	scanf("%d", &cols);
	
	int matrix[rows][cols];
	
	printf("Enter values in matrix\n");
	for(int i=0;i<rows;i++) {
	    
	    for(int j=0;j<cols;j++) {
	        
	        scanf("%d", &matrix[i][j]);
	    }
	}
	
	firstSize = sqrt(cols);
	//firstLevelSize = firstSize + 1;
	
	int firstLevelMat[rows][MAX_SIZE];
	
    finalFirstLevelSize = createFirstLevelMat(firstSize, MAX_SIZE, rows, cols, firstLevelMat, matrix);
	
	secondSize = sqrt(rows);
    	//secondLevelSize = secondSize + 1;
	
	int finalLevelMat[MAX_SIZE][MAX_SIZE];
	
	finalSecondLevelSize = createFinalLevelMat(secondSize, MAX_SIZE, MAX_SIZE, rows, finalFirstLevelSize, finalSecondLevelSize, firstLevelMat, finalLevelMat);
	
	//Finding minimum in the range x1=0, x2=0, y1=0, y2=1
	printf("Minimum value present in the given range is : %d\n", getMin(1, 2, 1, 4, firstSize, secondSize, MAX_SIZE, cols, matrix, firstLevelMat, finalLevelMat));
    
    //Updating value at x=2 and y = 2
    update(2, 2, 2, cols, firstSize, secondSize, MAX_SIZE, matrix, firstLevelMat, finalLevelMat);
    
    //Finding minimum in the range x1=0, x2=0, y1=0, y2=1
	printf("Minimum value present in the given range is : %d ", getMin(1, 2, 1, 4, firstSize, secondSize, MAX_SIZE, cols, matrix, firstLevelMat, finalLevelMat));
    
	return 0;
}

