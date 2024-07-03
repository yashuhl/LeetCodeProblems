/*
460. LFU Cache

Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3
 

Constraints:

1 <= capacity <= 104
0 <= key <= 105
0 <= value <= 109
At most 2 * 105 calls will be made to get and put.

*/

#include<iostream>
#include<stdio.h>
#include<unordered_map>

using namespace std;

// Node class holds key, value
// next and prev pointers point to next memory and previous memory 
// in Doubly Linked List
class Node
{
    public:
        int key;
        int value;
        int count;
        Node* next;
        Node* prev;

        // constructor of Node class
        Node(int key, int value)
        {
            // key used in Hash map creation
            this->key = key;
            // value used to store value used to consider for cache hit and miss
            this->value = value;
            // count for frequency monitoring how many times Node called
            count=1;
            // next pointer links to next memory address of node
            next=NULL;
            // prev pointer links to prev memory address of node
            prev=NULL;
        }
};

class List
{
    public:

        // To monitor size of List, assign 0 in constructor.
        // increment when add node apperas , decrement when delete node appears
        int size;
        // head pointer to node
        Node* head;
        // tail pointer to node
        Node* tail;

        // constructur of list , linking head and tail nodes
        List()
        {
            // 2 empty node one head and another tail
            size=0;
            head=new Node(0,0);
            tail=new Node(0,0);

            // avoids multiple if else condition check of null, by maintaining constant head and tail
            head->next=tail;
            tail->prev=head;
        }  

        // add node at head next position
        void addNodeAtHead(Node* newNode)
        {   
            Node* temp = head->next;

            newNode->next = temp;
            newNode->prev = head;

            head->next = newNode;
            temp->prev = newNode;
            size++;
        }

        // delete node at any given node link
        void deleteGivenNode(Node *deleteNode)
        {
            Node* nextTemp = deleteNode->next;
            Node* prevTemp = deleteNode->prev;
            
            prevTemp->next = nextTemp;
            nextTemp->prev = prevTemp;
            size--;
        }
};

class LFUCache 
{


    // capacity of cache \ max frequency cache can have
    int capacity;
    // minimum frequency
    int minFreq;
    // current size of cache
    int curSize;
    // Object of class List
    List L1;

    // store key and its associated node
    std::unordered_map<int,Node*> keyNodeMap;
    // store frequency and its associated List
    std::unordered_map<int,List*> freqListMap;

public:

    // constructor of LRUCache class
    LFUCache(int capacity) 
    {
        this->capacity = capacity;
        minFreq=0;
        curSize=0;
    }

    // important for LFU cache implementation i.e
    // Updating the frequency map for which frequency the List falls into
    void updateFreqListMap(Node* node)
    {
        // take out the node from key,node map
        keyNodeMap.erase(node->key);
        // remove the node from frequency, list map also
        // counter will be helpful to identify the frequency list it belong to
        freqListMap[node->count]->deleteGivenNode(node);

        // update the minimum frequency also if any list emptiness happened because of removal of node
        if( (node->count == minFreq) && (freqListMap[node->count]->size == 0) )
        {
            minFreq++;
        }

        // create next higher frequency list
        List* nextHigherFreqList = new List();
        // check for List in next higher frequency list
        if(freqListMap.find(node->count+1) != freqListMap.end())
        {
            // if List present assign to newly created List
            nextHigherFreqList = freqListMap[node->count+1];
        }
        // increment counter
        node->count++;
        // add to front of List
        nextHigherFreqList->addNodeAtHead(node);
        // update the frequency, list map
        freqListMap[node->count]=nextHigherFreqList;
        // update the key, node map
        keyNodeMap[node->key]=node;
    }
    
    int get(int key) 
    {
        // if get key is present in key, node map
        if(keyNodeMap.find(key) != keyNodeMap.end())
        {
            // get node of the requested key
            Node* resultNode = keyNodeMap[key];
            // get the value from the requested key node
            int result = resultNode->value;

            //Update the frequency, list map
            updateFreqListMap(resultNode);

            return result;
        }
        return -1;
        
    }
    
    void put(int key, int value) 
    {
        // corner case for empty capacity
        if(capacity == 0)
        {
            return;
        }
        // if the key is present, update the value
        // as List containing the node is accessed, update frequency
        if(keyNodeMap.find(key) != keyNodeMap.end())
        {
            Node* newNode=keyNodeMap[key];
            newNode->value=value;
            updateFreqListMap(newNode);
        }
        else
        {
            // If capacity is full follow LRU method 
            if(curSize == capacity)
            {
                // get minimum frequency list
                List* list=freqListMap[minFreq];
                // delete its least used node of tail previous from key, node map
                keyNodeMap.erase(list->tail->prev->key);
                // delete nodes frequency from frequency, List map
                list->deleteGivenNode(list->tail->prev);
                // decrease size
                curSize--;
            }
            // increase size , applies for both capacity full case or not full case
            curSize++;

            // if code comes here its first time in flow new key,value came
            // minimum frequency
            minFreq=1;
            // initialize new list
            List* ListFreq = new List();
            // if already minFreq list is present in frequency, list map
            // assign the same to new List frequency created
            if(freqListMap.find(minFreq) != freqListMap.end())
            {
                ListFreq=freqListMap[minFreq];
            }
            // initialize new node
            Node* newNode  = new Node(key,value);
            // add new node using new list to the head next position
            ListFreq->addNodeAtHead(newNode);
            // add new Node to key,node map
            keyNodeMap[key]=newNode;
            // add new node contained list to frequency, list map
            freqListMap[minFreq]=ListFreq;
        }
        
    }
};

int main()
{
    LFUCache lfu(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    int result=lfu.get(1);      // return 1
                    // cache=[1,2], cnt(2)=1, cnt(1)=2
    cout << result<<endl;
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                    // cache=[3,1], cnt(3)=1, cnt(1)=2
    result=lfu.get(2);      // return -1 (not found)
    cout << result<<endl;
    result=lfu.get(3);      // return 3
                    // cache=[3,1], cnt(3)=2, cnt(1)=2
    cout << result<<endl;
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                    // cache=[4,3], cnt(4)=1, cnt(3)=2
    result=lfu.get(1);      // return -1 (not found)
    cout << result<<endl;
    result=lfu.get(3);      // return 3
                    // cache=[3,4], cnt(4)=1, cnt(3)=3
    cout << result<<endl;
    result=lfu.get(4);      // return 4
                    // cache=[4,3], cnt(4)=2, cnt(3)=3
    cout << result<<endl;
    return 0;
}