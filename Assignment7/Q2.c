//
// 0/1 Knapsack
//
// Given n items, where ith item has size si & value vi
// Put these items into a knapsack of capacity C
//
// Write a function using bottom-up dynamic programming technique
// to calculate the max values of the items that can fit in the knapsack
//
// Use the following recursive formula:
// M(i, j) = max {M(i-1, j), M(i-1, j-si) + Vj}
//
// Sample Input:
// Enter the number of items n: 4
// Enter the capacity C: 5
// Enter the sizes of items (as a list, separate by spacing: 2 1 3 2
// Enter the values of items (as a list, separate by spacing: 12 10 20 15
//
// Sample Output:
// The maximum value is: 37
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int bottom_up_dp(int n, int *s, int *v, int C) {
    //write your code here
}

int main() {
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
}
