/*
140. Word Break II

Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
 

Constraints:

1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
Input is generated in a way that the length of the answer doesn't exceed 105.

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<unordered_set>

using namespace std;

void recCall(string stringUnderTest, int start,
             const unordered_set<string> &wordDictSet, string &curr,
             vector<string> &result)
{

    //base case when we reach the end of the string s
    if(start == int(stringUnderTest.length()))
    {
        result.push_back(curr);
        return;
    }

    for(int end=start+1; end<=int(stringUnderTest.length()); end++)
    {
        //substring from start to end-start
        string word=stringUnderTest.substr(start,end-start);

        //if the formed word is in set
        if(wordDictSet.count(word))
        {
            //from word
            string previous;
            if(curr.empty())
            {
                previous=word;
            }
            else
            {
                previous = curr + " " + word;
            }
            // call recursive function where new start is constrcuted end 
            // new current is constructed previous
            recCall(stringUnderTest,end,wordDictSet,previous,result);
        }
    }

}


//Time complexity: O(2^n) we have possibility of creating two branches at each step
//Space complexity: O(2^n) stack space is used for calling out at each branch
vector<string> wordBreak(string s,vector<string> &wordDict)
{
    // convert wordDict from vector format to unordered set
    unordered_set<string> wordDictSet(wordDict.begin(),wordDict.end());

    //answer vector
    vector<string> answer;

    // curr string to track of answer formation in recurssive call
    // initially its empty
    string curr="";

    recCall(s,0,wordDictSet,curr,answer);

    return answer;

    
}

int main()
{
    string s="catsanddog";
    vector<string> wordDict={"cat","cats","and","sand","dog"};

    vector<string> output = wordBreak(s,wordDict);

    cout<<"\n output is \n"<<endl;
    for(size_t i=0; i<output.size(); i++)
    {
        cout<<output[i]<<endl;
    }
    return 0;
}