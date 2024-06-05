#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

int numberOfIslands(vector<vector<int>>& grid) {

    queue<pair<pair<int,int>,int>> q;    
    int length = grid.size();
    int high = grid[0].size();
    int visited[length][high];

    int delta_x[] = {-1,0,+1,0};
    int delta_y[] = {0,+1,0,-1};

    int time = 0;

    for(int i=0; i<length; i++)  {
        for(int j=0; j<high; j++)  {
            if(grid[i][j] == 2)  {
                q.push({{i,j},0});
                visited[i][j] = 2;
            }
            else{
                visited[i][j] = 0;
            }
        }
    }

    while (!q.empty())  {
        int x_top_elem = q.front().first.first;
        int y_top_elem = q.front().first.second;
        int time_top_elem = q.front().second;
        q.pop();

        //test togliere
        time = max(time, time_top_elem);
        
        for(int i=0; i<4; i++)  {
            int new_x = x_top_elem+delta_x[i];
            int new_y = y_top_elem+delta_y[i];

            if(new_x >= 0 && new_x < length && new_y >= 0 && new_y < high
            && visited[new_x][new_y] != 2 && grid[new_x][new_y] == 1)  {
                q.push({{new_x,new_y}, time+1});
                visited[new_x][new_y] = 2;                
            }
        }       

    }  

    for(int i=0; i<length; i++)  {
        for(int j=0; j<high; j++)  {
            if(grid[i][j] == 1 && visited[i][j]!= 2) {
                return -1;
            }
        }
    }
    return time;    
}

void printMatrix(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Initialize a test matrix with 0, 1, and 2
    std::vector<std::vector<int>> matrix = {
        {2, 1, 0, 2, 1},
        {1, 0, 1, 2, 1},
        {1, 0, 0, 2, 1},
        {2, 0, 1, 1, 1},
        {2, 1, 0, 0, 2}
    }; 

    /*std::vector<std::vector<int>> matrix = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };*/

    // Print the original matrix
    std::cout << "Original matrix:\n";
    printMatrix(matrix);

    // Call the function
    int result = numberOfIslands(matrix);

    // Print the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}