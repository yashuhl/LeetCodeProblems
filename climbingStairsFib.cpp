/*
70. Climbing Stairs

You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

 

Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>

using namespace std;

/*
Approach 1

Explanation: The recursive solution uses the concept of Fibonacci numbers to solve the problem. 
It calculates the number of ways to climb the stairs by recursively calling the climbStairs function 
for (n-1) and (n-2) steps. 
However, this solution has exponential time complexity (O(2^n)) due to redundant calculations.
space complexity is O(1)

*/
int climbStairsRecursive(int n) 
{
    //Fibannoci series
    if(n==0 || n==1)
    {
        return 1;
    }
    int result=climbStairsRecursive(n-1)+climbStairsRecursive(n-2);

    return result;
    
}

//dynamic programming for fibonacci
// by memoization we can reduce time complexity from O (2 power n) to O(n)
// space complexity is O(n)
//dynamic programming for fibonacci
// by memoization we can reduce time complexity from O (2 power n) to O(n)
// space complexity is O(n)

/*
Approach 2: Memoization
Explanation: The memoization solution improves the recursive solution by introducing memoization,
which avoids redundant calculations. We use an unordered map (memo) to store the already 
computed results for each step n. Before making a recursive call, 
we check if the result for the given n exists in the memo. 
If it does, we return the stored value; otherwise, 
we compute the result recursively and store it in the memo for future reference.
*/
int climb(int n,unordered_map<int,int> &memo) 
{
    //Fibannoci series

    // for n==2 case tweeking fib series base case yields 2
    // n-1 + n-2 
    // 1+0 ==> 1+1
    // 2
    if(n==0 || n==1)
    {
        return 1;
    }
    // if memoization does not exist
    if(memo.find(n)==memo.end())
    {
        memo[n]=climb(n-1,memo)+climb(n-2,memo);
    }
    
    // if memoization exist return that
    return memo[n];
    
}

int climbStairs(int n) 
{
    unordered_map<int,int> memo;
    return climb(n, memo);
}


/*
Approach 3: Tabulation
Explanation: The tabulation solution eliminates recursion and uses a bottom-up approach 
to solve the problem iteratively. It creates a DP table (dp) of size n+1 to store 
the number of ways to reach each step. The base cases (0 and 1 steps) are initialized to 1 
since there is only one way to reach them. 
Then, it iterates from 2 to n, filling in the DP table by summing up the values for the previous two steps. 
Finally, it returns the value in the last cell of the DP table, 
which represents the total number of ways to reach the top.
Time Complexity = O(n)
Space Complexity = O(n)
*/
int climbStairsTabulization(int n) 
{

    vector<int> dp(n+1);
    dp[0] = dp[1] = 1;
    
    for (int i = 2; i <= n; i++) 
    {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

/*
Approach 4: Space Optimization
Explanation: The space-optimized solution further reduces the space complexity
by using only two variables (prev and curr) instead of an entire DP table. 
It initializes prev and curr to 1 since there is only one way to reach the base cases (0 and 1 steps). 
Then, in each iteration, it updates prev and curr by shifting their values. 
curr becomes the sum of the previous two values, and prev stores the previous value of curr
Time complexity is O(n)
Space complexity is O(1)
*/
int climbStairsSpace(int n) 
{
    int prev = 1;
    int curr = 1;
    for (int i = 2; i <= n; i++) 
    {
        int temp = curr;
        curr = prev + curr;
        prev = temp;
    }
    return curr;
}


int main()
{
    // using recurssive method

    int n=5;

    int result = climbStairsSpace(n);
    cout<<"\n distinct ways to climb " <<n<<" steps top is "<<result;
    return 0;
}