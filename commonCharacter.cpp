/*
1002. Find Common Characters

Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.

 

Example 1:

Input: words = ["bella","label","roller"]
Output: ["e","l","l"]
Example 2:

Input: words = ["cool","lock","cook"]
Output: ["c","o"]
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of lowercase English letters.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

//Time complexity O(n*m) where n is number of words, m is max length of word
// space complexity is O(26) ie. O(1)
vector<string> commonChars(vector<string>& words)
{
    vector<string> result;

    vector<int> wordToChar(26,0);

    // Form vector from a to z for word 0
    string temp=words[0];
    for(size_t i=0; i<temp.size(); i++)
    {
        wordToChar[temp[i]-'a']++;
    }

    

    for(size_t i=1; i<words.size(); i++)
    {
        // Form vector from a to z for word 1 to n
        vector<int> word1tonToChar(26,0);
        temp=words[i];
        for(size_t j=0; j<temp.size(); j++)
        {
            word1tonToChar[temp[j]-'a']++;
        }

        // Collect the minimum value of character in wordToChar
        // which gives the repetation of character count in all strings
        for(int k=0; k<26; k++)
        {
            int count=min(wordToChar[k],word1tonToChar[k]);
            wordToChar[k]=count;
        }

    }
    

    for(int i=0; i<26; i++)
    {
        //cout<<"\n Index--> "<<i<<" count is "<<wordToChar[i]<<endl;
        int numCharCount=wordToChar[i];
        //Collect the caracter with repetation count in result  
        while(numCharCount)
        {
            result.push_back(string(1,(i+'a')));
            numCharCount--;
        }
    }

    return result;
        
}

int main()
{
    vector<string> input={"bella","label","roller"};
    vector<string> output=commonChars(input);

    cout<<"\n Common Characters found are { ";
    for(size_t i=0; i<output.size(); i++)
    {
        cout<<output[i];
        if(i<(output.size()-1))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;
    return 0;
}