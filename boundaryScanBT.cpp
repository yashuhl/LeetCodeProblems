/*
545. Boundary of Binary Tree

The boundary of a binary tree is the concatenation of the root, 
the left boundary, the leaves ordered from left-to-right, and the reverse order of the right boundary.

The left boundary is the set of nodes defined by the following:

The root node's left child is in the left boundary. If the root does not have a left child,
then the left boundary is empty.
If a node in the left boundary and has a left child, then the left child is in the left boundary.
If a node is in the left boundary, has no left child, but has a right child, 
then the right child is in the left boundary.

The leftmost leaf is not in the left boundary.

The right boundary is similar to the left boundary, except it is the right side of the root's right subtree. 
Again, the leaf is not part of the right boundary, 
and the right boundary is empty if the root does not have a right child.

The leaves are nodes that do not have any children. For this problem, the root is not a leaf.

Given the root of a binary tree, return the values of its boundary

Example 1:

Input: root = [1,null,2,3,4]
Output: [1,3,4,2]
Explanation:
- The left boundary is empty because the root does not have a left child.
- The right boundary follows the path starting from the root's right child 2 -> 4.
  4 is a leaf, so the right boundary is [2].
- The leaves from left to right are [3,4].
Concatenating everything results in [1] + [] + [3,4] + [2] = [1,3,4,2].
Example 2:


Input: root = [1,2,3,4,5,6,null,null,null,7,8,9,10]
Output: [1,2,4,7,8,9,10,6,3]
Explanation:
- The left boundary follows the path starting from the root's left child 2 -> 4.
  4 is a leaf, so the left boundary is [2].
- The right boundary follows the path starting from the root's right child 3 -> 6 -> 10.
  10 is a leaf, so the right boundary is [3,6], and in reverse order is [6,3].
- The leaves from left to right are [4,7,8,9,10].
Concatenating everything results in [1] + [2] + [4,7,8,9,10] + [6,3] = [1,2,4,7,8,9,10,6,3].
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-1000 <= Node.val <= 1000

*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;

//Tree class
class Tree
{
    public:
        int value;
        Tree* left;
        Tree* right;

        Tree(int value)
        {
            this->value=value;
            left=NULL;
            right=NULL;
        }
};

void scanLeft(Tree* leftNode, vector<int> &boundaryScan)
{
    //required to break the recurssive flow
    if(leftNode==NULL)
    {
        return;
    }
    //required to avoid left boundary collecting leaves
    if( (leftNode->left==NULL) && (leftNode->right==NULL) )
    {
        return;
    }

    // collect the data result in inorder form
    boundaryScan.push_back(leftNode->value);
    // If left exist, put that to boundary
    if(leftNode->left)
    {
        scanLeft(leftNode->left, boundaryScan);
    }
    // collect lefts right boundaries if left does not present
    else if(leftNode->right)
    {
        scanLeft(leftNode->right, boundaryScan);
    }
}

void scanLeaves(Tree* leaves, vector<int> &boundaryScan)
{
    //required to break the recurssive flow
    if(leaves == NULL)
    {
        return;
    }
    // required to collect the leaves
    if( (leaves->left==NULL) && (leaves->right==NULL) )
    {
        // collect only leaves which has left and right as NULL
        boundaryScan.push_back(leaves->value);
        return;
    }
    scanLeaves(leaves->left, boundaryScan);
    scanLeaves(leaves->right, boundaryScan);
}

void scanRight(Tree* rightNode, vector<int> &boundaryScan)
{
    //required to break the recurssive flow
    if(rightNode == NULL)
    {
        return;
    }
    //required to avoid right boundary collecting leaves
    if( (rightNode->right == NULL) && (rightNode->left == NULL) )
    {
        return;
    }

    // collect right boundaries if present
    if(rightNode->right)
    {
        scanRight(rightNode->right, boundaryScan);
    }
    // collect rights left boundaries if right does not present
    else if(rightNode->left)
    {
        scanRight(rightNode->left, boundaryScan);
    }
    //collect result in post order manner for right boundries
    boundaryScan.push_back(rightNode->value);
}

//Time complexity is O(n)
//Space complexity is O(n)
vector<int> boundaryOfBinaryTree(Tree* root) 
{
    // Fill up result
    vector<int> boundaryScan;

    if(root==NULL)
    {
        return boundaryScan;
    }
    
    // Push root
    boundaryScan.push_back(root->value);

    // eg: if only one node is present, it will be accounted for left and leaves
    // to avoid that check for its left and right null return result
    if( (root->left==NULL) && (root->right==NULL) )
    {
        return boundaryScan;
    }

    // Scan and push Left boundaries
    scanLeft(root->left, boundaryScan);

    // Scan and push left leaves
    scanLeaves(root, boundaryScan);

    // Scan and push Right boundaries
    scanRight(root->right, boundaryScan);

    return boundaryScan;
}
vector<vector<int>> collectBFS(Tree* root)
{
    vector<vector<int>> result;
    queue<Tree*> q;
    q.push(root);

    while(!q.empty())
    {
        //cout<<"\nI am here "<<q.size()<<endl;
        vector<int> tempVector;
        // do not try to include size in loop directly, as the size gets updated inside the loop
        // we want static size before collecting layer elements
        int qSize=q.size();
        for(int i=0; i<qSize; i++)
        {
            Tree* temp=q.front();
            
            //cout<<" temp->value "<<temp->value<<endl;
            tempVector.push_back(temp->value);
            q.pop();
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
        result.push_back(tempVector);
    }
    return result;
}

int main()
{
    Tree* root=new Tree(1);
    root->left=new Tree(2);
    root->right=new Tree(3);

    root->left->left=new Tree(4);
    root->left->right=new Tree(5);

    root->right->left=new Tree(6);

    root->left->left->left=new Tree(7);
    root->left->left->right=new Tree(8);

    root->left->right->left=new Tree(9);
    root->left->right->right=new Tree(10);

    vector<vector<int>> resultOutput=collectBFS(root);

    cout << "\n Result vector BFS search is"<<endl;
    cout << " {"<<endl;
    for(size_t i=0; i<resultOutput.size(); i++)
    {
        cout<<" { ";
        for(size_t j=0; j<resultOutput[i].size(); j++)
        {
            cout<<resultOutput[i][j];
            if(j < (resultOutput[i].size()-1))
            {
                cout<<" , ";
            }
        }
        cout <<" } "<<endl;
    }
    cout<<" }"<<endl;

    cout<<"\n Boundary of Binary Tree is { ";
    vector<int> boundary=boundaryOfBinaryTree(root);
    
    for(size_t i=0; i<boundary.size(); i++)
    {
        cout<<boundary[i];
        if(i<boundary.size()-1)
        {
            cout<<" , ";
        }
    }
    cout<<" }"<<endl;
    return 0;
}