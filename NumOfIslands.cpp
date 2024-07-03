/*
200. Number of Islands

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

void dfs_traversal_helper(vector<vector<char>>& matrix, int row, int col)
{
    int rowSize=matrix.size();
    int colSize=matrix[row].size();
    
    if(row<0 || row >= rowSize ||
       col<0 || col >= colSize || matrix[row][col]=='0')
    {
        return;

    }
    // considering visited as 0
    matrix[row][col]='0';
    // dfs recursion on vertex neighbours as per problem
    dfs_traversal_helper(matrix,row-1,col);
    dfs_traversal_helper(matrix,row+1,col);
    dfs_traversal_helper(matrix,row,col-1);
    dfs_traversal_helper(matrix,row,col+1);
}

int dfs_traversal(vector<vector<char>>& matrix)
{
    int countIslands=0;
    for(size_t row=0; row<matrix.size(); row++)
    {
        for(size_t col=0; col<matrix[row].size(); col++)
        {
            // considering 1 inside cells as not visited
            if(matrix[row][col]=='1')
            {
                dfs_traversal_helper(matrix,row,col);
                countIslands++;
            }
        }
    }
    return countIslands;
}

int main()
{
    //case 1
    //vector<vector<char>> islands = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};

    //case 2
    vector<vector<char>> islands = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};

    cout <<"\n Printing matrix \n" << endl;
    for(size_t i=0; i<islands.size(); i++)
    {
        for(size_t j=0; j<islands[i].size(); j++)
        {
            cout<< islands[i][j]<<"\t";

        }
        cout<< endl;
    }

    int count=dfs_traversal(islands);

    cout << "\n Number of Islands = "<<count<<endl;

    return 0;
}