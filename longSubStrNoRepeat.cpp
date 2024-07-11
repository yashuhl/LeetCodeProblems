/*
Given a string s, find the length of the longest 
substring
 without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/
#include<iostream>
#include<stdio.h>
#include<string>
#include<unordered_set>
#include<math.h>

using namespace std;

class Solution 
{
    public:
        // time complexity is O(n)
        // space complexity is O(n)
        int lengthOfLongestSubstring(string s) 
        {
            // create unordered set of string element i.e each char 
            unordered_set<char> setStrToChar;
             // collecting longest length
            int maxLength=0;

            //previous pointer
            int prev=0;

            for(size_t curr=0; curr<s.size(); curr++)
            {
                if(setStrToChar.count(s[curr])==0)
                {
                    // adding 1 as array size starts from 0
                    maxLength=max(maxLength,(int)curr-prev+1);

                }
                else
                {
                    while(setStrToChar.count(s[curr]))
                    {
                        setStrToChar.erase(s[prev]);
                        prev++;
                    }
                }
                setStrToChar.insert(s[curr]);
            }
            
            return maxLength;
        }
};

int main()
{
    string str="abcabcbb";

    Solution Solve;
    int answer=Solve.lengthOfLongestSubstring(str);

    cout<<" \n Longest Substring Without Repeating Characters is "<<answer<<endl;
    return 0;
}
