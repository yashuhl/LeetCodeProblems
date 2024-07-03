/*

2055. Plates Between Candles
                                                                                                                                                                                                   
There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.

You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. 
A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.

For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
Return an integer array answer where answer[i] is the answer to the ith query.

 

Example 1:

ex-1
Input: s = "**|**|***|", queries = [[2,5],[5,9]]
Output: [2,3]
Explanation:
- queries[0] has two plates between candles.
- queries[1] has three plates between candles.
Example 2:

ex-2
Input: s = "***|**|*****|**||**|*", queries = [[1,17],[4,5],[14,17],[5,11],[15,16]]
Output: [9,0,0,0,0]
Explanation:
- queries[0] has nine plates between candles.
- The other queries have zero plates between candles.
 

Constraints:

3 <= s.length <= 105
s consists of '*' and '|' characters.
1 <= queries.length <= 105
queries[i].length == 2
0 <= lefti <= righti < s.length
*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

// self implemented brute force
// O(Queries length(Sub string))
// space Queries length sub string + Queries length output
vector<int> countPlatesBwCandels(string &s, vector<vector<int>> &queries)
{
    vector<int> out;

    //vector<string> temp;
    string test;

    for(size_t m=0; m<queries.size(); m++)
    {
        int lefti=queries[m][0];
        int righti=queries[m][1];
        test=s.substr(lefti,(righti-lefti+1));

        cout<<" sub string is = " << test <<endl;

        int candleStart=-2;
        int candleEnd=2;

        int plates=0;
        int count=0;

        for(size_t i=0; i<test.size(); i++)
        {
            if(test[i]=='|' && (candleStart!=1))
            {
                candleStart=1;
            }
            else if(test[i]=='|' && (candleEnd!=1))
            {
                candleEnd=1;
            }
            if(test[i]=='*' && candleStart==1)
            {
                count++;
            }
            if(candleStart == candleEnd)
            {
                candleStart=-2;
                candleEnd=2;
                plates=plates+count;
                count=0;
                i--;
            }


        }
        out.push_back(plates);

        //temp.push_back(s.substr(lefti,(righti-lefti+1)));
    }

    return out;
}

// prefix sum method
vector<int> countPlatesBwCandelsOofN(string &s, vector<vector<int>> &queries)
{
    vector<int> starCount(s.length());
    vector<int> lefti(s.length(),-1);
    vector<int> righti(s.length(),-1);

    int stringSize=s.size()-1;

    //candleCount[0] = s[0] == '|'  ? 1 : 0 ;
    if( s[0] == '*' )
    {
        starCount[0]=1;
    }
    
    for(int i=1; i<=stringSize; i++)
    {
        if(s[i]=='*')
        {
            starCount[i]=starCount[i-1]+1;
        }
        else
        {
            starCount[i]=starCount[i-1];
        }
    }

    cout << "             index are          ";
    for(size_t i=0; i<starCount.size(); i++)
    {
        cout << i << " " ;
    }
    cout << endl;

    cout << "             stars are          " ;
    for(size_t i=0; i<starCount.size(); i++)
    {
        cout << starCount[i] << " " ;
    }
    cout << endl;

    if( s[0] == '|' )
    {
        lefti[0]=0;
    }
    for(int i=1; i<=stringSize; i++)
    {
        if(s[i]=='|')
        {
            lefti[i]=i;
        }
        else
        {
            lefti[i]=lefti[i-1];
        }
    }

    cout<<"nearest left candles index are  ";
    for(size_t i=0; i<lefti.size(); i++)
    {
        cout << lefti[i] << " " ;
    }
    cout << endl;

    if( s[stringSize] == '|' )
    {
        righti[stringSize]=stringSize;
    }
    for(int i=stringSize-1; i>=0; i--)
    {
        if(s[i]=='|')
        {
            righti[i]=i;
        }
        else
        {
            righti[i]=righti[i+1];
        }
    }

    cout<<"nearest right candles index are ";
    for(size_t i=0; i<righti.size(); i++)
    {
        cout << righti[i] << " " ;
    }
    cout << endl;

    vector<int> out(queries.size());
    for(size_t m=0; m<queries.size(); m++)
    {
        int queryStart=queries[m][0];
        int queryEnd=queries[m][1];

        int startCandleIndex=righti[queryStart];
        int endCandleIndex=lefti[queryEnd];

        int count=0;

        if(startCandleIndex >= 0 && endCandleIndex >=0 && startCandleIndex<endCandleIndex)
        {
            count = starCount[endCandleIndex] - starCount[startCandleIndex];

        }
        out[m]=count;
    }

    
    return out;
}

int main()
{
    
    // case 1
    
    //string s = "**|**|***|";
    //vector<vector<int>> queries = { {2,5},{5,9}};
    
    
    //case 2
    
    string s = "***|**|*****|**||**|*";
    vector<vector<int>> queries = {{1,17},{4,5},{14,17},{5,11},{15,16}};
    
    /*
    vector<int> out = countPlatesBwCandels(s,queries);

    cout<<"Output of counting Plates between Candels\n";
    for(size_t i=0; i< out.size(); i++ )
    {
        cout<<out[i]<<"\t";
    }
    cout<<endl;
    */

    vector<int> out1 = countPlatesBwCandelsOofN(s,queries);

    cout<<"Output of counting Plates between Candels\n";
    for(size_t i=0; i< out1.size(); i++ )
    {
        cout<<out1[i]<<"\t";
    }
    cout<<endl;
}