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
You are given an array/list of ‘N’ integers. You are supposed to return the maximum sum of the subsequence with the constraint that no two elements are adjacent in the given array/list.
Note:
A subsequence of an array/list is obtained by deleting some number of elements (can be zero) from the array/list, leaving the remaining elements in their original order.
*/

//---------------------------------------------------------------- MEMONIZATION top-down
int maximumNonAdjacentSumHelper1(int n, vector<int> &nums, vector<int> &dp){     
    if (n == 0) return nums[n];
    if (n < 0) return 0;
    if (dp[n] != -1) return dp[n];

    int pick = nums[n] + maximumNonAdjacentSumHelper1(n-2, nums, dp);
    int not_pick = 0 + maximumNonAdjacentSumHelper1(n-1, nums, dp);

    dp[n] = max(pick, not_pick);
    return dp[n];
}

int maximumNonAdjacentSum1(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n + 1, -1);
    return maximumNonAdjacentSumHelper1(n-1, nums, dp);
}


//---------------------------------------------------------------- TABULATION bottom-up

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n, 0);
    if(n <= 0) return 0;

    dp[0] = nums[0];
    int negative = 0; //sarebbe l'altro base case
    
    for(int i = 1; i < n; i++){
        int pick = nums[i];
        if(i>1)  {
            pick += dp[i - 2];
        }
        int not_pick = 0 + dp[i-1];

        dp[i] = max(pick, not_pick);
    }

    return dp[n-1];
}

int main() {
    // Test case 1: Basic case
    vector<int> nums1 = {2, 1, 4, 9};
    int expected1 = 11;
    int result1 = maximumNonAdjacentSum(nums1);
    cout << "Test case 1: " << (result1 == expected1 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected1 << ", Got: " << result1 << endl << endl;

    // Test case 2: All positive numbers
    vector<int> nums2 = {1, 2, 3, 1};
    int expected2 = 4;
    int result2 = maximumNonAdjacentSum(nums2);
    cout << "Test case 2: " << (result2 == expected2 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected2 << ", Got: " << result2 << endl << endl;

    // Test case 3: With negative numbers
    vector<int> nums3 = {2, 7, 9, 3, 1};
    int expected3 = 12;
    int result3 = maximumNonAdjacentSum(nums3);
    cout << "Test case 3: " << (result3 == expected3 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected3 << ", Got: " << result3 << endl << endl;

    // Test case 4: All negative numbers
    vector<int> nums4 = {-2, -1, -4, -9};
    int expected4 = -1;
    int result4 = maximumNonAdjacentSum(nums4);
    cout << "Test case 4: " << (result4 == expected4 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected4 << ", Got: " << result4 << endl << endl;

    // Test case 5: Single element
    vector<int> nums5 = {5};
    int expected5 = 5;
    int result5 = maximumNonAdjacentSum(nums5);
    cout << "Test case 5: " << (result5 == expected5 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected5 << ", Got: " << result5 << endl << endl;

    // Test case 6: Empty array
    vector<int> nums6 = {};
    int expected6 = 0;
    int result6 = maximumNonAdjacentSum(nums6);
    cout << "Test case 6: " << (result6 == expected6 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected6 << ", Got: " << result6 << endl << endl;

    // Test case 7: Larger array
    vector<int> nums7 = {5, 3, 4, 11, 2, 8, 1, 9, 6, 7};
    int expected7 = 32;
    int result7 = maximumNonAdjacentSum(nums7);
    cout << "Test case 7: " << (result7 == expected7 ? "PASSED" : "XXXXXXXXX - FAILED") << endl;
    cout << "Expected: " << expected7 << ", Got: " << result7 << endl << endl;

    return 0;
}