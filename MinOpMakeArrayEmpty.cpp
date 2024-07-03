/*
2870. Minimum Number of Operations to Make Array Empty
You are given a 0-indexed array nums consisting of positive integers.

There are two types of operations that you can apply on the array any number of times:

Choose two elements with equal values and delete them from the array.
Choose three elements with equal values and delete them from the array.
Return the minimum number of operations required to make the array empty, or -1 if it is not possible.

 

Example 1:

Input: nums = [2,3,3,2,2,4,2,3,4]
Output: 4
Explanation: We can apply the following operations to make the array empty:
- Apply the first operation on the elements at indices 0 and 3. The resulting array is nums = [3,3,2,4,2,3,4].
- Apply the first operation on the elements at indices 2 and 4. The resulting array is nums = [3,3,4,3,4].
- Apply the second operation on the elements at indices 0, 1, and 3. The resulting array is nums = [4,4].
- Apply the first operation on the elements at indices 0 and 1. The resulting array is nums = [].
It can be shown that we cannot make the array empty in less than 4 operations.
Example 2:

Input: nums = [2,1,2,2,3,3]
Output: -1
Explanation: It is impossible to empty the array.

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>

using namespace std;

int minOperations(vector<int>& nums)
{
    //Create un ordered HashMap of integers and its repetetions.
    unordered_map<int,int> uOMap;
    for(size_t i=0; i<nums.size(); i++)
    {
        uOMap[nums[i]]++;
    }
    // problem solution
    // if array element count divisible by 3 or 2 then count the quotients.
    // else return count -1
    int count=0;
    cout<<"Print unordered map"<<endl;
    for(auto it=uOMap.begin(); it!=uOMap.end(); it++)
    {
        int tempCount=0;
        cout << it->first <<"\t" <<it->second<<endl;
        if(it->second < 2)
        {
            count=-1;
            return count;
        }
        // 2-> 2/2 = 1 count ==>   (2+2)/3 = 1
        // 3->3/3 =1 count   ==>   (3+2)/3 = 1
        // 4-> 4/2 = 2 count ==>   (4+2)/3 = 2
        // 5-> 3+2 = 2 count ==>   (5+2)/3 = 2
        // 6-> 3+3 = 2 count ==>   (6+2)/3 = 2
        // 7-> 2+2+3 = 3 count ==> (7+2)/3 = 3
        // 8-> 3+3+2 = 3 count ==> (8+2)/3 = 3
        //general formula (number+2)/3 rounded integer
        tempCount=(it->second + 2)/3;
        count=count+tempCount;
    }
    return count;    
}

//Driver program
int main()
{
    vector<int> nums={2,3,3,2,2,4,2,3,4};
    //vector<int> nums={2,1,2,2,3,3};
    int count = minOperations(nums);

    cout<<"\nMinimum Number of Operations to Make Array Empty is " <<count<<endl;

    return 0;
}
