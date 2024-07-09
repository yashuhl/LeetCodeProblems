/*
582. Kill Process

You have n processes forming a rooted tree structure. You are given two integer arrays pid and ppid, 
where pid[i] is the ID of the ith process and ppid[i] is the ID of the ith process's parent process.

Each process has only one parent process but may have multiple children processes. 
Only one process has ppid[i] = 0, which means this process has no parent process (the root of the tree).

When a process is killed, all of its children processes will also be killed.

Given an integer kill representing the ID of a process you want to kill, 
return a list of the IDs of the processes that will be killed. You may return the answer in any order.

Example 1:

0-->3
   / \
  /   \
 1     5
      /
     /
    10

Input: pid = [1,3,10,5], ppid = [3,0,5,3], kill = 5
Output: [5,10]

*/

#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<map>
#include<unordered_map>

using namespace std;

void dfs_helper(unordered_map<int,vector<int>> &mapParentChild, int index, vector<int> &result)
{
    result.push_back(index);
    for(auto v:mapParentChild[index])
    {
        dfs_helper(mapParentChild,v,result);
        
    }
}

vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) 
{
    // map parent to child process and will be in ascending order
    unordered_map<int, vector<int>> mapParentChild;

    for(size_t i=0; i<ppid.size(); i++)
    {
        mapParentChild[ppid[i]].push_back(pid[i]);
    }

    cout<<"\n Map Parent to Children"<<endl;
    for(auto pc:mapParentChild)
    {
        cout<<" Parent is "<<pc.first<<" children are { ";
        for(size_t j=0; j<pc.second.size(); j++)
        {
            cout<<pc.second[j];
            if( j<(pc.second.size()-1) )
            {
                cout<<" , ";
            }
        }
        cout<<" } "<<endl;
    }

    // Collect result of children to be killed with parent
    vector<int> result;

    // Apply BFS from the considered kill variable unordered map
    /*
    queue<int> q;
    q.push(kill);

    while(!q.empty())
    {
        int temp=q.front();
        q.pop();
        result.push_back(temp);
        
        //for( int v:mapParentChild[temp])
        //{
        //    q.push(v);
        //}
        
       for(size_t i=0; i<mapParentChild[temp].size(); i++)
       {
            q.push(mapParentChild[temp][i]);
       }
    }
    */

   //Apply DFS from the considered kill variable unordered map
   dfs_helper(mapParentChild,kill,result);
   return result;
}

int main()
{
    vector<int> pid={ 1,3,10,5};
    vector<int> ppid={3,0,5,3};

    //case 1
    int kill=5;

    vector<int> result=killProcess(pid,ppid,kill);

    cout<<"\n When a parent "<<kill<<" process is killed all of its children { ";
    for(size_t i=1; i<result.size(); i++)
    {
        cout<<result[i];
        if( i< result.size()-1 )
        {
            cout<<" , ";
        }
    }
    cout<<" } processes will be killed"<<endl;
    return 0;
}