/*

56. Merge Intervals

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, 
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 

Constraints:

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
    sort(intervals.begin(),intervals.end());
    vector<vector<int>> result;

    vector<int> temp(2);

    // Put initial start and end interval
    int start=intervals[0][0];
    int end=intervals[0][1];

    for(size_t i=0; i<intervals.size()-1; i++)
    {
        vector<int> temp(2);
        // if present intervals end greater than start\end of next intervals
        if( end >= intervals[i+1][0])
        {
            end=max(end,intervals[i+1][1]);
        }
        else
        {   
            temp[0]=start;
            temp[1]=end;
            result.push_back(temp);

            start=intervals[i+1][0];
            end=intervals[i+1][1];  
        }

    }
    //pushing last interval
    result.push_back({start,end});
    return result;
        
}

int main()
{

    vector<vector<int>> intervals = {{1,3},{3,5},{2,7},{8,10},{15,18}};

    cout<<"\nGiven Intervals are {";
    for(size_t i=0; i<intervals.size(); i++)
    {
        cout<<" {";
        for(size_t j=0; j<intervals[i].size(); j++)
        {
            cout<<intervals[i][j] << ",";
        }
        cout<<" }";
    }
    cout<<" }"<<endl;

    vector<vector<int>> result = merge(intervals);
    cout<<"\nMerged Intervals are {";
    for(size_t i=0; i<result.size(); i++)
    {
        cout<<" {";
        for(size_t j=0; j<result[i].size(); j++)
        {
            cout<<result[i][j]<<",";
        }
        cout<<" }";
    }
    cout<<" }"<<endl;

    return 0;

}