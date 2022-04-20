#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *M;

int fib_recursive(int n)
{
    //write your code here
}

int top_down_dp(int n)
{
    //write your code here

}

int bottom_up_dp(int n)
{
    //write your code here
}
 
void main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    //allocate the memory array
    M = malloc(sizeof(int) * (n+1));
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, fib_recursive(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                M[i] = -1;
                
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, top_down_dp(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                M[i] = -1;
                
            clock_t begin = clock();
            printf("The result of Fib(%d) is: %d \n", n, bottom_up_dp(n));
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Running time is: %f seconds \n", time_spent);
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}