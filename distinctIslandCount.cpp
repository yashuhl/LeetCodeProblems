/*
694. Number of Distinct Islands

You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.

Return the number of distinct islands.

 

Example 1:


Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
Output: 1
Example 2:


Input: grid = [[1,1,0,1,1],[1,0,0,0,0],[0,0,0,0,1],[1,1,0,1,1]]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0 or 1.
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_set>

using namespace std;

void dfs_helper(vector<vector<int>> &grid, int i,int j, int row, int column, string &result,char dir)
{
    //base conditions
    // cannot go below 0 and above matrix size -1, and if the value is 0
    if(i<0 || j<0 || i>= row || j>=column || grid[i][j]==0)
    {
        return;
    }
    //mark as visited
    grid[i][j]=0;
    
    // collect direction of flow
    // L->Left, R->Right, U->Up, D->Down
    result+=dir;
    cout<<"Print string here also is "<<result<<endl;
    

    // surf through all neighbours in matrix
    // check Left path
    dfs_helper(grid,i-1,j,row,column,result,'L');
    // check right path
    dfs_helper(grid,i+1,j,row,column,result,'R');
    // check upwards path
    dfs_helper(grid,i,j-1,row,column,result,'U');
    // check downards path
    dfs_helper(grid,i,j+1,row,column,result,'D');

    // to differentiate direction movement
    // eg 1 1           vs 1 1 1
    //      1 1              1
    // IDRDCCCC         IDRCDCCC
    result=result+ 'C';
}


/*
Time complexity: O(mn)

Space complexity: O(mn)

*/
int numDistinctIslands(vector<vector<int>>& grid) 
{
    //int count=0;
    int row=grid.size();
    int column=grid[0].size();
    

    cout <<"\n Printing matrix of row "<<row<<" column "<<column << endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            cout<< grid[i][j]<<"\t";

        }
        cout<< endl;
    }

    // to capture unique island direction of calls
    // if the islands are exactly same like squre or rectangle
    // the direction of DFS path captured will be same
    // collect in hash set -->property no duplicates
    unordered_set<string> hashDirection;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            // if 1 not visited, if 0 visited --> property of graph
            if(grid[i][j]==1)
            {
                // to capture direction of flow of capturing 1's
                string result;
                dfs_helper(grid, i, j, row,column,result,'I');
                cout<<"\nprint string is "<<result<<endl;
                // insert captured direction of islands path in string
                hashDirection.insert(result);
                //count++; --> gives all distinct islands
            }
        }
        
    }
    // return size of set with unique values
    return hashDirection.size();
}

int main()
{
    //vector<vector<int>> inputGridMatrix = {{1,1,0,1,1},{1,0,0,0,0},{0,0,0,0,1},{1,1,0,1,1}};

    vector<vector<int>> inputGridMatrix = { {1,1,0}, {0,1,1}, {0,0,0}, {1,1,1}, {0,1,0} };


    int distinctIslandCount = numDistinctIslands(inputGridMatrix);
    cout<<" \n Distinct Islands are "<<distinctIslandCount<<endl;
    return 0;
}