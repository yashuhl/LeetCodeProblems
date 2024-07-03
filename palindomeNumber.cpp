/*
9. Palindrome Number

Given an integer x, return true if x is a 
palindrome
, and false otherwise.

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 

Constraints:

-231 <= x <= 231 - 1
*/

#include<iostream>
#include<stdio.h>

using namespace std;

// Time complexity is O(n)
bool isPalindrome(int x) 
{
    if(x<0)
    {
        return false;
    }
    long long temp=x;
    long long reverse=0;

    while(temp!=0)
    {
        // modulus collects unit place value
        int digit=temp%10;
        reverse=reverse*10+digit;
        // division by 10 gives value without unit place
        temp=temp/10;
    }
    
   cout << " The reverse of number is "<<reverse<<endl;

   if(x==reverse)
   {
    return true;
   }
   return false;
}

int main()
{
    //int palindrome=65056;
    int palindrome=-121;
    bool result = isPalindrome(palindrome);

    if(result==true)
    {
        cout << " The number "<<palindrome<<" is a palindrome"<<endl;
    }
    else
    {
        cout << " The number "<<palindrome<<" is not a palindrome"<<endl;
    }
    
    return 0;
}