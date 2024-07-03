/*
https://leetcode.com/problems/clone-binary-tree-with-random-pointer/description/

1485. Clone Binary Tree With Random Pointer

A binary tree is given such that each node contains an additional random pointer which could point to any node in the tree or null.

Return a deep copy of the tree.

The tree is represented in the same input/output way as normal binary trees where each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (in the input) where the random pointer points to, or null if it does not point to any node.
You will be given the tree in class Node and you should return the cloned tree in class NodeCopy. NodeCopy class is just a clone of Node class with the same attributes and constructors.

 

Example 1:


Input: root = [[1,null],null,[4,3],[7,0]]
Output: [[1,null],null,[4,3],[7,0]]
Explanation: The original binary tree is [1,null,4,7].
The random pointer of node one is null, so it is represented as [1, null].
The random pointer of node 4 is node 7, so it is represented as [4, 3] where 3 is the index of node 7 in the array representing the tree.
The random pointer of node 7 is node 1, so it is represented as [7, 0] where 0 is the index of node 1 in the array representing the tree.
Example 2:


Input: root = [[1,4],null,[1,0],null,[1,5],[1,5]]
Output: [[1,4],null,[1,0],null,[1,5],[1,5]]
Explanation: The random pointer of a node can be the node itself.
Example 3:


Input: root = [[1,6],[2,5],[3,4],[4,3],[5,2],[6,1],[7,0]]
Output: [[1,6],[2,5],[3,4],[4,3],[5,2],[6,1],[7,0]]
 

Constraints:

The number of nodes in the tree is in the range [0, 1000].
1 <= Node.val <= 106

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

class Node
{
public:

    int val;
    Node* left;
    Node* right;
    Node* random;

    Node()
    {
        val=0;
        left=NULL;
        right=NULL;
        random=NULL;
    }

    Node(int x)
    {
        val=x;
        left=NULL;
        right=NULL;
        random=NULL;
    }

    Node(int x, Node* left, Node* right, Node* random)
    {
        val=x;
        this->left=left;
        this->right=right;
        this->random=random;
    }

};

class NodeCopy
{
public:

    int val;
    NodeCopy* left;
    NodeCopy* right;
    NodeCopy* random;

    NodeCopy()
    {
        val=0;
        left=NULL;
        right=NULL;
        random=NULL;
    }

    NodeCopy(int x)
    {
        val=x;
        left=NULL;
        right=NULL;
        random=NULL;
    }

    NodeCopy(int x, NodeCopy* left, NodeCopy* right, NodeCopy* random)
    {
        val=x;
        this->left=left;
        this->right=right;
        this->random=random;
    }

};

template <typename T>
vector<vector<int>> BFS(T root)
{
    vector<vector<int>> result;
    queue<T> q;
    q.push(root);

    while(!q.empty())
    {
        T temp=q.front();
        result.push_back({temp->val,temp->random->val-1});
        q.pop();

        if(temp->left != NULL)
        {
            q.push(temp->left);
        }
        if(temp->right != NULL)
        {
            q.push(temp->right);
        }
    }
    return result;

}

unordered_map<Node*, NodeCopy*> NodeToCopy;
unordered_map<NodeCopy*, Node*> copyToNodeRandom;

// Create binary tree
NodeCopy* helper(Node* root) 
{
    
    if(root == NULL) 
    {
        return NULL;
    }

    NodeCopy* copy = new NodeCopy();

    copy->val = root->val;
    copy->left = helper(root->left);
    copy->right = helper(root->right);
    copyToNodeRandom[copy] = root->random;

    NodeToCopy[root] = copy;
    return copy;
    
}

// Populate Random.
void helper2(NodeCopy* copy) 
{
    if(copy == NULL) return;
    copy->random = NodeToCopy[copyToNodeRandom[copy]];
    helper2(copy->left);
    helper2(copy->right);
}

NodeCopy* copyRandomBinaryTree(Node* root) 
{
    auto copy = helper(root);
    helper2(copy);
    return copy;
}

NodeCopy* copyRandomBinaryTreeBFS(Node* root)
{
    unordered_map<Node*,NodeCopy*> mapNodeToNodeCopy;

    queue<Node*> q;

    // 1st bfs run, establish the hash map between Node class and NodeCopy class
    q.push(root);
    while(!q.empty())
    {
        Node* temp=q.front();
        q.pop();

        NodeCopy* copyCat=new NodeCopy(temp->val);
        mapNodeToNodeCopy[temp]=copyCat;

        if(temp->left)
        {
            q.push(temp->left);
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
    }

    // 2nd bfs run, link the NodeCopy class pointers similar to Node class
    q.push(root);
    while(!q.empty())
    {
        Node* temp=q.front();
        q.pop();

        if(temp->left != NULL)
        {
            //NodeCopy left = NodeCopy mapped to Node class left element
            mapNodeToNodeCopy[temp]->left = mapNodeToNodeCopy[temp->left];
            q.push(temp->left);

        }
        if(temp->right != NULL)
        {
            //NodeCopy right = NodeCopy mapped to Node class right element
            mapNodeToNodeCopy[temp]->right = mapNodeToNodeCopy[temp->right];
            q.push(temp->right);
        }
        if(temp->random != NULL)
        {
            //NodeCopy left = NodeCopy mapped to Node class left element
            mapNodeToNodeCopy[temp]->random = mapNodeToNodeCopy[temp->random];
        }

    }
    return mapNodeToNodeCopy[root];

}

int main()
{
    vector<vector<int>> BT = { {1,6}, {2,5}, {3,4}, {4,3}, {5,2}, {6,1}, {7,0} };

    Node* root=new Node(BT[0][0]);
    root->left=new Node(BT[1][0]);
    root->right=new Node(BT[2][0]);
    root->left->left=new Node(BT[3][0]);
    root->left->right=new Node(BT[4][0]);
    root->right->left=new Node(BT[5][0]);
    root->right->right=new Node(BT[6][0]);

    root->random = root->right->right;
    root->left->random = root->right->left;
    root->right->random = root->left->right;
    root->left->left->random = root->left->left;
    root->left->right->random = root->right;
    root->right->left->random = root->left;
    root->right->right->random = root;

    vector<vector<int>> bfSearch=BFS(root);
    cout << "\n BFS on Node is \n"<<endl;
    for(size_t i=0; i<bfSearch.size(); i++)
    {
        cout << "{"<<bfSearch[i][0]<< "," <<bfSearch[i][1] <<"}"<<"\t";
    }
    cout << endl;

    
    NodeCopy* rootCopy=new NodeCopy();
    // Shallow copy points to same memory address for pointer
    rootCopy=(NodeCopy*)root;
    bfSearch=BFS(rootCopy);

    cout << "\n BFS on Node Shallow Copy is \n"<<endl;
    for(size_t i=0; i<bfSearch.size(); i++)
    {
        cout << "{"<<bfSearch[i][0]<< "," <<bfSearch[i][1] <<"}"<<"\t";
    }
    cout << endl;

    // Deep copy using DFS
    rootCopy=copyRandomBinaryTree(root);

    bfSearch=BFS(rootCopy);

    cout << "\n BFS on Node used DFS Deep Copy is \n"<<endl;
    for(size_t i=0; i<bfSearch.size(); i++)
    {
        cout << "{"<<bfSearch[i][0]<< "," <<bfSearch[i][1] <<"}"<<"\t";
    }
    cout << endl;

    //Deep copy using BFS
    rootCopy=copyRandomBinaryTreeBFS(root);
    bfSearch=BFS(rootCopy);

    cout << "\n BFS on Node used BFS Deep Copy is \n"<<endl;
    for(size_t i=0; i<bfSearch.size(); i++)
    {
        cout << "{"<<bfSearch[i][0]<< "," <<bfSearch[i][1] <<"}"<<"\t";
    }
    cout << endl;

    return 0;
}


