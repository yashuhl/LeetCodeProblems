/*
2385. Amount of Time for Binary Tree to Be Infected

You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.

Each minute, a node becomes infected if:

The node is currently uninfected.
The node is adjacent to an infected node.
Return the number of minutes needed for the entire tree to be infected.

 

Example 1:
            1
          /   \
         5     3
         \    / \ 
          4  10  6
         / \
        9    2

Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.
Example 2:


Input: root = [1], start = 1
Output: 0
Explanation: At minute 0, the only node in the tree is infected so we return 0.
 

Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 105
Each node has a unique value.
A node with a value of start exists in the tree.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;

class TreeNode
{
    public:
        int val;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val)
        {
            this->val = val;
            left=NULL;
            right=NULL;
        }
};


void convertTreeToAdjList(TreeNode* root, vector<vector<int>> &adjList)
{
    //base condition of recurssive function
    if(root==NULL)
    {
        return;
    }

    int parent=root->val;

    if(root->left)
    {
        int leftChild=root->left->val;
        adjList[parent].push_back(leftChild);
        adjList[leftChild].push_back(parent);  
        
        convertTreeToAdjList(root->left,adjList);
    }

    if(root->right)
    {
        int rightChild=root->right->val;
        adjList[parent].push_back(rightChild);
        adjList[rightChild].push_back(parent);  

        convertTreeToAdjList(root->right,adjList);
    }
}

// & for result is required, to collect result and retain till it reaches calling function
void dfs_traversal(vector<vector<int>> &adjList, vector<bool> &isVisited,int start,int time,int &result)
{
    isVisited[start]=true;
    result=max(result,time);

    for(auto child:adjList[start])
    {
        if(!isVisited[child])
        {
            dfs_traversal(adjList,isVisited,child,time+1,result);
        }
    }
}

/*
Complexity
Time complexity:
Traversing the tree is O(n), 
while traversing the graph is O(n + m) where m is the number of edges ,
which makes it nearly O(2*n + m).
 -> time complexity is O(Sum of adjacencyDegree for all vertex+number of vertex)
                         =O(2*number of edges+vertex)

Space complexity:
The solution inculdes building another tree/graph, which doubles the expected memory. 
The vis vector adds another 1e5 bits, which wont bother much.
*/

int amountOfTime(TreeNode* root, int start) 
{
    //convert tree to graph adjacency list
    //using Preorder DFS traversal
    vector<vector<int>> adjList(11);
    convertTreeToAdjList(root, adjList);
    
    cout<<" Print Tree converted to Adjacency List "<<endl;
    cout<<"{ "<<endl;
    for(size_t i=0; (i<adjList.size()); i++)
    {
        cout<<" for index "<<i<<"-->{ ";
        for(size_t j=0; j<adjList[i].size(); j++)
        {
            cout<<adjList[i][j];
            if(j<(adjList[i].size()-1))
            {
                cout<<" , ";
            }
        }
        cout<< " } "<<endl;
    }
    cout<<" } "<<endl;
    
    vector<bool> isVisited(11,false);
    int time=0;
    int result=0;
    dfs_traversal(adjList,isVisited,start,time,result);

    return result;
        
}


int main()
{
    TreeNode *root=new TreeNode(1);
    root->left = new TreeNode(5);
    root->right = new TreeNode(3);

    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(6);

    root->left->right->left = new TreeNode(9);
    root->left->right->right = new TreeNode(2);

    int start=3;
    int finalTime=amountOfTime(root,start);
    cout<<"\n Time to infect from starting point "<< start<<" is " <<finalTime<<endl;

    return 0;
}