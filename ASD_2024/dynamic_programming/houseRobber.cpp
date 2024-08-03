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
Mr. X is a professional robber planning to rob houses along a street. Each house has a certain amount of money hidden.

All houses along this street are arranged in a circle. That means the first house is the neighbour of the last one.
Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two 
adjacent houses are broken long long into on the same night.

You are given an array/list of non-negative long long integers 'ARR' representing the amount of money of each house. 
Your task is to return the maximum amount of money Mr. X can rob tonight without alerting the police.
*/

//---------------------------------------------------------------- TABULATION bottom-up
long long int houseRobberHelper(vector<long long int> &nums){
    long long int n = nums.size();
    vector<long long int> dp(n, 0);    
    if(n <= 0) return 0;

    dp[0] = nums[0];
    long long int negative = 0; //sarebbe l'altro base case
    
    for(long long int i = 1; i < n; i++){
        long long int pick = nums[i];
        if(i>1)  {
            pick += dp[i - 2];
        }
        long long int not_pick = 0 + dp[i-1];

        dp[i] = max(pick, not_pick);
    }
    return dp[n-1];
}

long long int houseRobber(vector<int> &nums) {
    long long int n = nums.size();
    vector<long long int> long_nums(nums.begin(), nums.end());

    if (n == 1) return long_nums[0];

    vector<long long int> temp1, temp2;
    for(long long int i = 0; i < n; i++) {
        if (i != 0) temp1.push_back(long_nums[i]);
        if (i != n-1) temp2.push_back(long_nums[i]);
    }

    return max(houseRobberHelper(temp1), houseRobberHelper(temp2));
}

int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5},
        {2, 7, 9, 3, 1},
        {10, 2, 2, 10, 1},
        {1},
        {5, 5, 10, 100, 10, 5},
        {10, 20, 30, 40, 50},
        {8, 7, 6, 5, 4},
        {0, 0, 0, 0, 0},
        {},
        {1, 2, 3, 1},
        {1, 3, 1, 3, 100},
        {2, 3, 2, 3, 2, 3},
        {1, 3, 1, 3, 1, 3, 1},
        {100, 90, 80, 70, 60, 50, 40},
        {1, 2}
    };

    for(auto &testCase : testCases) {
        cout << "Test case: ";
        for(int num : testCase) {
            cout << num << " ";
        }
        cout << "\nMax amount robbed: " << houseRobber(testCase) << "\n\n";
    }

    return 0;
}