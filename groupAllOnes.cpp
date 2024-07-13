/*
2134. Minimum Swaps to Group All 1's Together II

A swap is defined as taking two distinct positions in an array and swapping the values in them.

A circular array is defined as an array where we consider the first element and the last element 
to be adjacent.

Given a binary circular array nums, return the minimum number of swaps required to group all 1's 
present in the array together at any location.

 

Example 1:

Input: nums = [0,1,0,1,1,0,0]
Output: 1
Explanation: Here are a few of the ways to group all the 1's together:
[0,0,1,1,1,0,0] using 1 swap.
[0,1,1,1,0,0,0] using 1 swap.
[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
There is no way to group all 1's together with 0 swaps.
Thus, the minimum number of swaps required is 1.


Example 2:

Input: nums = [0,1,1,1,0,0,1,1,0]
Output: 2
Explanation: Here are a few of the ways to group all the 1's together:
[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
[1,1,1,1,1,0,0,0,0] using 2 swaps.
There is no way to group all 1's together with 0 or 1 swaps.
Thus, the minimum number of swaps required is 2.


Example 3:

Input: nums = [1,1,0,0,1]
Output: 0
Explanation: All the 1's are already grouped together due to the circular property of the array.
Thus, the minimum number of swaps required is 0.
 

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.

*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

class Solution 
{
public:
    /*

    eg:                      { 0 , 1 , 0 , 1 , 1 , 0 , 0 }
    count number of ones = 3
    construct circular array { 0 , 1 , 0 , 1 , 1 , 0 , 0 ,
                               0 , 1 , 0 , 1 , 1 , 0 , 0 }

    1) slide for 1st 3 circullar array i.e indexed 0,1,2 and collect number of zeros i.e 2

    2) slide for rest of the circullar array 1.e indexed 3,4,5,6,7,8,9,10,11,12,13

       now for index 3 --> circullar array element at 3 is 1                --> number of zeros is still 2
                       --> circullar array element[3 - 3(numberOfOnes)]  
                           i.e array element[0] is 0                        --> number of zeros is 1
                           ans is min of ans(2) or swap count at index 3(1) --> answer is 1

        now for index 4 --> circullar array element at 4 is 1                -->number of zeros is 1
                        --> circullar array element[4 - 3(numberOfOnes)]  
                            i.e array element[1] is 1                        -->number of zeros is 1
                            ans is min of ans(2) or swap count at index 4(1) --> answer is 1

        now for index 5 --> circullar array element at 5 is 0             -->number of zeros is 2
                        --> circullar array element[5 - 3(numberOfOnes)]  -->number of zeros is 1
                            i.e array element[2] is 0
                            ans is min of ans(2) or swap count at index 5(1) --> answer is 1

        now for index 6 --> circullar array element at 6 is 0             -->number of zeros is 2
                        --> circullar array element[6 - 3(numberOfOnes)]  -->number of zeros is 2
                            i.e array element[3] is 1

        now for index 7 --> circullar array element at 7 is 0             -->number of zeros is 3
                        --> circullar array element[7 - 3(numberOfOnes)]  -->number of zeros is 3
                            i.e array element[4] is 1

        now for index 8 --> circullar array element at 8 is 1             -->number of zeros is 3
                        --> circullar array element[8 - 3(numberOfOnes)]  -->number of zeros is 2
                            i.e array element[5] is 0

        now for index 9 --> circullar array element at 9 is 0             -->number of zeros is 2
                        --> circullar array element[9 - 3(numberOfOnes)]  -->number of zeros is 1
                            i.e array element[6] is 0

        now for index 10 --> circullar array element at 10 is 1            -->number of zeros is 1
                         --> circullar array element[10 - 3(numberOfOnes)] -->number of zeros is 0
                             i.e array element[7] is 0

        now for index 11 --> circullar array element at 11 is 1            -->number of zeros is 0
                         --> circullar array element[11 - 3(numberOfOnes)] -->number of zeros is 0
                             i.e array element[8] is 1

        now for index 12 --> circullar array element at 12 is 0            -->number of zeros is 1
                         --> circullar array element[11 - 3(numberOfOnes)] -->number of zeros is 1
                             i.e array element[8] is 1

        now for index 13 --> circullar array element at 13 is 0            -->number of zeros is 2
                         --> circullar array element[11 - 3(numberOfOnes)] -->number of zeros is 1
                             i.e array element[9] is 0
    
    */
    // Space Complexity=O(n)
    // Time complexity = O(n)
    int minSwapsLeetCodeSolution(vector<int>& nums) 
    {
        vector<int> numsCircular;
        int sizeOfNums=nums.size();
        // Form the circular vector by attaching the vector again to vector
        for(int i=0; i<2*sizeOfNums; i++)
        {
            numsCircular.push_back(nums[i%sizeOfNums]);
        }

        // Print constructed circular array
        cout<<"\n Printing constructed circular array { ";
        for(int i=0; i<2*sizeOfNums; i++)
        {
            cout<<numsCircular[i];
            if( i < (2*sizeOfNums - 1) )
            {
                cout<<" , ";
            } 
        }
        cout<<"}"<<endl;

        // Count the 1's in the array
        int countOnes=0;
        for(int i=0; i<sizeOfNums; i++)
        {
            if(nums[i]==1)
            {
                countOnes++;
            }
        }
        cout<<"\n Number of 1's in nums are "<<countOnes;

        //corner case optimization
        // if count of ones is 0 or equal to size of array, then no swaps required
        if( (countOnes == 0) || (countOnes == sizeOfNums) )
        {
            return 0;
        }

        int swapCounts=0;

        // collect 0's in first count of ones sliding window as number of swaps
        for(int i=0; i<countOnes; i++)
        {
            if(numsCircular[i]==0)
            {
                swapCounts++;
            }
        }
        int ans=swapCounts;
        cout<<"\n Minimum swaps required in considered sliding window of "<<countOnes<<" is "<<ans;

        // Slide from number of ones to twice array count
        for(size_t window=countOnes; window<numsCircular.size(); window++)
        {
            // collect number of zeros in the sliding window array of [countOnes to twice array size]
            if(numsCircular[window] == 0)
            {
                swapCounts++;
            }
            // deduct number of zeros in the sliding window array of [zero to ( twice array size - nimber of ones) ]
            // as circular array has twice the size of array this logic is required
            if(numsCircular[window-countOnes]==0)
            {
                swapCounts--;
            }
            ans=min(ans,swapCounts);
        }



        return ans;
    }


    // using two pointer method
    // Time complexity is O(n*n)
    // Space complexity is O(n)
    int minSwaps(vector<int>& nums) 
    {
        int sizeOfNums=nums.size();
        int countOnes=0;
        // Form the circular vector by attaching the vector again to vector
        // Count the 1's in the array
        for(int i=0; i<sizeOfNums; i++)
        {
            if(nums[i]==1)
            {
                countOnes++;
            }
            nums.push_back(nums[i]);
        }

        // Print constructed circular array
        sizeOfNums=nums.size();
        cout<<"\n Printing constructed circular array { ";
        for(int i=0; i<sizeOfNums; i++)
        {
            cout<<nums[i];
            if( i < (sizeOfNums - 1) )
            {
                cout<<" , ";
            } 
        }
        cout<<" }"<<endl;

        //Applying sliding window with two pointer method
        
        int answer=countOnes;
        for(int start=0,end=countOnes; end<sizeOfNums; start++,end++)
        {
            int swapCount=0;
            for(int i=start; i<end; i++)
            {
                if(nums[i]==0)
                {
                    swapCount++;
                }
            }
            answer=min(answer,swapCount);
        }

        return answer;
    }
};

int main()
{
    vector<int> input={0,1,0,1,1,0,0};

    Solution S;
    int output = S.minSwaps(input);
    cout<<"\n Minimum swaps required is "<<output<<endl;

    return 0;
}