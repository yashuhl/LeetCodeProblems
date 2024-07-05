/*
472. Concatenated Words

Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.

 

Example 1:

Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
"dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Example 2:

Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
 

Constraints:

1 <= words.length <= 104
1 <= words[i].length <= 30
words[i] consists of only lowercase English letters.
All the strings of words are unique.
1 <= sum(words[i].length) <= 105
*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<unordered_set>

using namespace std;

// Dynamic Programming problem
// use tabulization
// Complexity
// Time complexity: O(N*(M^2))
// Space complexity: O(N*M)
// where N : size of words
// M : size of string with maximum length
vector<string> findAllConcatenatedWordsInADict(vector<string>& words) 
{
    // convert string vector to unordered set (having hash table DSA underhood) for beter lookup
    unordered_set<string> usString;

    for(size_t i=0; i<words.size(); i++)
    {
        usString.insert(words[i]);
    }

    cout<<"\n Print unordered set \n";
    unordered_set<string>::iterator itr;
    for(itr=usString.begin(); itr!=usString.end(); itr++)
    {
        cout<< " string is "<<*itr<<endl;;
    }

    vector<string> result;

    for(size_t i=0; i<words.size(); i++)
    {
        // individual word inside words vector size
        int wordSize=words[i].size();
        cout<<"\n word under test is "<<words[i]<<endl;

        // create a wordSize+1 DP of int vector to indicate the word made up of other word
        vector<int> dp(wordSize+1,0);

        // initialize first words letter to 1 in DP int vector
        dp[0]=1;

        for(int j=0; j<wordSize; j++)
        {
            /* C++ continue statement is a loop control statement that forces the program control to 
               execute the next iteration of the loop. As a result, the code inside the loop following 
               the continue statement will be skipped and the next iteration of the loop will begin. */
            cout<<"dp[j] at "<< j <<" is "<<dp[j]<<endl;

            // as dp[0] is 1 it will not iterate for unwanted cases
            // eg: for cat - first round cat is fine
            // at is not taken
            // t is not taken
            // empty string is not taken
            if( !dp[j])
            {
                continue;
            }
            // kept wordSize+1 for this for loop as substr function will take start and end similar to array size
            // if j=0 and k=3 the word cat will be taken
            // substr(j=0,k-j=3) of words[0] is cat
            for(int k=j+1; k<=wordSize; k++)
            {
                // k-j < wordSize restrict the last trailing extra character of k when we are checking k=wordSize
                // The unordered_set::count() function is a built-in function in C++ STL which is used to count
                // occurrences of a particular element in an unordered_set container. 
                // As the unordered_set container does not allows to store duplicate elements so this function is
                // generally used to check if an element is present in the container or not. 
                // The function returns 1 if the element is present in the container otherwise it returns 0.
                cout<<"here k is " <<k <<"and j is "<<j<<"and substring is "<<words[i].substr(j,k-j)<<endl;
                if( (k-j < wordSize) && usString.count(words[i].substr(j,k-j)) )
                {
                    // end of word which forms concatination is set to 1;
                    // eg: in catsdogcats
                    // dp[3] is set to 1, dp[6] is set to 1, dp[10] is set to 1
                    dp[k]=1;
                    cout<<"\nSet last letter of existing word in set to 1 for dp[k]\n";
                }

            }
            cout<<"\n";

            cout<<"\ndp array value is {";
            for(size_t n=0; n<dp.size();n++)
            {

                cout<<dp[n];
                if(n<dp.size()-1)
                {
                    cout<<" , ";
                }
            }
            cout<<"} "<<endl;

            if(dp[wordSize])
            {
                result.push_back(words[i]);
                break;
            }
        }
    }
    return result;
}

int main()
{
    vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};

    vector<string> result = findAllConcatenatedWordsInADict(words);

    cout<<"\nConcatenated words are { ";
    for(size_t i=0; i<result.size(); i++)
    {
        cout<<result[i];
        if(i<result.size()-1)
        {
            cout<<" , ";
        }
    }
    cout<<" }";
    return 0;
}