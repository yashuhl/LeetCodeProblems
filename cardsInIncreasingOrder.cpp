/*
950. Reveal Cards In Increasing Order

You are given an integer array deck. There is a deck of cards where every card has a unique integer. The integer on the ith card is deck[i].

You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:

Take the top card of the deck, reveal it, and take it out of the deck.
If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
If there are still unrevealed cards, go back to step 1. Otherwise, stop.
Return an ordering of the deck that would reveal the cards in increasing order.

Note that the first entry in the answer is considered to be the top of the deck.

 

Example 1:

Input: deck = [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation: 
We get the deck in the order [17,13,11,2,3,5,7] (this order does not matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.
Example 2:

Input: deck = [1,1000]
Output: [1,1000]
 

Constraints:

1 <= deck.length <= 1000
1 <= deck[i] <= 106
All the values of deck are unique.

*/

#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;


// Time complexity O(n(logn))
vector<int> deckRevealedIncreasing(vector<int>& deck) 
{
    // Sort array in ascending order
    // {2,3,5,7,11,13,17}
    
    sort(deck.begin(),deck.end());

    //size of deck
    int sizeOfDeck = deck.size();
    // collecting ans vector
    vector<int> ans(sizeOfDeck,0);
    
    // Index for deck
    // {0,1,2,3,4,5,6}

    // Uses FIFO data structure to store index  
    queue<int> index;
    for(int i=0; i<sizeOfDeck; i++)
    {
        index.push(i);
    }

    // v maintains the deck sorted array index
    int v=0;

    // check index queue is empty or not for displaying

    // 1st round collects n/2 elements
    // 2nd round collects n/4 elements
    // 3rd round collects n/8 elements and so on
    // n(logn) events
    while(!index.empty())
    {
        // Take the top card of the deck, reveal it, and take it out of the deck.
        // Place it to answer
        int temp=index.front();
        ans[temp] = deck[v];
        index.pop();

        // If there are still cards in the deck then 
        //put the next top card of the deck at the bottom of the deck.
        if(!index.empty())
        {
            int secondTemp=index.front();
            index.pop();
            index.push(secondTemp);
        }
        v++;
    }
    return ans;
}

int main()
{
    vector<int> array= {17,13,11,2,3,5,7};
    int size=array.size();

    cout<< "\nI am original array"<<endl;
    for(int i=0; i<size; i++)
    {
        cout<<array[i]<< "\t";

    }
    cout<<endl;

    vector<int> resultArray;
    resultArray=deckRevealedIncreasing(array);
    cout<< "\nI am asked deck array"<<endl;
    for(int i=0; i<size; i++)
    {
        cout<<resultArray[i]<< "\t";

    }
    cout<<endl;

    return 0;
}