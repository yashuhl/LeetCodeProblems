/*
875. Koko Eating Bananas

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

//Use binary search to come to proper minimu bananas koko should consume
// minimum is 1
// maximum is max piles in banana
// for the mid calculate kokos hours by dividing each pile by mid value collect the total hours koko is spending
// if the calculated kokos hours is greater than given gaurds hour h
// for binary search decrease maximum to mid+1, else increase mimimum to mid
// do the loop till minimum satisfies less than maximum hours.
// Time cmplexity is O(nlogn)
int minEatingSpeed(vector<int> &piles, int h)
{
    int minimum=1;
    int maximum=0;
    int pilesSize=piles.size();

    // Colect max bananas and sum of all bananas
    for(int i=0; i<pilesSize; i++)
    {
        maximum=max(maximum,piles[i]);
    }

    // if the pile of banana size is equal to hours guards away
    // minimum koko has to eat per hour is max banana pile number
    if(pilesSize==h)
    {
        return maximum;
    }

    while(minimum < maximum)
    {
        int mid = ( minimum + maximum )/2;
        int hours=0;
        // have for loop of collecting hours to do binary search to identify minimum number
        for(auto v:piles)
        {
            // convert the division decimal to next lower number using ceil
            //cout<<"\nfor value "<< v << " the hours is "<<ceil((float) v/mid)<<endl;
            hours=hours+ceil((float) v/mid);

        }
        //cout<<"\n minimum is "<<minimum<<" maximum is "<<maximum<<" mid is "<<mid<<" total hours is "<<hours<<endl;
        if(hours > h)
        {
            minimum = mid+1;
        }
        else
        {
            maximum = mid;
        }
    }
    return minimum;

}

int main()
{
    vector<int> piles;
    int h;

    //case 1
    piles = {3,6,7,11};
    h=8;

    //case 2
    piles = {30,11,23,4,20};
    h=5;

    //case 3
    piles = {30,11,23,4,20};
    h=6;

    int k = minEatingSpeed(piles,h);

    cout<< "\n Expected minimum eating speed is "<<k<<" in "<<h<<" hours for gaurds to return\n";

    return 0;
}