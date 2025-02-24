/*
7. Reverse Integer

Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

 

Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
Example 3:

Input: x = 120
Output: 21
 

Constraints:

-231 <= x <= 231 - 1
*/

#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;
int reverse(int x) 
{
    long long rev=0;
    long long temp=x;

    while(temp!=0)
    {
        // reverse using formula from modulus to get unit digit value
        // and divide by 10 to get value without unit digit.
        int digit=temp%10;
        rev=rev*10+digit;
        temp=temp/10;

        // restrict to + or - 2 power 31 value
        // to avoid buffer overflow
        if(rev > pow(2,31) || rev<-pow(2,31))
        {
            return 0;
        }

    } 
    
    return rev;
}

int main()
{
    int x=1534236469;
    int rev=reverse(x);

    cout<<"The number "<<x<<"'s reverse number is "<<rev<<endl;
    return 0;
}