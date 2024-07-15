/*
227. Basic Calculator II

Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 105
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.
*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stack>

using namespace std;

int calculate(string s) 
{
    //to add ending digit
    s=s+'+';
    long long answer=0;

    stack<int> store;

    long long digit=0;
    char op='+';
    long long temp=0;
    

    for(size_t i=0; i<s.size(); i++)
    {
        // collect digits before any operand appears
        cout<<"\n here character is "<<s[i]<<endl;
        if(isdigit(s[i]))
        {
            digit=digit*10+(s[i]-'0');
        }
        else if( s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
        {
            switch(op)
            {
                // Cause it has to added to the ans
                case '+':
                    cout<<"\n here in plus digit is "<<digit<<endl;
                    store.push(digit);
                    break;
                // Cause it has to be subtracted to the ans, keep it as negative number
                case '-':
                    cout<<"\n here in minus digit is "<<digit<<endl;
                    digit=digit*(-1);
                    store.push(digit);
                    break;
                case '*':
                // multiply with previous value in stack, pop revious value and store present value
                    temp=store.top();
                    cout<<"\n here in multiplication previou digit is "<<temp<<" present digit is "<<digit<<endl;
                    store.pop();
                    digit=digit*temp;
                    store.push(digit);
                    break;
                case '/':
                // divide with previous value in stack, pop revious value and store present value
                    temp=store.top();
                    cout<<"\n here in division digit is "<<temp<<endl;
                    store.pop();
                    digit=temp/digit;
                    store.push(digit);
                    break;
                default:
                    break;    
            }
            // capture operation here to avoid bad division and multiplication
            // eg 3+2*2 to avoid 3*2
            op=s[i];
            digit=0;
            
        }
    }

    while(!store.empty())
    {
        cout<<"\nDigits are "<<store.top()<<endl;
        answer=answer+store.top();
        store.pop();
    } 

    return answer;
        
}

int main()
{
    string S="3+2*2";
    long long result=calculate(S);

    cout<<"\n Calculator result is "<<result<<endl;
    return 0;
}