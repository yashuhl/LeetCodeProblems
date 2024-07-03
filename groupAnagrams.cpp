/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
*/

#include<iostream>
#include<string.h>
#include<stdio.h>
#include<vector>
#include<list>
#include<unordered_map>
#include<algorithm>

using namespace std;

//Time complexity O(n*mlogm)
// n is size of strs, m is max strs element length
vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
    vector<vector<string>> res;
    unordered_map<string, vector<string>> mapAnagrams;

    for(size_t i=0; i<strs.size(); i++)
    {
        string temp=strs[i];
        //sort the string
        sort(temp.begin(),temp.end());

        // place the origin anagram string in the same list of sorted string
        mapAnagrams[temp].push_back(strs[i]);
    }

    // collect mapAnagram string to vector of vector in the order of anagrams
    for(auto ptr:mapAnagrams)
    {
        res.push_back(ptr.second);
    }

    return res;
}

int main()
{
    vector<string> strs = { "eat","tea","tan","ate","nat","bat" };
    cout <<"\n array of strings are \n";
    for(size_t k=0; k<strs.size(); k++)
    {
        cout<<strs[k]<<"\t";
    }
    cout<<endl;

    vector<vector<string>> result = groupAnagrams(strs);

    cout<<"\n Group of anagrams are \n";
    for(size_t i=0; i<result.size(); i++)
    {
        for(size_t j=0; j<result[i].size(); j++)
        {
            cout << result[i][j] << "\t";
        }
        cout <<endl;
    }
    return 0;
}