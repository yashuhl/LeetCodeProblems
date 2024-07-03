/*
1496. Path Crossing

Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.

 

Example 1:


Input: path = "NES"
Output: false 
Explanation: Notice that the path doesn't cross any point more than once.
Example 2:


Input: path = "NESWW"
Output: true
Explanation: Notice that the path visits the origin twice.
 

Constraints:

1 <= path.length <= 104
path[i] is either 'N', 'S', 'E', or 'W'

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<set>
#include<vector>

using namespace std;

// Time complexity is O(n)
bool isPathCrossing(string path) 
{
    int pathSize=path.size();
    // initialize staring path(x,y) as (0,0)
    int x=0;
    int y=0;

    // initialize hash set for vector of int containing x and y co-ordinates
    set<vector<int>> setXY;
    // fill set with initial coordinated x=0,y=0;
    setXY.insert({x,y});

    for(int i=0; i<pathSize; i++)
    {
        // switch statement for parsing through path
        switch(path[i])
        {
            // if N-> north comes increment y
            case 'N':
                y++;
                break;
            // if S-> south comes increment y
            case 'S':
                y--;
                break;

            // if E-> east comes increment x
            case 'E':
                x++;
                break;
            
            // if W-> west comes decrement x
            case 'W':
                x--;
                break;
        }

        if(setXY.find({x,y}) != setXY.end())
        {
            return true;
        }

        setXY.insert({x,y});
    }
    return false;
}

int main()
{
    // string path="NES";
    string path="NESWW";
    bool pathCrossing = isPathCrossing(path);
    cout << "Is Path Crossing " << pathCrossing << endl;
    return 0;
}