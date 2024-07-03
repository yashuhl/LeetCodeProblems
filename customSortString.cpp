/*
791. Custom Sort String

You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.

Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.

Return any permutation of s that satisfies this property.

 

Example 1:

Input: order = "cba", s = "abcd"

Output: "cbad"

Explanation: "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".

Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.

Example 2:

Input: order = "bcafg", s = "abcd"

Output: "bcad"

Explanation: The characters "b", "c", and "a" from order dictate the order for the characters in s. The character "d" in s does not appear in order, so its position is flexible.

Following the order of appearance in order, "b", "c", and "a" from s should be arranged as "b", "c", "a". "d" can be placed at any position since it's not in order. The output "bcad" correctly follows this rule. Other arrangements like "bacd" or "bcda" would also be valid, as long as "b", "c", "a" maintain their order.

 

Constraints:

1 <= order.length <= 26
1 <= s.length <= 200
order and s consist of lowercase English letters.
All the characters of order are unique.
*/

#include<iostream>
#include<stdio.h>
#include<string>
#include<unordered_map>

using namespace std;

// Time Complexity O(s.size())
// Space complexity O(26)

string customSortString(string order, string s) 
{
    // map the alphabets frequency max 26 alphabet for string s
    unordered_map<char,int> mapSCharFreq;
    for(size_t i=0; i<s.size(); i++)
    {
        mapSCharFreq[s[i]]++;
    }

    // if the char of s string in order push the same char and same sort order to answer
    string ans;
    for(size_t j=0; j<order.size(); j++)
    {
        //while loop is required to place all the similar character before next one appears
        // for example if e appaers 2 times and its sorting will be same for 2 e's as in order string
        while(mapSCharFreq[order[j]]>0)
        {
            ans.push_back(order[j]);
            mapSCharFreq[order[j]]--;
        }

    }

    // push the rest content of s to answer in the order it appears in unordered map
    for(auto it:mapSCharFreq)
    {
        // while loop to collect all the extra same char present in s string which are not in order string
        while(it.second > 0 )
        {
            ans.push_back(it.first);
            it.second--;
        }
    }
    return ans;
        
}

int main()
{
    string order="bcafg";
    string s="abcd";

    string ans=customSortString(order, s);

    cout<<"\n Order string is \""<<order<<"\" s string is \""<<s<<"\" answer string is \""<<ans<<"\""<<endl;
    return 0;
}