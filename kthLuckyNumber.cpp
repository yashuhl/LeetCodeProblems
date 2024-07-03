/*
2802. Find The K-th Lucky Number

We know that 4 and 7 are lucky digits. Also, a number is called lucky if it contains only lucky digits.

You are given an integer k, return the kth lucky number represented as a string.

 

Example 1:

Input: k = 4
Output: "47"
Explanation: The first lucky number is 4, the second one is 7, the third one is 44 and the fourth one is 47.
Example 2:

Input: k = 10
Output: "477"
Explanation: Here are lucky numbers sorted in increasing order:
4, 7, 44, 47, 74, 77, 444, 447, 474, 477. So the 10th lucky number is 477.
Example 3:

Input: k = 1000
Output: "777747447"
Explanation: It can be shown that the 1000th lucky number is 777747447.
 

Constraints:

1 <= k <= 109
*/

#include<iostream>
#include<stdio.h>

using namespace std;

// using recurssion Time complexity is O(logn)
// base condition 1st element is 4 and 2nd lucky number is 7.
// For forming 8th lucky number, we want to remember 2nd lucky number and as 8 is even add 7 to its end
// For forming 7th lucky number, we want to remember 2nd lucky number and add as 7 is odd 4 to its end
string kthLuckyNumber(int k) 
{
    string temp;
    if(k==1)
    {
        temp="4";
        return temp;

    }
    else if(k==2)
    {
        temp="7";
        return temp;
    }

    int p=(k-1)/2;

    if( (k & 1) == 1)
    {
        return kthLuckyNumber(p)+"4";
    }
    else
    {
        return kthLuckyNumber(p)+"7";
    }
        
}

int main()
{
    // Case 1
    //int k=4;

    // Case 2
    int k=10;

    string result=kthLuckyNumber(k);

    cout<<"Asked " << k << "th Lucky number string is " << result<< endl;

    return 0;
}