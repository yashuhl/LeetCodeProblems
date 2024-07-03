/*
1. Two SUm

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

// Time complexity O(n2)
vector<int> twoSumBruteForce(vector<int>& nums, int target) 
{
    vector<int> ans;
    for(size_t i=0; i<nums.size()-1; i++)
    {
        for(size_t j=i+1; j<nums.size(); j++)
        {
            if(nums[i]+nums[j] == target)
            {
                ans.push_back(i);
                ans.push_back(j);

            }
        }
    }
    
    return ans;
}

// Time complexity O(n)
vector<int> twoSumHash(vector<int>& nums, int target)
{
    // contains first element the nums value, second element its index
    unordered_map<int,int> mapRequired;
    vector<int> ans;

    int numsSize=nums.size();

    for(int i=0; i<numsSize; i++)
    {
        int required = target-nums[i];
        // find the required number in map by first index or key 
        if(mapRequired.find(required) != mapRequired.end())
        {
            // Get map second element which has index
            ans.push_back(mapRequired[required]);
            ans.push_back(i);

            return ans;
        }
        // push the number to map with index for next pass
        mapRequired[nums[i]]=i;
    }
    return{-1, -1};

}

int main()
{
    vector<int> nums={2, 11, 7, 15};
    int target=9;

    cout<< "\n Given numbers \n";
    for(size_t i=0; i<nums.size(); i++)
    {
        cout<< nums[i]<< "\t";
    }

    vector<int> indexes;
    //indexes=twoSumBruteForce(nums,target);
    indexes=twoSumHash(nums,target);
    cout << "\n Indexes forming target using brute force method are "<<endl;
    for(size_t i=0; i<indexes.size(); i++)
    {
        cout<<indexes[i]<<"\t";
    }
}