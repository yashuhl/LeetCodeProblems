/*

1152: Analyze User Website Visit Pattern

You are given two string arrays username and website and an integer array timestamp. 
All the given arrays are of the same length and the tuple [username[i], website[i], timestamp[i]] 
indicates that the user username[i] visited the website website[i] at time timestamp[i].

A pattern is a list of three websites (not necessarily distinct).

For example, ["home", "away", "love"], ["leetcode", "love", "leetcode"], and ["luffy", "luffy", "luffy"] 
are all patterns. The score of a pattern is the number of users that visited all the 
websites in the pattern in the same order they appeared in the pattern.

For example, if the pattern is ["home", "away", "love"], the score is the number of users x 
such that x visited "home" then visited "away" and visited "love" after that.
Similarly, if the pattern is ["leetcode", "love", "leetcode"], 
the score is the number of users x such that x visited "leetcode" then visited "love" and visited "leetcode" 
one more time after that.
Also, if the pattern is ["luffy", "luffy", "luffy"], the score is the number of users x such that x visited 
"luffy" three different times at different timestamps.
Return the pattern with the largest score. If there is more than one pattern with the same largest score, 
return the lexicographically smallest such pattern.
 

Example 1:

Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], 
timestamp = [1,2,3,4,5,6,7,8,9,10], 
website = ["home","about","career","home","cart","maps","home","home","about","career"]
Output: ["home","about","career"]
Explanation: The tuples in this example are:
["joe","home",1],["joe","about",2],["joe","career",3],["james","home",4],
["james","cart",5],["james","maps",6],["james","home",7],["mary","home",8],
["mary","about",9], and ["mary","career",10].
The pattern ("home", "about", "career") has score 2 (joe and mary).
The pattern ("home", "cart", "maps") has score 1 (james).
The pattern ("home", "cart", "home") has score 1 (james).
The pattern ("home", "maps", "home") has score 1 (james).
The pattern ("cart", "maps", "home") has score 1 (james).
The pattern ("home", "home", "home") has score 0 (no user visited home 3 times).
Example 2:

Input: username = ["ua","ua","ua","ub","ub","ub"], timestamp = [1,2,3,4,5,6], 
website = ["a","b","a","a","b","c"]
Output: ["a","b","a"]
 

Constraints:

3 <= username.length <= 50
1 <= username[i].length <= 10
timestamp.length == username.length
1 <= timestamp[i] <= 109
website.length == username.length
1 <= website[i].length <= 10
username[i] and website[i] consist of lowercase English letters.
It is guaranteed that there is at least one user who visited at least three websites.
All the tuples [username[i], timestamp[i], website[i]] are unique.
*/

#include<iostream>
#include<stdio.h>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<vector>

using namespace std;

// Time complexity O(npower3)
// space complexity O(npower2)
vector<string> mostVisitedPattern(vector<string> &username, vector<string> &website, vector<int> &timestamp)
{
    // creating a two-dimensional map: unordered_map< key_1_type, map< key_2_type, value_type> > object;
    // create unordered map for [username(key1) ->(map) [timestamp(key2) -> website(value)]]
    // used map for timestamp and website, where using map the key value pair will be sorted as per timestamp
    // this way the users and its associated website order is sorted as per visited timestamp in 
    // ascending order
    unordered_map<string, std::map<int,string>> usertimewebsiteMap;

    for(size_t i=0; i<username.size(); i++)
    {
        usertimewebsiteMap[username[i]][timestamp[i]] = website[i];
    }

    cout<<"\n tuples are \n";
    for(auto user=usertimewebsiteMap.begin(); user != usertimewebsiteMap.end(); user++)
    {
        for(auto time=user->second.begin(); time !=user->second.end(); time++)
        {
            cout<< user->first<<" , "<<time->first<<" , "<<time->second<<endl;;
        }
    }

    // iterate through two-dimentional map
    // collect max frequency of {w1,w2,w3} pattern visit
    // key->freq[w1+" "+w2+ " "+w3]=value->count in ascending order
    map<string,int> freq;

    // assume maxfrequency is 0
    int maxfreq=0;
    for(auto [user,time] : usertimewebsiteMap)
    {
        // have unordered set of 3 website string constructed from details inside usertimewebsiteMap
        // can use unordered_set or vector
        unordered_set<string> stringstream;
        //vector<string> stringstream;

        // first website
        for(auto itr1=time.begin(); itr1 != time.end(); itr1++)
        {
            // second website
            for(auto itr2=next(itr1); itr2 != time.end(); itr2++)
            // third website
            {
                for(auto itr3=next(itr2); itr3 != time.end(); itr3++)
                {
                    stringstream.insert(itr1->second+" "+itr2->second+" "+itr3->second);
                    //stringstream.push_back(itr1->second+" "+itr2->second+" "+itr3->second);
                }
            }
        }

        cout<< "\nSet elements are "<<endl;
        for(auto ss:stringstream)
        {
            cout<<ss<<endl;
            freq[ss]++;
            // collect the max frequency
            maxfreq=max(maxfreq,freq[ss]);
        }
    }

    string result;
    for(auto maxfreqcount:freq)
    {
        // collect first lexograghic max frequency wensite patterns
        if(maxfreqcount.second==maxfreq)
        {
            result=maxfreqcount.first;
            break;
        }
    }

    vector<string> resultArray;
    string temp;
    for(size_t x=0; x<result.size(); x++)
    {
        if(result[x] == ' ')
        {
            resultArray.push_back(temp);
            temp="";

        }
        else
        {
            temp=temp+result[x];
        }
    }
    if((temp.size()) != 0)
    {
        resultArray.push_back(temp);

    }

    return resultArray;
}

int main()
{
    vector<string> username = {"joe","joe","joe","james","james","james","james","mary","mary","mary"};
    vector<string> website = {"home","about","career","home","cart","maps","home","home","about","career"};
    vector<int> timestamp = {1,2,3,4,5,6,7,8,9,10};

    vector<string> result = mostVisitedPattern(username,website,timestamp);

    cout<<"\n website pattern { ";
    for(size_t i=0; i<result.size(); i++)
    {
        cout<<result[i];
        if(i!=result.size()-1)
        {
            cout << " , ";

        }
    }
    cout<<" }"<<endl;

    return 0;

}