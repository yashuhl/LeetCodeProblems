/*
253. Meeting Rooms II

Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], 
return the minimum number of conference rooms required.

 

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 104
0 <= starti < endi <= 106
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

// method 1
// time complexity O(n)
// space complexity O(n)
int minMeetingRooms(vector<vector<int>>& intervals)
{
    int sizeOfIntervals=intervals.size();
    
    // collected start intervals and sorted 
    // time complexity O(n)
    // space complexity O(n)
    vector<int> start(sizeOfIntervals);
    for(int i=0; i<sizeOfIntervals; i++)
    {
        start[i]=intervals[i][0];
    }
    sort(start.begin(),start.end());

    // collected end intervals and sorted
    vector<int> end(sizeOfIntervals);
    for(int i=0; i<sizeOfIntervals; i++)
    {
        end[i]=intervals[i][1];
    }
    sort(end.begin(),end.end());

    int countMeetingRooms=0;
    int tempCount=0;

    // two pointer method, one for start and another for end vector
    int startPointer=0;
    int endPointer=0;

    // as start pointer reaches the end of interval size before end pointer
    // time complexity O(n)
    while(startPointer<sizeOfIntervals)
    {
        if(start[startPointer] < end[endPointer])
        {
            startPointer++;
            // increment meeting room count if meeting started
            tempCount++;
        }
        else
        {
            endPointer++;
            // decrement meeting room count if meeting ended
            tempCount--;
        }
        // at that momemt capture the max meeting room required
        countMeetingRooms=max(countMeetingRooms,tempCount);
    }  

    return countMeetingRooms;
}

int main()
{
    vector<vector<int>> intervals = {{0,30},{5,10},{15,20}};

    int sizeOfInterval=intervals.size();
    cout<<"\n Given intervals are { ";
    for(int i=0; i<sizeOfInterval; i++)
    {
        cout<<"{";
        for(size_t j=0; j<intervals[i].size(); j++)
        {
            cout<<intervals[i][j];
            if(j==0)
            {
                cout<<",";
            }

        }
        cout<<"} ";
        
        if( i<(sizeOfInterval-1) )
        {
            cout<<", ";

        }
    }
    cout<<" }"<<endl;

    int numberOfRooms = minMeetingRooms(intervals);

    cout<<"\nNumber of meeting rooms needed is "<<numberOfRooms<<endl;

}
