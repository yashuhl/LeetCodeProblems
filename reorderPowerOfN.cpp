/*
869. Reordered Power of 2

You are given an integer n. We reorder the digits in any order 
(including the original order) such that the leading digit is not zero.

Return true if and only if we can do this so that the resulting number is a power of two.

 

Example 1:

Input: n = 1
Output: true
Example 2:

Input: n = 10
Output: false
 

Constraints:

1 <= n <= 109

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

// Space Complexity O(31)
// Time Complexity O(nlogn) sorting the string format of 2 max power
class Solution 
{
    public:
        bool reorderedPowerOf2(int n) 
        {
            long long x=1;
            int max=1e9;
            vector<string> possiblePowerN;

            while(x<max)
            {
                possiblePowerN.push_back(to_string(x));
                // to capture for 2 power 0;
                x=2*x;
            }

            for(size_t i=0; i<possiblePowerN.size(); i++)
            {
                sort(possiblePowerN[i].begin(), possiblePowerN[i].end());
            }

            string stringN=to_string(n);
            sort(stringN.begin(),stringN.end());

            cout<<"\n Required string Power of n is "<<stringN<<endl;
            cout<<"\n Possible strings are "<<endl;
            for(auto si:possiblePowerN)
            {
                cout<<si<<endl;
                if(si==stringN)
                {
                    return true;
                }
            }
            return false;
        }
};

int main()
{
    int power=1024;
    Solution Solve;
    bool boolean=Solve.reorderedPowerOf2(power);
    cout<<"\n Reordered Power of 2 i.e " << power<< " is ";
    if(boolean)
    {
        cout<<" possible\n";
    }
    else
    {
        cout<<" not possible\n";
    }
    return 0;
}