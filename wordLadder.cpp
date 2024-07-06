/*
127. Word Ladder

A transformation sequence from word beginWord to word endWord using a dictionary wordList
is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, 
return the number of words in the shortest transformation sequence from beginWord to endWord, 
or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is
 "hit" -> "hot" -> "dot" -> "dog" -> "cog", which is 5 words long.
 "hit" -> "hot" -> "lot" -> "log" -> "cog", which is also 5 words long

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<unordered_set>
#include<queue>

using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
{

    // collect the string in vector to unordered set
    unordered_set<string> wordSet;
    
    for(size_t i=0; i<wordList.size(); i++)
    {
        wordSet.insert(wordList[i]);
    }

    // if end word is not in set return 0
    if(wordSet.find(endWord) == wordSet.end())
    {
        return 0;
    }

    // use BFS methos i.e queue DSA to store the possible transformation of words
    // as per given problem, one letter at a time
    // By using BFS a layer of next possible neighbours will be formed

    // queue with pair of sting and its int to track the number of convertion 
    // reaching from begin to end transformation
    queue<pair<string, int>> q;
    // push initial pair, beginWord and 1
    q.push({beginWord,1});

    while(!q.empty())
    {
        // take the pair at front to process
        auto curr=q.front();
        string str=curr.first;
        
        int deapth=curr.second;
        cout<<"\n string here is "<<str<<" and its depth is "<<deapth<<endl;
        q.pop();

        if(str==endWord)
        {
            return deapth;
        }

        // For the length of the word under test
        for(size_t i=0; i<str.size(); i++)
        {
            string temp=str;
            // change for considered ith bit character to change from a to z
            for(char j='a'; j<='z'; j++)
            {
                temp[i]=j;
                // if the changed word is present in set
                // push to queue-> new found value and increment depth and delete from set
                // using count inbuilt function for unordered_set as it indicates 1 if present else 0
                // unique prperty of set , cannot have duplicates so count can be 1 or 0
                if(wordSet.count(temp))
                {
                    q.push({temp,deapth+1});
                    wordSet.erase(temp);
                }
            }
        }

    }
    return 0;
        
}

int main()
{
    string beginWord="hit";
    string endWord="cog";

    vector<string> wordList={"hot","dot","dog","lot","log","cog"};

    int length=ladderLength(beginWord, endWord, wordList);
    cout<<"\n The length of begin word "<<beginWord<<" transformed into end word "<<endWord<<" is "<<length<<endl;
    return 0;
}