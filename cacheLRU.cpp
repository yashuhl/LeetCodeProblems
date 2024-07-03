/* 146. LRU Cache
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.


What ia a cache?
 - Allows faster access to specific data
 - has limiter capacity

LRU - A Least Recently Used (LRU) Cache organizes items in order of use, 
allowing you to quickly identify which item hasn't been used for the longest amount of time.

LRU - Get rid of most recently used item with new item.
    - maximizes cache hits vs cache miss

Problem with FIFO is it replace heavily used data
Problem with LRU is it has ovehead i.e  as there is a page fault, we need to track of page used

Implementing with queue DSA, get function has O(n) time complexity
*/

#include<iostream>
#include<stdio.h>
#include<unordered_map>

using namespace std;

// built using Hash Map (dictonary)
// we want ordering managed in doubly linked list

// Node class holds key, value
// next and prev pointers point to next memory and previous memory 
// in Doubly Linked List
class Node
{
    public:
        int key;
        int value;
        Node* next;
        Node* prev;

        // constructor of Node class
        Node(int key, int value)
        {
            // key used in Hash map creation
            this->key = key;
            // value used to store value used to consider for cache hit and miss
            this->value = value;
            // next pointer links to next memory address of node
            next=NULL;
            // prev pointer links to prev memory address of node
            prev=NULL;
        }
};

class List
{
    public:

        // head pointer to node
        Node* head;
        // tail pointer to node
        Node* tail;

        // constructur of list , linking head and tail nodes
        List()
        {
            // 2 empty node one head and another tail
            head=new Node(0,0);
            tail=new Node(0,0);

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
        }

        // delete node at any given node link
        void deleteGivenNode(Node *deleteNode)
        {
            Node* nextTemp = deleteNode->next;
            Node* prevTemp = deleteNode->prev;
            
            prevTemp->next = nextTemp;
            nextTemp->prev = prevTemp;
        }
};

class LRUCache
{
    public:

        // capacity of cache
        int capacity;
        List L1;
        std::unordered_map<int,Node*> m;

        // constructor of LRUCache class
        LRUCache(int capacity)
        {
            // fill the capacity of class List
            this->capacity=capacity;
        }

        int get(int key)
        {
            if(m.find(key) != m.end())
            {
                Node* resNode = m[key];
                int ans = resNode->value;

                // if key found, delete Node and add to head
                // add head->next to map for considered key's value
                m.erase(key);
                L1.deleteGivenNode(resNode);
                L1.addNodeAtHead(resNode);

                m[key]=L1.head->next;
                cout<< "\n Inside get when key found\n";
                for(auto v:m)
                {
                    cout<<"{"<<v.first<<", {"<<v.second->key<<","<<v.second->value<<"} }"<<endl;
                }
                return ans;

            }
            // if key not found return -1
            cout<< "\n Inside get when key not found\n";
            for(auto v:m)
            {
                cout<<"{"<<v.first<<", {"<<v.second->key<<","<<v.second->value<<"} }"<<endl;
            }
            return -1;
        }

        void put(int key, int value)
        {
            if(m.find(key) != m.end())
            {
                // if cache found, remove from map and doublyLinked List and add to head at step 3
                Node *curr = m[key];
                m.erase(key);
                L1.deleteGivenNode(curr);
            }

            int mSize=m.size();
            if(mSize == capacity)
            {
                // if capacity is full, erase from map the tail previous key
                // and delete node from tail previous
                m.erase(L1.tail->prev->key);
                L1.deleteGivenNode(L1.tail->prev);
            }

            // add to head
            // case 1) when capacity is not full and new key came
            // case 2) when element is found and need to be recent
            // case 3) when capacity is full and requires content refresh
            L1.addNodeAtHead(new Node(key, value));
            m[key] = L1.head->next;

            cout<<"\n Inside put\n";
            for(auto v:m)
            {
                cout<<"{"<<v.first<<", {"<<v.second->key<<","<<v.second->value<<"} }"<<endl;
            }
        }

};

int main()
{

    LRUCache lRUCache(2);
    int getResult;
    lRUCache.put(1, 1); // cache is { {1,1} }
    lRUCache.put(2, 2); // cache is { {2,2} , {1,1} }
    getResult=lRUCache.get(1);    // return 1 and cache is { {1,1} , {2,2} }
    cout<<getResult<<endl;
    lRUCache.put(3, 3); // as per LRU Logic evicts key 2, cache is { {3,3} , {1,1} }
    getResult=lRUCache.get(2);    // returns -1 (not found)
    cout<<getResult<<endl;
    lRUCache.put(4, 4); // as per LRU Logic evicts key 1, cache is { {4,4} , {3=3} }
    getResult=lRUCache.get(1);    // return -1 (not found)
    cout<<getResult<<endl;
    getResult=lRUCache.get(3);    // return 3 and cache is { {3,3} , {4,4} }
    cout<<getResult<<endl;
    getResult=lRUCache.get(4);    // return 4 and cache is { {4,4} , {3=3} }
    cout<<getResult<<endl;

    return 0;
}