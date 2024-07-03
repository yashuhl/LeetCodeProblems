/*
2781. Length of the Longest Valid Substring

You are given a string word and an array of strings forbidden.

A string is called valid if none of its substrings are present in forbidden.

Return the length of the longest valid substring of the string word.

A substring is a contiguous sequence of characters in a string, possibly empty.

 

Example 1:

Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
Output: 4
Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
It can be shown that all other substrings contain either "aaa" or "cb" as a substring. 
Example 2:

Input: word = "leetcode", forbidden = ["de","le","e"]
Output: 4
Explanation: There are 11 valid substrings in word: "l", "t", "c", "o", "d", "tc", "co", "od", "tco", "cod", and "tcod". The length of the longest valid substring is 4.
It can be shown that all other substrings contain either "de", "le", or "e" as a substring. 
 

*/
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>

using namespace std;

void findSubSetHelper(string &S, vector<string> &res, string &temp,int index, vector<string> &forbid )
{
    int sLength=S.size();
    //int tempLength=temp.size();
    //int forbidLength = forbid.size();

    if(index==sLength)
    {
        res.push_back(temp);
        return;
    }
    // inclusive
    temp.push_back(S[index]);
    findSubSetHelper(S,res,temp,index+1,forbid);

    // exclusive
    temp.pop_back();
    findSubSetHelper(S,res,temp,index+1,forbid);

}
// Time O(N*2powerN)
vector<string> findSubSet(string &S, vector<string> &forbid)
{
    string temp;
    vector<string> res;
    int index=0;
    findSubSetHelper(S,res,temp,index,forbid);
    return res;
}

int findValidLength(vector<string> &result, vector<string> &forbid)
{
    vector<string> valid;
    int resLength=result.size();
    int forbidLength = forbid.size();
    int maxLength=0;

    
    // using two pointer O(string Subset length* fobid string array length)
    for(int i=0; i< resLength; i++)
    {
        int j;
        for(j=0; j<forbidLength; j++)
        {
            if( result[i].find(forbid[j]) != string::npos )
            {
                break;
            }

        }
        if(j==forbidLength)
        {
            int reultSubSetLength=result[i].length();
            maxLength=max(maxLength,reultSubSetLength);

            valid.push_back(result[i]);
        }
    }

    cout<< "SubSet of valid string is" << endl;
    for(size_t i=0; i<valid.size(); i++)
    {
        cout<< valid[i] << endl;
        
    }

    return maxLength;

}

/*
Using Dynamic sliding window technique
    We are moving in the right direction when the problem:
    involves a data structure that is iterable (arrays, strings, etc.)
    asks to find a subsection (substring/subarray) that meets a desired condition/target value (e.g. max/min/common/longest/shortest/contains)
    does NOT have a size constraint
*/

/*
Time Complexity
The time complexity of the given code can be analyzed by going through the nested loops and operations within them. 
The outer loop runs for len(word) times, where 'word' is the input string and its length is denoted by 'n'. 
The inner loop at worst case runs for a maximum of 10 iterations since it looks back from the current position k
only up to 10 characters because of max(end - 10, start - 1) condition.

Hence, in the worst-case scenario, for each character we might look at the next 10 characters to check if the substring 
is in the forbidden set. Since checking whether a substring is in a set is O(1) operation due to hashing, 
the worst case would consider these constant time checks up to 10 times for each character.

Combining both loops, the worst-case time complexity can therefore be simplified to O(n), where each character is checked against a 
constant number of potential forbidden substrings.

Space Complexity
The space complexity consists of the space required for the set 'forbiddenSet' and a few integer variables.
Since 'forbiddenSet' contains the forbidden substrings, its space complexity will be O(m), 
where 'm' is the total length of all forbidden substrings combined.

The other variables, maxLength, 'start', 'end', and 'k' are constant space, adding O(1) to the total space complexity.
Therefore, the total space complexity of the code is O(m + 1) which simplifies to O(m), 
denoting the space taken up by the set of forbidden substrings.

*/


/**
 * Finds the longest valid substring that does not contain any forbidden substrings.
 * @param word The main string in which to look for the substring.
 * @param forbidden A vector of forbidden substrings.
 * @return maxLength The length of the longest valid substring.
 */
int longestValidString(string &word, vector<string> &forbidden)
{
    
    // Convert the forbidden vector to a set for efficient lookup using Hash set
    // O(forbid set length)
    unordered_set <string> forbiddenSet(forbidden.begin(),forbidden.end());

    // Variable to store the answer, i.e., the length of the longest valid substring
    int maxLength=0;

    // Variable to store the length of the word
    int wordLength=word.size();

    // Two pointers technique to iterate through the string
    // `start` denotes the start index of the current valid substring
    // `end` denotes the end index of the current valid substring
    // in the problem 10 is the max forbidden string element size
    for(int start=0,end=0; end<wordLength; end++)
    {
        // define dynamic sliding window
        cout<< "printing dynamic sliding window string" <<endl;
        for(int k=end; k>max(end-10,start-1); k--)
        {
             // If a forbidden substring is found
             cout << "end is = "<<end<<" k is = " << k << " ";
             cout << word.substr(k,end-k+1) << endl;
             if(forbiddenSet.count(word.substr(k,end-k+1)))
             {
                //move the start pointer past it
                start=k+1;
                break;
             }
        }
        cout << endl;
        //move the start pointer past it
        maxLength=max(maxLength, end-start+1);
    }
    return maxLength;
}



int main()
{
    string S="leetcode";
    vector<string> forbid ={"co","d"};

    vector<string> res;
    
    res=findSubSet(S,forbid);

    cout<< "SubSet of string " << S << " is" << endl;
    for(size_t i=0; i<res.size(); i++)
    {
        cout<< res[i] << endl;
        
    }

    int length=findValidLength(res,forbid);
    cout << "longest Valid Sub String is " <<length<<endl;

    /*
    brute force method is a learning exercise did which still lacks the solution of removing the
    subset "A substring is a contiguous sequence of character in a string" possibly empty.
    eg: ltcod is wrong as leetcode has le or e has forbidden string, so valid string should not have the content before.
    */  


    length=longestValidString(S,forbid);
    cout << "longest Valid Sub String using dynamic sliding window is " <<length<<endl;
    

    return 0;
}