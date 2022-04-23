//
// Recursive Function
//
// Given the function F defined as:
// F(n) = F(n-1) + 2*(Fn-2) - 3F(n-3)
// with F(0) = 0, F(1) = 1, & F(2) = 2
//
// Write a function using top-down dynamic programming technique
// to calculate the value of F(n) with n >= 0
//
// Sample Input:
// Enter the value of n: 5
//
// Sample Output:
// The value of F(n) is: 7
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *M;

int top_down_dp(int n) {
    if (n == 0) {
        M[0] = 0;
        return 0;
    }

    if (n == 1) {
        M[1] = 1;
        return 1;
    }

    if (n == 2) {
        M[2] = 2;
        return 2;
    }

    if (M[n - 1] == -1) { // F(n-1) was not calculated
        // calculate F(n-1) and store in M
        M[n - 1] = top_down_dp(n - 1);
    }

    if (M[n - 2] == -1) { // F(n-2) was not calculated
        // calculate F(n-2) and store in M
        M[n - 2] = top_down_dp(n - 2);
    }
    
    if (M[n - 3] == -1) { // F(n-3) was not calculated
        // calculate F(n-3) and store in M
        M[n - 3] = top_down_dp(n - 3);
    }

    M[n] = M[n - 1] + 2 * M[n - 2] - 3 * M[n - 3];
    return M[n];
}

int main() {
    int n;
    int i;
    
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    M = malloc(sizeof(int) *(n + 1));
    for (i = 0; i <= n; i++) {
        M[i] = -1;
    }
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
}
