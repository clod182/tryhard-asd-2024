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

int frogJumpHelper1(int n, vector<int> &heights)
{
    if (n == 0) return 0;  // Base case: we're at the start
    if (n == 1) return abs(heights[1] - heights[0]);  // Base case: only one step possible

    int option1 = frogJumpHelper1(n-1, heights) + abs(heights[n] - heights[n-1]);
    int option2 = frogJumpHelper1(n-2, heights) + abs(heights[n] - heights[n-2]);
    
    return min(option1, option2);
}

int frogJump1(int n, vector<int> &heights)
{
    return frogJumpHelper1(n-1, heights);
}

//---------------------------------------------------------------- MEMONIZATION top-down
int frogJumpHelper2(int n, vector<int> &heights, vector<int> &dp)
{
    if(dp[n] != -1) return dp[n];
    if (n == 0) return 0;  // Base case: we're at the start
    if (n == 1) {// Base case: only one step possible
        int val = abs(heights[1] - heights[0]);
        dp[n] = val;
        return val;  
    }

    int option1 = frogJumpHelper2(n-1, heights, dp) + abs(heights[n] - heights[n-1]);
    int option2 = frogJumpHelper2(n-2, heights, dp) + abs(heights[n] - heights[n-2]);
    
    dp[n] = min(option1, option2);
    return min(option1, option2);
}

int frogJump2(int n, vector<int> &heights)
{
    vector<int> dp(n + 1, -1);
    return frogJumpHelper2(n-1, heights, dp);
}

//---------------------------------------------------------------- TABULATION bottom-up
int frogJump3(int n, vector<int> &heights)
{
    vector<int> dp(n , 0);

    dp[0] = 0; // base case if (n == 0) return 0;
    
    for(int i=1; i<n; i++){
        int option1 = dp[i-1] + abs(heights[i] - heights[i-1]);
        int option2 = INT_MAX;
        if(i>1){
            option2 = dp[i-2] + abs(heights[i] - heights[i-2]);
        }
        dp[i] = min(option1, option2);         
    }

    return dp[n-1];
}

//---------------------------------------------------------------- SPACE OPTIMIZATION
int frogJump(int n, vector<int> &heights)
{
    int prev = 0; // --> dp[i-1]
    int prev1 = 0; // --> dp[i-2]
    
    for(int i=1; i<n; i++){
        int option1 = prev + abs(heights[i] - heights[i-1]);
        int option2 = INT_MAX;
        if(i>1){
            option2 = prev1 + abs(heights[i] - heights[i-2]);
        }
        int current = min(option1, option2);
        prev1 = prev;  
        prev = current;     
    }

    return prev;
}

int main() {
    // Test case 1
    vector<int> height1 = {10, 20, 30, 10};
    int expected1 = 20; // Risultato previsto
    int result1 = frogJump(height1.size(), height1);
    cout << "Test case 1: " << (result1 == expected1 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected1 << ", Got: " << result1 << endl;

    // Test case 2
    vector<int> height2 = {10, 50, 10};
    int expected2 = 0; // Risultato previsto
    int result2 = frogJump(height2.size(), height2);
    cout << "Test case 2: " << (result2 == expected2 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected2 << ", Got: " << result2 << endl;

    // Test case 3
    vector<int> height3 = {10, 20, 10, 10, 30, 40};
    int expected3 = 30; // Risultato previsto
    int result3 = frogJump(height3.size(), height3);
    cout << "Test case 3: " << (result3 == expected3 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected3 << ", Got: " << result3 << endl;

    // Test case 4
    vector<int> height4 = {40, 10, 20, 70, 80, 10};
    int expected4 = 30; // Risultato previsto
    int result4 = frogJump(height4.size(), height4);
    cout << "Test case 4: " << (result4 == expected4 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected4 << ", Got: " << result4 << endl;

    // Test case 5
    vector<int> height5 = {1, 100, 1, 1, 100, 1};
    int expected5 = 2; // Risultato previsto
    int result5 = frogJump(height5.size(), height5);
    cout << "Test case 5: " << (result5 == expected5 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected5 << ", Got: " << result5 << endl;

    // Test case 6
    vector<int> height6 = {30, 10, 60, 10, 60, 50};
    int expected6 = 40; // Risultato previsto
    int result6 = frogJump(height5.size(), height6);
    cout << "Test case 6: " << (result6 == expected6 ? "Passed" : "Failed") << endl;
    cout << "Expected: " << expected6 << ", Got: " << result6 << endl;

    return 0;
}