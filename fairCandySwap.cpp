/*
Alice and Bob have a different total number of candies. You are given two integer arrays aliceSizes and bobSizes where aliceSizes[i] is the number of candies of the ith box of candy that Alice has and bobSizes[j] is the number of candies of the jth box of candy that Bob has.

Since they are friends, they would like to exchange one candy box each so that after the exchange, they both have the same total amount of candy. The total amount of candy a person has is the sum of the number of candies in each box they have.

Return an integer array answer where answer[0] is the number of candies in the box that Alice must exchange, and answer[1] is the number of candies in the box that Bob must exchange. If there are multiple answers, you may return any one of them. It is guaranteed that at least one answer exists.

 

Example 1:

Input: aliceSizes = [1,1], bobSizes = [2,2]
Output: [1,2]
Example 2:

Input: aliceSizes = [1,2], bobSizes = [2,3]
Output: [1,2]
Example 3:

Input: aliceSizes = [2], bobSizes = [1,3]
Output: [2,3]
 

Constraints:

1 <= aliceSizes.length, bobSizes.length <= 104
1 <= aliceSizes[i], bobSizes[j] <= 105
Alice and Bob have a different total number of candies.
There will be at least one valid answer for the given input.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>

using namespace std;

/*
sum_of_aliceSizes + bobSizes[i] -aliceSizes[j] = sum_of_bobSizes - bobSizes[i] + aliceSizes[j]

==> sum_of_aliceSizes - sum_of_bobSizes = 2(aliceSizes[j] - bobSizes[i])

==> (aliceSizes[j] - bobSizes[i]) = (sum_of_aliceSizes - sum_of_bobSizes) / 2

==> aliceSizes[j] - (sum_of_aliceSizes - sum_of_bobSizes) / 2 = bobSizes[i]

*/

vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) 
{
    // sum of alice's array
    int sum_of_aliceSizes=0;
    for(size_t i=0; i<aliceSizes.size(); i++)
    {
        sum_of_aliceSizes=sum_of_aliceSizes + aliceSizes[i];
    }

    // sum of bob's array
    // Also form hash map of bob sizes
    unordered_map<int,int> bobMap;
    int sum_of_bobSizes=0;
    // space complexity O(m) - m is size of bob array to create unordered hash map
    for(size_t i=0; i<bobSizes.size(); i++)
    {
        bobMap[bobSizes[i]]=i;
        sum_of_bobSizes=sum_of_bobSizes + bobSizes[i];
    }

    int diff = (sum_of_aliceSizes - sum_of_bobSizes)/2;

    

    // Time complexity is O(n) n is number of alice array size
    for(size_t i=0; i<aliceSizes.size(); i++)
    {
        int findInbob = aliceSizes[i] - diff;

        // Time complexity is O(1), to find element in unordered map
        if(bobMap.find(findInbob) != bobMap.end())
        {
            return {aliceSizes[i],findInbob};

        }

    }
    return {-1,-1};
        
}

int main()
{

    //case 1
    vector<int> alicesSizes ={1,1};
    vector<int> bobSizes ={2,2};

    vector<int> answer = fairCandySwap(alicesSizes,bobSizes);

    cout << "\nFair Candy Swaps for case 1 are"<<endl;
    for(size_t s=0; s<answer.size(); s++)
    {
        cout << answer[s] << "\t";
    }

    //case 2
    alicesSizes ={1,2};
    bobSizes ={2,3};

    answer = fairCandySwap(alicesSizes,bobSizes);

    cout << "\nFair Candy Swaps for case 2 are"<<endl;
    for(size_t s=0; s<answer.size(); s++)
    {
        cout << answer[s] << "\t";
    }

    //case 3
    alicesSizes ={2};
    bobSizes ={1,3};

    answer = fairCandySwap(alicesSizes,bobSizes);

    cout << "\nFair Candy Swaps for case 3 are"<<endl;
    for(size_t s=0; s<answer.size(); s++)
    {
        cout << answer[s] << "\t";
    }

    return 0;

}

