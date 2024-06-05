#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

void markIsland(vector<vector<char>>& grid, int x, int y, vector<vector<int>>& visited){
    int length = grid.size();
    int high = grid[0].size();
    // Directions array for moving up, right, down, left
    int delta_x[] = {-1, 0, +1, 0};
    int delta_y[] = {0, +1, 0, -1};

    queue<pair<int, int>> q;

    q.push({x, y});
    visited[x][y] = 1; 

    
    while (!q.empty()){
        int x_cur = q.front().first;    
        int y_cur = q.front().second;    
        q.pop();

        //visited[x_cur][y_cur] = 1;
        for(int i = 0; i < 4; i++){
            int new_x = x_cur + delta_x[i];
            int new_y = y_cur + delta_y[i];
            if(new_x >= 0 && new_x < length && new_y >= 0 && new_y < high && grid[new_x][new_y] == '1' && visited[new_x][new_y] == 0){
                q.push({new_x, new_y});
                visited[new_x][new_y] = 1;
            }
        }
        
    }
    
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    int length = grid.size();
    int high = grid[0].size();
    vector<vector<int>> visited(length, vector<int>(high, 0));

    for(int i = 0; i < length; i++){
        for(int j = 0; j < high; j++){
            if(grid[i][j] == '1' && visited[i][j] == 0){
                count++;
                markIsland(grid, i, j, visited);
            }            
        }
    }
    
    return count;
}

void printMatrix(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Initialize a test matrix with 0, 1, and 2
    std::vector<std::vector<char>> matrix = {
        {'0', '1', '1', '0'},
        {'0', '1', '1', '0'},
        {'0', '0', '1', '0'},
        {'0', '0', '0', '0'},
        {'1', '1', '0', '1'}
    };    

    // Print the original matrix
    std::cout << "Original matrix:\n";
    printMatrix(matrix);

    // Call the function
    int result = numIslands(matrix);

    // Print the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}