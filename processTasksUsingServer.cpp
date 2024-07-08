/*
1882. Process Tasks Using Servers

You are given two 0-indexed integer arrays servers and tasks of lengths n​​​​​​ and m​​​​​​ respectively. 
servers[i] is the weight of the i​​​​​​th​​​​ server, and tasks[j] is the time needed to process the j​​​​​​th​​​​ task in seconds.

Tasks are assigned to the servers using a task queue. Initially, all servers are free, and the queue is empty.

At second j, the jth task is inserted into the queue (starting with the 0th task being inserted at second 0). 
As long as there are free servers and the queue is not empty, the task in the front of the queue will be assigned 
to a free server with the smallest weight, and in case of a tie, it is assigned to a free server with the smallest 
index.

If there are no free servers and the queue is not empty, we wait until a server becomes free and 
immediately assign the next task. If multiple servers become free at the same time, 
then multiple tasks from the queue will be assigned in order of insertion following 
the weight and index priorities above.

A server that is assigned task j at second t will be free again at second t + tasks[j].

Build an array ans​​​​ of length m, where ans[j] is the index of the server the j​​​​​​th task
will be assigned to.

Return the array ans​​​​.

 

Example 1:

Input: servers = [3,3,2], tasks = [1,2,3,2,1,2]
Output: [2,2,0,2,1,2]
Explanation: Events in chronological order go as follows:
- At second 0, task 0 is added and processed using server 2 until second 1.
- At second 1, server 2 becomes free. Task 1 is added and processed using server 2 until second 3.
- At second 2, task 2 is added and processed using server 0 until second 5.
- At second 3, server 2 becomes free. Task 3 is added and processed using server 2 until second 5.
- At second 4, task 4 is added and processed using server 1 until second 5.
- At second 5, all servers become free. Task 5 is added and processed using server 2 until second 7.
Example 2:

Input: servers = [5,1,4,3,2], tasks = [2,1,2,4,5,2,1]
Output: [1,4,1,4,1,3,2]
Explanation: Events in chronological order go as follows: 
- At second 0, task 0 is added and processed using server 1 until second 2.
- At second 1, task 1 is added and processed using server 4 until second 2.
- At second 2, servers 1 and 4 become free. Task 2 is added and processed using server 1 until second 4. 
- At second 3, task 3 is added and processed using server 4 until second 7.
- At second 4, server 1 becomes free. Task 4 is added and processed using server 1 until second 9. 
- At second 5, task 5 is added and processed using server 3 until second 7.
- At second 6, task 6 is added and processed using server 2 until second 7.
 

Constraints:

servers.length == n
tasks.length == m
1 <= n, m <= 2 * 105
1 <= servers[i], tasks[j] <= 2 * 105

*/

/*
Solution:

Intuition and Approach
Priority Queues:

Free Servers Queue (fs): 
This min-heap keeps track of free servers, prioritized by their weight and index. 
The server with the smallest weight (and smallest index in case of ties) will be at the top, 
making it easy to retrieve the most suitable server for the next task.

Busy Servers Queue (bs): 
This min-heap manages servers currently processing tasks, prioritized by the time 
they will become free. When a server finishes a task, it moves back to the free servers queue.


Task Processing:
1) At each second, a new task is added to the task queue.
2) If there are any tasks waiting in the queue and free servers available, 
we assign tasks to the free servers based on their priority (smallest weight, smallest index).
3) If no servers are free when a task arrives, we wait until one or more servers become free. 
The moment a server is free, we immediately assign it the next task in the queue, 
again based on the priority rules.

Detailed Steps:

Initialization:
Populate the free servers priority queue (fs) with all servers, using their weight and index as the key.

Task Assignment:
For each task at second j:
   1) Move Finished Tasks: Check the busy servers queue (bs) and move any servers that have finished 
      their tasks back to the free servers queue (fs). This is done by comparing the current time j 
      with the free time recorded in bs.
   2) Assign Tasks: If there are free servers available (fs is not empty), 
      pop the top server (smallest weight and index) and assign it the current task. 
      Record the server's index in the result array. 
      Calculate the new free time for this server (current time j + task duration) and 
      push it to the busy servers queue (bs).
    3) Wait for Free Server: If no servers are free (fs is empty), 
      take the server that will be free the soonest from bs, assign it the current task, 
      and update its next free time.

Time Complexity Analysis
Heap Operations:
Each insertion or removal operation from a priority queue takes O(logn),
where n is the number of servers.

Total Complexity:
Initialization: Building the initial free servers heap takes O(nlogn).
Processing Each Task:
Checking and moving servers between queues involves heap operations which are O(logn).
Assigning a task to a server also involves heap operations O(logn).
With m tasks, n servers the overall complexity is O((n+m)logn)
*/

#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<iterator>

using namespace std;

vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) 
{

    // collect asked result
    vector<int> result;

    // convert server vector to priority queue with free server and index with min heap
    /*
       A C++ priority queue is a type of "container adapter", specifically designed such that the 
       first element of the queue is either the greatest or the smallest of all elements in the queue, 
       and elements are in non-increasing or non-decreasing order (hence we can see that each element 
       of the queue has a priority {fixed order}).

       In C++ STL, the top element is always the greatest by default.
       We can also change it to the smallest element at the top. 
       Priority queues are built on the top of the max heap and use an array or vector as an internal structure. 
       In simple terms, STL Priority Queue is the implementation of Heap Data Structure.

       general syntax : 
       std::priority_queue<int> pq;

       As we saw earlier, a priority queue is implemented as max heap by default in C++ but,
       it also provides us an option to change it to min heap by passing another parameter while creating 
       a priority queue.

       Syntax: priority_queue <int, vector<int>, greater<int>> gq;

       where,

      ‘int’ is the type of elements you want to store in the priority queue. 
       In this case, it’s an integer. You can replace int with any other data type you need.
      ‘vector<int>’ is the type of internal container used to store these elements. 
       std::priority_queue is not a container in itself but a container adopter. It wraps other containers. 
       In this example, we’re using a vector, but you could choose a different container that supports front(),
       push_back(), and pop_back() methods. 
      ‘greater<int>‘ is a custom comparison function. This determines how the elements 
       are ordered within the priority queue. In this specific example, greater<int> sets up a min-heap. 
       It means that the smallest element will be at the top of the queue.
       
       In the case of max heap, we didn’t have to specify them as the 
       default values for these are already suitable for max heap.
    */


   // priority queue with pair 1st one for server weight and second one for server index
   priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > freeServer;

   // this arranges the min heap with min server and its min index order
   // eg: order is server 2 with 2 index, server 3 with 0 index, server 3 with 1 index  
   for(size_t i=0; i<servers.size(); i++)
   {
        freeServer.push({servers[i],i});
   }
   // log for printing freeServer weight with index
   /*
    while(!freeServer.empty())
    {
            pair<int,int> temp=freeServer.top();
            cout<<" \n server is "<<temp.first<<" index is "<<temp.second;
            freeServer.pop();
    }
    */

   // busy server priority queue with pair<int<pair<int,int> where 1st pair is for calculated task time to finish
   // pair inside pair 1st is for taken freeserver server weight, pair inside pair 2nd is for taken freeServer index
   priority_queue< pair<int, pair<int, int>>, vector< pair<int, pair<int, int>>>, greater< pair<int, pair<int,int>>> > busyServer;
    

   for(size_t i=0; i<tasks.size(); i++)
   {
        // busy servers will be freed when its calculated free up time arrives
        while(!busyServer.empty())
        {
            pair<int, pair<int,int>> temp=busyServer.top();
            if(temp.first <= (int)i)
            {
                freeServer.push(temp.second);
                busyServer.pop();

            }
            else
            {
                break;
            }
            
        }

        // when server is free, assign it to busy
        if(!freeServer.empty())
        {

            pair<int,int> temp=freeServer.top();
            freeServer.pop();
            //collect the index of server assigned in result array
            result.push_back(temp.second);
            // calculating busy server time is
            int busyServerTime = i+tasks[i];
            busyServer.push({busyServerTime,{temp.first,temp.second}});
            
        }
        // when server is fully utilized wait for next server to become free from busy
        else
        {
            pair<int, pair<int,int>> temp=busyServer.top();
            busyServer.pop();

            // as tasks keep on coming , we need to assign the servers for future processing
            // take the server that will be free the soonest from bs using priority queue min heap property
            // add the current task time to it , and update its next free time.
            // This way we will not loose the time track of task when server is busy
            // also capture the index of the server assigned for next task
            result.push_back(temp.second.second);

            int busyServerNewTime=temp.first+tasks[i];
            busyServer.push({busyServerNewTime, temp.second});

        }
   }
   

   return result;
        
}

int main()
{
    vector<int> servers ={3,3,2};
    vector<int> tasks = {1,2,3,2,1,2};

    vector<int> output = assignTasks(servers, tasks);

    cout<<"\n The index of the server's j​​​​​​ task will be assigned to is { ";
    for(size_t i=0; i<output.size(); i++)
    {
        cout<<output[i];
        if(i < (output.size()-1))
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;

    return 0;
}

