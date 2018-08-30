/* This program doesn't do input validation. */

#include <stdio.h>
#include <math.h>

int getSum(int tree[], int lazy[], int qs, int qe, int si, int ss, int se) {
    
    //Checking if there are any pending updation left on this node
    if(lazy[si] != 0) {
        
        tree[si] += ((se - ss) + 1) * lazy[si];
        
        if(ss != se) {
            
            lazy[2*si + 1] += lazy[si];
            lazy[2*si + 2] += lazy[si];
        }
        
        lazy[si] = 0;
    }
    
    if(ss >= qs && se <= qe)
        return tree[si];
    
    else if(qs > se || qe < ss)
        return 0;
    
    else {
        
        int mid = (ss + se) / 2;
        return getSum(tree, lazy, qs, qe, 2*si + 1, ss, mid) + 
                    getSum(tree, lazy, qs, qe, 2*si + 2, mid + 1, se);
    }
    
}

void constructSTUtil(int tree[], int lazy[], int arr[], int ss, int se, int si)
{
    if (ss == se)
    {
        tree[si] = arr[ss];
        lazy[si] = 0;
        return;
    }
    
    int mid = (ss + se)/2;
    constructSTUtil(tree, lazy, arr, ss, mid, si*2+1);
    constructSTUtil(tree, lazy, arr, mid+1, se, si*2+2);
 
    tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
    lazy[si] = 0;
}
 
void constructST(int tree[], int lazy[], int arr[], int n)
{
    constructSTUtil(tree, lazy, arr, 0, n-1, 0);
}
 
void updateRange(int tree[], int lazy[], int diff, int us, int ue, int si, int ss, int se) {
    
    //Checking if there are any pending updation left on this node
    if(lazy[si] != 0) {
        
        tree[si] += ((se- ss) + 1) * lazy[si];
        
        if(ss != se) {
            
            lazy[2*si + 1] += lazy[si];
            lazy[2*si + 2] += lazy[si];
        }
        
        lazy[si] = 0;
    }
    
    if(ss > ue || se < us)
        return 0;
    
    else if(ss >= us && se <= ue) {
        
        tree[si] += ((se - ss) + 1) * diff;
        
        if(ss != se) {
            
            lazy[2*si + 1] += diff;
            lazy[2*si + 2] += diff;
        }
        return;
    }
    
    else {
        
        int mid = (ss + se) / 2;
        updateRange(tree, lazy, diff, us, ue, 2*si + 1, ss, mid);
        updateRange(tree, lazy, diff, us, ue, 2*si + 2, mid + 1, se);
        
        tree[si] = tree[2*si + 1] + tree[2*si + 2];
    }
}
 
 
int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int max_size = 2 * (int)pow(2, ((int)ceil(log2(n)))) - 1;
    
    int tree[max_size];
    int lazy[max_size];
    
    constructST(tree, lazy, arr, n);

    printf("Sum of values in given range = %d\n",
           getSum(tree, lazy, 4, 5, 0, 0, n-1));
 
    updateRange(tree, lazy, 10, 2, 2, 0, 0, n-1);
 
    printf("Sum of values in given range = %d\n",
           getSum(tree, lazy, 4, 5, 0, 0, n-1));
 
    return 0;
}


