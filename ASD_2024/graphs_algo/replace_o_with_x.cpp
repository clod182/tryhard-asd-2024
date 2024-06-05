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

vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
        // code here


}

int main() {
    // Define test cases
    vector<vector<char>> mat1 = {
        {'X', 'O', 'X', 'X'},
        {'O', 'X', 'O', 'X'},
        {'X', 'X', 'O', 'O'},
        {'X', 'O', 'X', 'X'}
    };

    vector<vector<char>> mat2 = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'X'},
        {'O', 'X', 'X', 'X'}
    };

    // Run the fill function on the test cases
    vector<vector<char>> result1 = fill(4, 4, mat1);
    vector<vector<char>> result2 = fill(4, 4, mat2);

    // Print the results for mat1
    cout << "Result for mat1:" << endl;
    for (const auto& row : result1) {
        for (char val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Print the results for mat2
    cout << "Result for mat2:" << endl;
    for (const auto& row : result2) {
        for (char val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}