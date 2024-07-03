/*
210. Course Schedule II

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;

/* In this problem

Asymptotic complexity in terms of number of courses `n` and number of prerequisites `e`:
* Time: O(n + e).
* Auxiliary space: O(n + e).
* Total space: O(n + e).

The graph concept used is called topological sort

House keeping rules while identifying the order

1) there should be no cycle in the graph when pre-requisites are there
2) It will be a DAG- Directed Acyclic Graph
3) Should not have back edges
4) Can  have tree/ forward / cross edges whose departure time decreses

Solution 1: Build topological sort of course and reverse it

Solution 2: Kahns algorithm - time complexity is O(n)
1) Calculate and maintain an in-degree array for each vertex
2) Keep 0 indegree vertex in queue or stack
3) If graph is DAG, there should be an index with 0 indegree vertex
4) Make it a vertex in topological sort
5) Delete all its outgoing edges which means decrement the indegree array count
6) If any new indegree count with 0 is found, add that to queue or stack
7) Repeat till all vertex in the graphs are sorted

*/

vector<int>  findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<vector<int>> adjList(numCourses);
    vector<int> inDegree(numCourses);
    vector<int> topSort;

    for(size_t i=0; i<prerequisites.size(); i++)
    {
        // in prerequisities {[i][0],[i][1]} course[i][1] will form adjacency list 
        // containing course[i][0] as directed graph
        adjList[prerequisites[i][1]].push_back(prerequisites[i][0]);
        // Formulate in degree count for couse[i][0] which will be taken once its prerequisite is taken
        inDegree[prerequisites[i][0]]++;
    }

    // can use queue or stack
    queue<int> q;

    // collect vertex with 0 indegree
    for(int i=0; i<numCourses; i++)
    {
        if(inDegree[i]==0)
        {
            q.push(i);
        }
    }

    // return NULL array as the graph is cyclic without having starting node with zero indegree
    if(q.empty())
    {
        return {};
    }

    while(!q.empty())
    {
        int node=q.front();
        topSort.push_back(node);
        q.pop();

        for(size_t i=0; i<adjList[node].size(); i++)
        {
            // element in the adjacency list of indegree 0 node
            int neighbour = adjList[node][i];
            // degrement its indegree
            inDegree[neighbour]--;
            // if neighbours indegree becomes zero add it to queue
            if(inDegree[neighbour] == 0)
            {
                q.push(neighbour);

            }
        }
    }

    int topSortSize = topSort.size();
    if( topSortSize != numCourses)
    {
        return {};
    }
    return topSort;

}


int main()
{
    int numCourses=4;
    vector<vector<int>> prerequisites = { {1,0} , {2,0} , {3,1} , {3,2} };

    vector<int> result = findOrder(numCourses, prerequisites);

    cout<<"\n Cousere order taken is \n";
    for(size_t i=0; i<result.size(); i++)
    {
        cout<<result[i]<<"\t";
    }

    return 0;
}