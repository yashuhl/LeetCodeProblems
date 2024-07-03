/*
42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

// Time Complexity is O(height size)
// Space Complexity is O(leftPrefix + rightPrefix) ==> O(height size)
int trapUsingPrefixSum(vector<int>& height) 
{
    int heightSize = height.size();

    // left side prefix array
    vector<int> leftPrefix(heightSize);
    leftPrefix[0]=height[0];
    cout << "\nLeft Prefix is " <<endl;
    cout << leftPrefix[0] <<"\t";
    for(int i=1; i<heightSize; i++)
    {
        leftPrefix[i]=max(leftPrefix[i-1],height[i]);
        cout << leftPrefix[i] <<"\t";
    }

    // right side prefix array
    vector<int> rightPrefix(heightSize);
    rightPrefix[heightSize-1]=height[heightSize-1];
    cout << "\nright Prefix is " <<endl;
    for(int j=heightSize-2; j>=0; j--)
    {
        rightPrefix[j]=max(rightPrefix[j+1],height[j]);
        
    }
    // printing from 0 index
    for(int k=0; k<heightSize; k++)
    {
        cout << rightPrefix[k] <<"\t";
    }
    cout << endl;

    int count=0;

    for(int c=0; c<heightSize; c++)
    {
        int temp =  min(leftPrefix[c],rightPrefix[c]) - height[c];
        count=count+temp;
    }

    return count;
        
}

// Time Complexity O(height size) and space complexity O(1) using 2 pointers
int trap(vector<int>& height) 
{

    int i=0, left_max=height[0];
    int sum=0;
    int j=height.size()-1, right_max=height[j];

    while(i<j)
    {
        if(left_max < right_max)
        {
            sum = sum + (left_max - height[i]);
            i++;
            left_max = max(left_max,height[i]);
        }
        else
        {
            sum  = sum + (right_max - height[j]);
            j--;
            right_max = max(right_max,height[j]);
        }
    }

    return sum;
        
}

int main()
{
    //case 1
    //vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};

    // case 2
    vector<int> height ={4,2,0,3,2,5};

    cout<<"Given heights are"<<endl;
    for(size_t i=0; i<height.size(); i++)
    {
        cout << height[i]<<"\t";

    }

    int output = trapUsingPrefixSum(height);

    cout<<"\n Trapped water using prefix array is " << output << endl;


    output = trap(height);

    cout<<"\n Trapped water using two pointer is " << output << endl;
    return 0;
}