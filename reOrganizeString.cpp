/*
767. Reorganize String

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

 

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<unordered_map>
#include<iterator>
#include<algorithm>

using namespace std;

// construct N Choose R subset
string reorganizeString(string s) 
{
    //create hash map for lower case english letters.
    std::unordered_map<char,int> sUMap;
    for(size_t i=0; i<s.size(); i++)
    {
        sUMap[s[i]]++;
    }
    cout << "\n Hash map of string with individual characters"<<endl;
    for(auto it=sUMap.begin(); it!=sUMap.end(); it++)
    {
        cout<< it->first << "\t" << it->second <<endl;
    }

    // storing in vector for sorting as per value
    vector<pair<char,int>> pairs;
    for(auto& pair:sUMap)
    {
        pairs.push_back(pair);
    }
    
    cout<< "\n Content in vector pairs in un sorted order"<<endl;
    for(auto& pair:pairs)
    {
        cout<<pair.first<<"\t"<<pair.second<<endl;
    }
    sort(pairs.begin(),pairs.end(),
    [](auto& a, auto& b)
    {
        return a.second > b.second;
    }
    );
    cout<<"\n Content in vector pairs in sorted order"<<endl;
    for(auto& pair:pairs)
    {
        cout<< pair.first<<"\t"<<pair.second<<endl;
    }

    //Form string as per problem
    // If highest repeating number is more than rounded half value , no string can be formed
    // First place highest repeating char in even position till string length
    // then place in odd position
    string temp=s;
    int index=0;
    int stringSize=s.size();
    int stringValidCount=0;
    stringValidCount = (stringSize+1)/2;

    for(auto& pair:pairs)
    {
        int count=pair.second;
        cout<<"I am here with count = "<< count <<"String size = "<< stringSize<<endl;
        if(count <= stringValidCount)
        {
            cout<<"I am here 2" <<endl;
            while(count)
            {
                cout<<"I am here 3 with letter " << pair.first <<endl;
                temp[index]=pair.first;
                count--;
                index=index+2;
                if(index >= stringSize)
                {
                    index=1;
                }
            }
        }
        else
        {
            temp="";
            return temp;
        }
    }

    return temp;
}

int main()
{
    string s = "aaab";

    string result=reorganizeString(s);
    cout<<" Reorganized string = " << result <<endl;
    
    return 0;
}