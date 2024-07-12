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

int frogJumpKJumpsHelper1(int n, vector<int> &heights, int k)
  {
    if (n == 0) return 0;  // Base case: we're at the start

    int bestOption = INT_MAX;
    
    for(int i=1; i <= k; i++){
        if(n-i >= 0){
            int option =  frogJumpKJumpsHelper1(n-i, heights, k) + abs(heights[n] - heights[n-i]);
            bestOption = min(bestOption, option);
        }        
    }    
    
    return bestOption;
}

int frogJumpKJumps1(int n, vector<int> &heights, int k)
{
    
    return frogJumpKJumpsHelper1(n-1, heights, k);
}

//---------------------------------------------------------------- MEMONIZATION top-down
int frogJumpKJumpsHelper(int n, vector<int> &heights, int k, vector<int> &dp)
  {
    if (dp[n] != -1) return dp[n];
    if (n == 0) return 0;  // Base case: we're at the start

    int bestOption = INT_MAX;
    
    for(int i=1; i <= k; i++){
        if(n-i >= 0){
            int option =  frogJumpKJumpsHelper(n-i, heights, k, dp) + abs(heights[n] - heights[n-i]);
            bestOption = min(bestOption, option);
        }        
    }    
    
    dp[n] = bestOption;
    return bestOption;
}

int frogJumpKJumps(int n, vector<int> &heights, int k)
{
    vector<int> dp(n + 1, -1);
    return frogJumpKJumpsHelper(n-1, heights, k, dp);
}

//---------------------------------------------------------------- TABULATION bottom-up


//---------------------------------------------------------------- SPACE OPTIMIZATION


int main() {
    // Test case 1
    int n1 = 5;
    vector<int> heights1 = {10, 30, 40, 50, 20};
    int k1 = 3;
    int expected1 = 30; // Minimum cost expected for this test case
    
    int result1 = frogJumpKJumps(n1, heights1, k1);
    cout << "Test Case 1: Expected result is " << expected1 << ", got " << result1 << endl;

    // Test case 2
    int n2 = 3;
    vector<int> heights2 = {10, 20, 10};
    int k2 = 1;
    int expected2 = 20; // Minimum cost expected for this test case
    
    int result2 = frogJumpKJumps(n2, heights2, k2);
    cout << "Test Case 2: Expected result is " << expected2 << ", got " << result2 << endl;

    // Test case 3
    int n3 = 2;
    vector<int> heights3 = {10, 10};
    int k3 = 100;
    int expected3 = 0; // Minimum cost expected for this test case
    
    int result3 = frogJumpKJumps(n3, heights3, k3);
    cout << "Test Case 3: Expected result is " << expected3 << ", got " << result3 << endl;

    // Test case 4
    int n4 = 10;
    vector<int> heights4 = {40, 10, 20, 70, 80, 10, 20, 70, 80, 60};
    int k4 = 4;
    int expected4 = 40; // Minimum cost expected for this test case
    
    int result4 = frogJumpKJumps(n4, heights4, k4);
    cout << "Test Case 4: Expected result is " << expected4 << ", got " << result4 << endl;

    return 0;
}