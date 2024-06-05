#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;

// Function to find distance of nearest 1 in the grid for each cell.
vector<vector<int>> nearest(vector<vector<int>>& grid) {
    int value_to_check = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    int delta_x[] = {0, 0, 1, -1};
    int delta_y[] = {1, -1, 0, 0};
    queue<pair<pair<int, int>, int>> q;
    vector<vector<int>> visited(rows, vector<int>(cols, 0));
    vector<vector<int>> ret(rows, vector<int>(cols, -1));

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(grid[i][j] == value_to_check) { //replace with wanted value
                ret[i][j] = 0;
                q.push({{i, j}, 0});
                visited[i][j] = 1;
            }
        }
    }

    while (!q.empty()) {    
        int cur_x = q.front().first.first;
        int cur_y = q.front().first.second;
        int cur_value = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int new_x = cur_x + delta_x[i];
            int new_y = cur_y + delta_y[i];
            if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && visited[new_x][new_y] == 0) {
                ret[new_x][new_y] = cur_value + 1;
                q.push({{new_x, new_y}, cur_value + 1});
                visited[new_x][new_y] = 1;
            }
        }
    }    

    return ret;
}

void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test case 1
    vector<vector<int>> grid1 = {
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    cout << "Original Grid 1:" << endl;
    printGrid(grid1);

    vector<vector<int>> result1 = nearest(grid1);

    cout << "Result Grid 1:" << endl;
    printGrid(result1);

    // Test case 2
    vector<vector<int>> grid2 = {
        {1, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {1, 0, 0, 1}
    };

    cout << "Original Grid 2:" << endl;
    printGrid(grid2);

    vector<vector<int>> result2 = nearest(grid2);

    cout << "Result Grid 2:" << endl;
    printGrid(result2);

    return 0;
}
