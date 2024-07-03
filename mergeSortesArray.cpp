/*
88. Merge Sorted Array

You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

 

Example 1:

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
Example 2:

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
Example 3:

Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.
 

Constraints:

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 109
 

Follow up: Can you come up with an algorithm that runs in O(m + n) time?

*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

// Time O(m+n)
// Space O(m)
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
    // collect the nums1 elements in another temp vector
    vector<int> temp;
    for(int i=0; i<m; i++)
    {
        temp.push_back(nums1[i]);
    }

    int nums1Count=0;
    int nums2Count=0;
    int tempCount=0;
    while(nums1Count < m && nums2Count < n)
    {
        if(temp[nums1Count] <= nums2[nums2Count])
        {
            nums1[tempCount]=temp[nums1Count];
            nums1Count++;
        }
        else if(temp[nums1Count] > nums2[nums2Count])
        {
            nums1[tempCount]=nums2[nums2Count];
            nums2Count++; 
        }
        tempCount++;
   }
  
   while(nums1Count < m)
   {
        nums1[tempCount]=temp[nums1Count];
        nums1Count++;
        tempCount++;
   }
   while(nums2Count < n)
   {
        nums1[tempCount]=nums2[nums2Count];
        nums2Count++;
        tempCount++;
   }
}

// Time complexity is O(m+n)
// Space complexity is O(1)
void mergeInArray(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
    int nums1Count = m-1;
    int nums2Count = n-1;
    int temp=nums1.size()-1;

    while(nums1Count>=0 && nums2Count>=0)
    {
        if(nums1[nums1Count]>=nums2[nums2Count])
        {
            nums1[temp]=nums1[nums1Count];
            nums1Count--;
        }
        else if(nums1[nums1Count] < nums2[nums2Count])
        {
            nums1[temp]=nums2[nums2Count];
            nums2Count--;
        }
        temp--;
    }

    while(nums1Count>=0)
    {
        nums1[temp]=nums1[nums1Count];
        nums1Count--;
        temp--;
    }
    while(nums2Count>=0)
    {
        nums1[temp]=nums2[nums2Count];
        nums2Count--;
        temp--;
    }
}


int main()
{
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    int nums2Size = nums2.size();
    int nums1Size = nums1.size()-nums2Size;

    merge(nums1,nums1Size, nums2,nums2Size);

    cout<<"\n Printing merged vector \n";
    for(size_t i=0; i<nums1.size(); i++ )
    {
        cout << nums1[i] <<"\t";
    }
    cout <<endl;


    nums1 = {1,2,3,0,0,0};
    nums2 = {2,5,6};
    nums2Size = nums2.size();
    nums1Size = nums1.size()-nums2Size;

    mergeInArray(nums1,nums1Size, nums2,nums2Size);

    cout<<"\n Printing merged vector using sam earray \n";
    for(size_t i=0; i<nums1.size(); i++ )
    {
        cout << nums1[i] <<"\t";
    }
    cout <<endl;

    return 0;
}