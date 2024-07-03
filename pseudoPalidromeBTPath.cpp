/*
1457. Pseudo-Palindromic Paths in a Binary Tree
Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said to be pseudo-palindromic if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

 

Example 1:



Input: root = [2,3,1,3,1,null,1]
Output: 2 
Explanation: The figure above represents the given binary tree. There are three paths going from the root node to leaf nodes: the red path [2,3,3], the green path [2,1,1], and the path [2,3,1]. Among these paths only red path and green path are pseudo-palindromic paths since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).
Example 2:



Input: root = [2,1,1,1,3,null,null,null,null,null,1]
Output: 1 
Explanation: The figure above represents the given binary tree. There are three paths going from the root node to leaf nodes: the green path [2,1,1], the path [2,1,3,1], and the path [2,1]. Among these paths only the green path is pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1] (palindrome).
Example 3:

Input: root = [9]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 9
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>

using namespace std;

class Node
{
    public:
        int value;
        Node* left;
        Node* right;

        Node(int value)
        {
            this->value=value;
            left=NULL;
            right=NULL;
        }
};

vector<vector<int>> bfs(Node* root)
{
    vector<vector<int>> ansArray;

    queue<Node*> q;
    q.push(root);

    
    while(!q.empty())
    {
        vector<int> tempArray;
        int count=q.size();

        cout<<"I am here "<< count <<"\n";
        for(int i=0; i<count; i++)
        {
            Node* temp=q.front();
            tempArray.push_back(temp->value);
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
        ansArray.push_back(tempArray); 
    }
    return ansArray;
}

vector<vector<int>> dfs(Node* root)
{
    vector<vector<int>> ansArray;

    stack<Node*> s;
    s.push(root);

    
    while(!s.empty())
    {
        vector<int> tempArray;
        int count=s.size();

        cout<<"I am here "<< count <<"\n";
        for(int i=0; i<count; i++)
        {
            Node* temp=s.top();
            tempArray.push_back(temp->value);
            s.pop();

            if(temp->left)
            {
                s.push(temp->left);
            }

            if(temp->right)
            {
                s.push(temp->right);
            }
            
        }
        ansArray.push_back(tempArray); 
    }
    return ansArray;
}

void preOrder(Node* root, vector<int> &result)
{
    if(root ==NULL)
    {
        return;
    }
    result.push_back(root->value);
    preOrder(root->left,result);
    preOrder(root->right,result);
}

vector<int> dfsPreOrder(Node* root)
{
    vector<int> result;
    Node* curr=root;
    preOrder(curr,result);
    return result;
}

bool checkPalindrome(unordered_map<int,int> &mapIndex)
{
    int odds=0;
    for(auto v:mapIndex)
    {
        if(v.second%2 != 0)
        {
            odds++;
            if(odds>1)
            {
                return false;
            }
        }
    }
    return true;
}
void pseudoPalinRecursiveDFS(unordered_map<int,int> &mapIndex, Node* root, int &ans)
{
    if(root==NULL)
    {
        cout<<"\nRoot is null here\n";
        
        return;

    }

    mapIndex[root->value]++;

    cout << "\n here 1 root self value is "<< root->value << " and its count is "<<mapIndex[root->value];

    // condition check for pseudo palindrome path
    if( root->left == NULL && root->right == NULL)
    {
        if(checkPalindrome(mapIndex))
        {
            ans++;
        }
    }
    

    if(root->left)
    {
        cout << "\n here 1.1 root self value and its associated left call is  "<< root->value << " and its count is "<<mapIndex[root->value];

    }
    pseudoPalinRecursiveDFS(mapIndex,root->left,ans);
    cout<<endl;
    cout << "\n here 2 root self value  is "<< root->value << " and its count is "<<mapIndex[root->value];

    if(root->right)
    {
        cout << "\n here 2.1 root self value and its associated right call is  "<< root->value << " and its count is "<<mapIndex[root->value];

    }
    
    pseudoPalinRecursiveDFS(mapIndex,root->right,ans);
    cout<<endl;
    cout << "\n here 3 root self previous value is "<< root->value << " and its count is "<<mapIndex[root->value];

     mapIndex[root->value]--;
     cout << "\n here 4 root self value count after reducing is "<< root->value << " and its count is "<<mapIndex[root->value];

     if(mapIndex[root->value] == 0)
     {
        mapIndex.erase(root->value);
     }
}

int pseudoPalindromicPaths (Node* root) 
{
    // vector to map count of integers which ranges from 1 to 9
    unordered_map<int,int> mapIndex;
    // pass answer to helper function
    int ans=0;
    // send a cpy of root as tree root changes in dfs call
    Node* curr=root;
    // call preorder recurssive dfs call
    pseudoPalinRecursiveDFS(mapIndex,curr,ans);
    return ans;
}

int main()
{
    Node* root = new Node(2);
    root->left = new Node(3);
    root->right = new Node(1);
    root->left->left = new Node(3);
    root->left->right = new Node(1);
    root->right->right = new Node(1);

    vector<vector<int>> result=dfs(root);

    cout<<"\n DFS collecting array is\n";
    for(size_t i=0; i<result.size(); i++)
    {
        for(size_t j=0; j<result[i].size(); j++)
        {
            cout<<result[i][j]<<"\t";
        }
        cout<<endl; 
    }


    vector<int> ans;
    ans=dfsPreOrder(root);

    cout<<"\n DFS collecting array using Preorder is\n";
    for(size_t i=0; i<ans.size(); i++)
    {
        cout<<ans[i]<<"\t";
    }
    cout<<endl;

    int palindrome=pseudoPalindromicPaths(root);
    cout<<"\n Pseudo Palindrome Path is " << palindrome << "\n";
}