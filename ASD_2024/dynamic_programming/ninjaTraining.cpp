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
Ninja is planing this ‘N’ days-long training schedule. 
Each day, he can perform any one of these three activities. (Running, Fighting Practice or Learning New Moves). 
Each activity has some merit points on each day. As Ninja has to improve all his skills, he can’t do the same activity in two consecutive days. 
Can you help Ninja find out the maximum merit points Ninja can earn?

You are given a 2D array of size N*3 ‘POINTS’ with the points corresponding to each day and activity. 
Your task is to calculate the maximum number of merit points that Ninja can earn.

For Example
If the given ‘POINTS’ array is [[1,2,5], [3 ,1 ,1] ,[3,3,3] ],the answer will be 11 as 5 + 3 + 3.
*/

//---------------------------------------------------------------- MEMONIZATION top-down
int ninjaTrainingHelper1(int day, int prevAct, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    int n_activity = points[0].size();    
    if(day == 0) {        
        int maxi = 0;
        for(int i=0; i<n_activity; i++){
            if (i != prevAct && points[0][i] > maxi){
                maxi = points[0][i];                
            }
        }
        return maxi;
    }   
    //else
    if(dp[day][prevAct] != -1) return dp[day][prevAct];

    int maxi = 0;
    for(int i=0; i<n_activity; i++){
        if (i != prevAct){
            int points_sum = points[day][i] + ninjaTrainingHelper1(day-1, i, points, dp);          
            maxi = max(maxi, points_sum);      
        }
    }
    dp[day][prevAct] = maxi;
    return dp[day][prevAct];
}

int ninjaTraining1(int n, vector<vector<int>> &points)
{
    int n_activity = points[0].size();
    vector<vector<int>> dp(n, vector<int>(n_activity+1, -1));
    int prevAct = n_activity;

    return ninjaTrainingHelper1(n-1, prevAct, points, dp);
}

//---------------------------------------------------------------- TABULATION bottom-up
int ninjaTraining(int n, vector<vector<int>> &points)
{
    int n_activity = points[0].size();
    vector<vector<int>> dp(n, vector<int>(n_activity+1, 0));
    int prevAct = n_activity;

    dp[0][0] = points[0][0];
    dp[0][1] = points[0][1];
    dp[0][2] = points[0][2];

    for(int day = 1; day < n; day++){
        for(int act = 0; act < n_activity; act++){

        }
    }

    //INCOMPLETO, DA CAPIRE MEGLIO IL CONCETTO IN VIDEO

    return dp[n][]
}

int main() {
    vector<vector<vector<int>>> testCases = {
        {{1, 2, 5}, {3, 1, 1}, {3, 3, 3}}, // Expected result: 11 (5 + 3 + 3)
        {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}}, // Expected result: 210 (70 + 50 + 90)
        {{18, 11, 19}, {4, 13, 7}, {15, 8, 18}, {5, 6, 9}}, // Expected result: 55 (19 + 13 + 18 + 5)
        {{1, 2, 3}}, // Expected result: 3 (3)
        {{5, 10, 15}, {10, 20, 5}, {15, 5, 10}, {5, 15, 20}}, // Expected result: 55 (15 + 20 + 15 + 5)
        {{1, 3, 1}, {6, 1, 2}, {3, 2, 5}, {4, 3, 7}, {2, 4, 1}}, // Expected result: 20 (3 + 6 + 5 + 7 + 4)
        {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}}, // Expected result: 40 (10 + 10 + 10 + 10)
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, // Expected result: 0 (0 + 0 + 0)
        {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}}, // Expected result: 15 (1 + 2 + 3 + 4 + 5)
        {{100, 200, 300}, {200, 300, 100}, {300, 100, 200}, {100, 200, 300}} // Expected result: 1100 (300 + 300 + 300 + 300)
    };

    vector<int> expectedResults = {
        11, 210, 55, 3, 55, 20, 40, 0, 15, 1200
    };

    bool allTestsPassed = true;

    for (size_t i = 0; i < testCases.size(); i++) {
        int n = testCases[i].size();
        int result = ninjaTraining(n, testCases[i]);
        cout << "Test case " << i + 1 << ": ";
        for (const auto &day : testCases[i]) {
            cout << "[";
            for (int activity : day) {
                cout << activity << " ";
            }
            cout << "] ";
        }
        cout << "\nExpected result: " << expectedResults[i] << "\n";
        cout << "Actual result: " << result << "\n";
        if (result == expectedResults[i]) {
            cout << "Test passed\n\n";
        } else {
            cout << "Test failed\n\n";
            allTestsPassed = false;
        }
    }

    if (allTestsPassed) {
        cout << "All tests passed successfully.\n";
    } else {
        cout << "Some tests failed.\n";
    }

    return 0;
}