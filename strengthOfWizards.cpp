/*
2281. Sum of Total Strength of Wizards

As the ruler of a kingdom, you have an army of wizards at your command.

You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard.
For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength),
the total strength is defined as the product of the following two values:

The strength of the weakest wizard in the group.
The total of all the individual strengths of the wizards in the group.
Return the sum of the total strengths of all contiguous groups of wizards. 
Since the answer may be very large, return it modulo 109 + 7.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: strength = [1,3,1,2]
Output: 44
Explanation: The following are all the contiguous groups of wizards:
- [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
- [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
- [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
- [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
- [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
- [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
- [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
- [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
- [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
- [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
Example 2:

Input: strength = [5,4,6]
Output: 213
Explanation: The following are all the contiguous groups of wizards: 
- [5] from [5,4,6] has a total strength of min([5]) * sum([5]) = 5 * 5 = 25
- [4] from [5,4,6] has a total strength of min([4]) * sum([4]) = 4 * 4 = 16
- [6] from [5,4,6] has a total strength of min([6]) * sum([6]) = 6 * 6 = 36
- [5,4] from [5,4,6] has a total strength of min([5,4]) * sum([5,4]) = 4 * 9 = 36
- [4,6] from [5,4,6] has a total strength of min([4,6]) * sum([4,6]) = 4 * 10 = 40
- [5,4,6] from [5,4,6] has a total strength of min([5,4,6]) * sum([5,4,6]) = 4 * 15 = 60
The sum of all the total strengths is 25 + 16 + 36 + 36 + 40 + 60 = 213.
 

Constraints:

1 <= strength.length <= 105
1 <= strength[i] <= 109

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<math.h>
#include<stack>

using namespace std;

// Time complexity is O(nsquare)
// Spzce complexity is O(1)
int bruteForceWizardFind(vector<int> &strength)
{
    // max number is 1000000007 if asked to restrict overflow of integer
    //int mod=1e9+7;

    // collects all sum of wizards
    int allSum=0;
    // collects sum of continuous wizards
    int tempSum=0;
    // collects minimum wizard strength in the contiguous array
    int minimum=0;
    // collect wizard strength as per rule from contiguous wizard strengths
    int wizardSum=0;

    for(size_t i=0; i<strength.size(); i++)
    {
        
        minimum   = strength[i];
        tempSum   = strength[i];
        wizardSum = tempSum*minimum;
        allSum=allSum+wizardSum;
        
        for(size_t j=i+1; j<strength.size(); j++)
        {
            // start collecting minimum accounting from previous contiguous array
            minimum = min(minimum,strength[j]);
            tempSum=tempSum + strength[j];
            wizardSum = tempSum*minimum;
            allSum = allSum+wizardSum;
        }
    }
    return allSum;

}

/*
events are
array                     sum    min    ans
1                         1   *  1   =  1
1, 3                      4   *  1   =  4
1, 3, 1                   5   *  1   =  5
1, 3, 1, 2                7   *  1   =  7

   3                      3   *  3   =  9
   3, 1                   4   *  1   =  4
   3, 1, 2                6   *  1   =  6

      1                   1   *  1   =  1
      1, 2                3   *  1   =  3

         2                2   *  2   =  4 


optimizing further

1) # numbwer of distinct value of sum  => N power 2
2) # number of distinct value of minimum value => N

going with method 2

for each i in (0 to n)
{
    -How many sub-array are there for which strength[i] is the minimum?
    -What is the sum of all such sub-arrays ==>SUMi
    -ans = ans + SUMi * strength[i]
}


using monotonic stack
eg: 5, 4 ,6,7,8,11,3,4,5,6
for element 4 the previous smaller element is none and next smaller element is 3
round 1) 5 will be in stack
round 2) 5,4 will be in stack
round 3) 6 will be skipped
round 4) 7 will be skipped
round 5) 8 will be skipped
round 6) 11 will be skipped
round 7) 5,4,3 will be in min stack

using prefix sum collect the sum of array which has minimum element combination
between [Prev, next]

in this example
    pref(1)-pref(0)  pref(2)-pref(0)  pref(3)-pref(0)  pref(4)-pref(0)  pref(5)-pref(0)
                     pref(2)-pref(1)  pref(3)-pref(1)  pref(4)-pref(1)  pref(5)-pref(1)
                                                       

Generalizing
    pref(i)-pref(p)  pref(i+1)-pref(p)    pref(i+2)-pref(p)    pref(i+3)-pref(p)    pref(i+4)-pref(p)
                     pref(i+1)-pref(p+1)  pref(i+2)-pref(p+1)  pref(i+3)-pref(p+1)  pref(i+4)-pref(p+1)
                                          

Further generalizing




eg: walkthrough
strength array is          = 1 3 1  2          Index            =  0 1  2 3
prefix_sum array is        = 0 1 4 5  7        prev_small_index = -1 0 -1 2  
prefix_prefix_sum array is = 0 0 1 5 10 17     next_small       =  2 2  4 4   

*/

int totalStrength(vector<int>& strength) 
{
    // to reduce from n2 to n time complexity
    int strengthSize = strength.size();

    //int mod=1e9+7;

    vector<int> prefixSum(strengthSize+1,0);
    for(int i=0; i<strengthSize; i++)
    {
        prefixSum[i+1]=(prefixSum[i]+strength[i]);
    }

    cout<<"\n prefixSum of contiguous array { ";
    for(int i=0; i<(strengthSize+1); i++)
    {
        cout<<prefixSum[i];
        if(i<(strengthSize))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;

    vector<int> prefixPrefixSum(strengthSize+2,0);
    for(int i=0; i<(strengthSize+2); i++)
    {
        prefixPrefixSum[i+1]=(prefixPrefixSum[i]+prefixSum[i]);
    }

    cout<<"\n prefixPrefixSum of contiguous array { ";
    for(int i=0; i<(strengthSize+2); i++)
    {
        cout<<prefixPrefixSum[i];
        if(i<(strengthSize+1))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;

    stack<int> monotonicStack;

    while(!monotonicStack.empty())
    {
        monotonicStack.pop();
    }

    vector<int> prevSmallIndex(strengthSize,-1);
    for(int i=0; i<strengthSize; i++)
    {
        while( !monotonicStack.empty() && (strength[monotonicStack.top()] >= strength[i]) )
        {
            monotonicStack.pop();
        }
        if(monotonicStack.empty())
        {
            prevSmallIndex[i]=-1;
        }
        else
        {
            prevSmallIndex[i]=monotonicStack.top();
        }
        monotonicStack.push(i);
    }

    cout<<"\n Previous small index of contiguous array { ";
    for(int i=0; i<strengthSize; i++)
    {
        cout<<prevSmallIndex[i];
        if(i<(strengthSize-1))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;

    while(!monotonicStack.empty())
    {
        monotonicStack.pop();
    }

    vector<int> nextSmallIndex(strengthSize,strengthSize);
    for(int i=strengthSize-1; i>=0; i--)
    {
        while(!monotonicStack.empty() && (strength[monotonicStack.top()] > strength[i]))
        {
            monotonicStack.pop();

        }
        if(monotonicStack.empty())
        {
            nextSmallIndex[i]=strengthSize;
        }
        else
        {
            nextSmallIndex[i]=monotonicStack.top();
        }
        monotonicStack.push(i);
    }

    cout<<"\n Next small index of contiguous array { ";
    for(int i=0; i<strengthSize; i++)
    {
        cout<<nextSmallIndex[i];
        if(i<(strengthSize-1))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;

    int answer=0;
    for(int i=0; i<strengthSize; i++)
    {
        cout<<"\n For index i="<<i<<endl;
        cout<<" nextSmallIndex[i]=" <<nextSmallIndex[i]<<" and prefixPrefixSum[nextSmallIndex[i]+1]="<<prefixPrefixSum[nextSmallIndex[i]+1]<<endl;
        cout<<" prefixPrefixSum[i+1]="<<prefixPrefixSum[i+1]<<endl;
        cout<<" prevSmallIndex[i]=" <<prevSmallIndex[i]<<" and prefixPrefixSum[prevSmallIndex[i]+1]="<<prefixPrefixSum[prevSmallIndex[i]+1]<<endl;

        int plus = (prefixPrefixSum[nextSmallIndex[i]+1] - prefixPrefixSum[i+1]);
        cout<<" \n plus = (prefixPrefixSum[nextSmallIndex[i]+1] - prefixPrefixSum[i+1]) is "<<plus<<endl;
        int after =(i -prevSmallIndex[i]);
        cout<<" after =(i -prevSmallIndex[i]) "<<after<<endl;
        cout<<" plus*after is "<<plus*after<<endl;

        int minus = (prefixPrefixSum[i+1] - prefixPrefixSum[prevSmallIndex[i]+1]);
        cout<<"\n minus = (prefixPrefixSum[i+1] - prefixPrefixSum[prevSmallIndex[i]+1]) is "<<minus<<endl;
        int before = (nextSmallIndex[i] - i);
        cout<<" before =(nextSmallIndex[i] - i) "<<before<<endl;
        cout<<" minus*before is "<<minus*before<<endl;
        int temp = (plus*after - minus*before) * strength[i];

        cout<<"\n (plus*after - minus*before) is "<< (plus*after - minus*before)<<endl;
        cout<<"\n temp = (plus*after - minus*before) * strength[i] ("<< strength[i]<<") is "<<temp<<endl;

        answer=answer+temp;
    }
    return answer;
}

int main()
{
    vector<int> strength = {1,3,1,2};
    int sum = bruteForceWizardFind(strength);

    cout <<"\n Using Brute force method sum is "<<sum<<endl;

    cout <<"\n Using prefix sum method and monotonic stack DSA"<<endl;
    sum = totalStrength(strength);
    cout <<"\n Sum is "<<sum<<endl;

    return 0;
}