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

using namespace std;

/*
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

int climbStairsNoDPOptimized(int n) {
    //se sono a 1 ho solo una opzione (prendere uno scalino)
    if(n == 0 || n == 1) return 1;
    int left = climbStairsNoDPOptimized(n - 1);
    int right = climbStairsNoDPOptimized(n - 2);

    return left + right;
}

//ottimiziamo con la DP
int climbStairsNoSpaceOptHelper(int n, vector<int> &dp) {
    //se sono a 1 ho solo una opzione (prendere uno scalino)
    if(dp[n] != -1) return dp[n];
    else{
        if(n == 0 || n == 1) {
            dp[n] = 1;
            return 1;
        }
        int left = climbStairsNoSpaceOptHelper(n - 1, dp);
        int right = climbStairsNoSpaceOptHelper(n - 2, dp);

        dp[n] = left + right;
        return left + right;
    }    
}

int climbStairsNoSpaceOpt(int n) {
    vector<int> dp(n + 1, -1);
    return climbStairsNoSpaceOptHelper(n, dp);
}

//-------------------------------------------------tabulation
int climbStairsTabulazitionNoSpaceOpt(int n) {
    vector<int> dp(n + 1, -1);
    
    dp[0] = 1;
    dp[1] = 1;

    for(int i = 2; i<=n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

//una soluzione che computa in O(N) non va bene, dobbiamo farlo in almeno O(log N)
//-------------------------------------------------best solution with dp + tabulation + space optimization
int climbStairs(int n) {    
    
    int prev1 = 1;
    int prev2 = 1;
    int current = 1;

    for(int i = 2; i<=n; i++){
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main() {
    int steps;

    // Test cases
    steps = 2;
    std::cout << "Number of ways to climb " << steps << " steps: " << climbStairs(steps) << " (Expected: 2)" << std::endl;

    steps = 3;
    std::cout << "Number of ways to climb " << steps << " steps: " << climbStairs(steps) << " (Expected: 3)" << std::endl;

    steps = 4;
    std::cout << "Number of ways to climb " << steps << " steps: " << climbStairs(steps) << " (Expected: 5)" << std::endl;

    steps = 5;
    std::cout << "Number of ways to climb " << steps << " steps: " << climbStairs(steps) << " (Expected: 8)" << std::endl;

    return 0;
}