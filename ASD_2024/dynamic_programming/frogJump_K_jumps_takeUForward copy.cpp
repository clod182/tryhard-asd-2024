#include <iostream>
#include <iomanip>
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
#include <climits>

using namespace std;

/*
Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th stair. 
At a time the frog can climb either one or two steps. A height[N] array is also given. 
Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is abs(height[i]- height[j]), where abs() means the absolute difference. 
We need to return the minimum energy that can be used by the frog to jump from stair 0 to stair N-1.
*/

//---------------------------------------------------------------- SIMPLE RECURSIVE

int frogJumpKJumpsHelper(int n, vector<int> &heights, int k, int &bestOption)
  {
    if (n == 0) return 0;  // Base case: we're at the start
    if (n == 1) return abs(heights[1] - heights[0]);  // Base case: only one step possible    

    for(int i=0; i < k; i++){
        int option =  frogJumpKJumpsHelper(n-i, heights, k, bestOption) + abs(heights[n] - heights[n-i]);
        if (option < bestOption) bestOption = option;
    }    
    
    return bestOption;
}

int frogJumpKJumps(int n, vector<int> &heights, int k)
{
    int bestOption = INT_MAX;
    return frogJumpKJumpsHelper(n-1, heights, k, bestOption);
}

//---------------------------------------------------------------- MEMONIZATION top-down


//---------------------------------------------------------------- TABULATION bottom-up


//---------------------------------------------------------------- SPACE OPTIMIZATION


int main() {
    // Test case 1
    int n1 = 5;
    vector<int> heights1 = {10, 30, 40, 20, 50};
    int k1 = 2;
    int expected1 = 30; // Minimum cost expected for this test case
    
    int result1 = frogJumpKJumps(n1, heights1, k1);
    cout << "Test Case 1: Expected result is " << expected1 << ", got " << result1 << endl;
    
    // Test case 2
    int n2 = 7;
    vector<int> heights2 = {30, 10, 60, 80, 20, 50, 40};
    int k2 = 3;
    int expected2 = 70; // Minimum cost expected for this test case
    
    int result2 = frogJumpKJumps(n2, heights2, k2);
    cout << "Test Case 2: Expected result is " << expected2 << ", got " << result2 << endl;
    
    // Test case 3
    int n3 = 3;
    vector<int> heights3 = {10, 20, 30};
    int k3 = 1;
    int expected3 = 20; // Minimum cost expected for this test case
    
    int result3 = frogJumpKJumps(n3, heights3, k3);
    cout << "Test Case 3: Expected result is " << expected3 << ", got " << result3 << endl;
    
    return 0;
}