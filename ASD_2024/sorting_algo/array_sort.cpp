#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

//-----------------------------------------------------------------------------------------------------
// bubbleSort O^2 Time complexity
void bubbleSort(std::vector<int>& arr) {
    int endOfArr = arr.size();    

    // i è lo slider che esclude gli elementi a inizio array già ordinati    
    for (int i=0; i<endOfArr-1; i++){
        for (int j=endOfArr-1; j>i; j--) {
            if (arr[j] < arr[j-1]){
                std::swap(arr[j], arr[j-1]);
            }
        }        
    }     
}

//-----------------------------------------------------------------------------------------------------
// selectionSort O^2 Time complexity
int linearSearchMin(std::vector<int>& arr, int from){
    if (arr.empty() || from >= arr.size()) {
        return -1;
    }    
    int minpos = from;
    for(int i=from+1; i<arr.size(); i++){
        if (arr[i] < arr[minpos]){           
            minpos = i;
        }
    }
    return minpos;
}

void selectionSort(std::vector<int>& arr) {
    for (int i=0; i<arr.size(); i++){
        int minAtm = linearSearchMin(arr, i);
        if (minAtm != i && minAtm != -1){
            std::swap(arr[minAtm], arr[i]);
        }
    }
}

//-----------------------------------------------------------------------------------------------------
// insertionSort O^2  Time complexity
void insertionSort(std::vector<int>& arr) {
    for (int i=1; i<arr.size(); i++){
        int j=i;
        while(j>0 && arr[j] < arr[j-1]){
            std::swap(arr[j], arr[j-1]);
            j--;
        }
    }
}

//-----------------------------------------------------------------------------------------------------
// mergeSort O(n log n)  Time complexity
void merge(std::vector<int>& arr,int head, int mid, int tail) {
    std::vector<int> sortedArr;
    int left = head;
    int right = mid+1;
    while (left <= mid && right <= tail){
        if (arr[left] < arr[right]){
            sortedArr.push_back(arr[left]);
            left++;
        }
        else {
            sortedArr.push_back(arr[right]);
            right++;
        }
    }

    while(left<=mid){
        sortedArr.push_back(arr[left]);
        left++;
    }

    while(right<=tail){
        sortedArr.push_back(arr[right]);
        right++;
    }

    for(int i=0; i<sortedArr.size(); i++){
        arr[head+i] = sortedArr[i];
    }
}
 
void mergeSortCore(std::vector<int>& arr, int head, int tail) {
    if (head < tail){
        int mid = (head+tail)/2;
        mergeSortCore(arr, head, mid);
        mergeSortCore(arr, mid+1, tail);  
        merge(arr, head, mid, tail);
    }
}

void mergeSort(std::vector<int>& arr) {
    mergeSortCore(arr, 0, arr.size()-1);
}

//-----------------------------------------------------------------------------------------------------
// heapSort O(n log n)  Time complexity
// Function to heapify a subtree rooted with node i, n is the size of the heap
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);        
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    int lastNonLeafNode = n / 2 - 1;

    // Build heap (rearrange array)
    for (int i = lastNonLeafNode; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract elements from heap
    for (int i = n - 1; i >= 0; i--) {        
        std::swap(arr[0], arr[i]);        
        heapify(arr, i, 0);
    }
}

//-----------------------------------------------------------------------------------------------------
// quickSort O(n log n)  Time complexity

int findPlaceAndPartition(std::vector<int>& arr, int start, int end) {  
    int pivot = start;
    int i=start;
    int j=end;
    while(i<j){
        while(arr[i] <= arr[pivot] && i <= end ){
            i++;
        }

        while(arr[j] > arr[pivot] && j >= start ){
            j--;
        }
        
        if(i<j){
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[pivot], arr[j]); //"last elemet"
    return j;
} 

void quickSortCore(std::vector<int>& arr, int start, int end) {   
    if(start < end){
        int position = findPlaceAndPartition(arr, start, end);        
        quickSortCore(arr, start, position-1);
        quickSortCore(arr, position+1, end);
    }
}
void quickSort(std::vector<int>& arr) {
    int size = arr.size();
    quickSortCore(arr, 0, size-1);
}

/* #region utility function */

// Function to print a vector
void printVector(const std::vector<int>& arr) {
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

// Function to test and validate sort algo
bool testCurrentSortAlgoo(std::vector<int> arr) {
    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());

    //use the sort algo to test
    quickSort(arr);

    return arr == sortedArr;
}

/* #endregion utility function */

int main() {
    // Test cases
    std::vector<std::vector<int>> testCases = {
        {64, 34, 25, 12, 22, 11, 90},     // General case
        {},                               // Empty array
        {1},                              // Single element
        {2, 1},                           // Two elements
        {5, 4, 3, 2, 1},                  // Reverse order
        {1, 2, 3, 4, 5},                  // Already sorted
        {1, 3, 2, 5, 4},                  // Random order
        {5, 5, 5, 5, 5},                  // All elements the same
        {1000, 500, 0, -500, -1000},      // Mixed positive and negative
        {INT_MAX, INT_MIN, 0, INT_MAX, INT_MIN}, // Including integer limits
        {-1, -2, -3, -4, -5},             // All negative numbers
        {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, // Large sorted array
        {1000, 900, 800, 700, 600, 500, 400, 300, 200, 100}, // Large reverse sorted array
        {1, 3, 3, 1, 2, 2},               // Duplicates and unordered
        {0, 0, 0, 0, 0},                  // All zeros
        {-1, 0, 1, 2, -2, 0},             // Mix of negative, zero and positive
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},  // Reverse sorted from 10 to 1
        {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, // Already sorted prime numbers
        {29, 23, 19, 17, 13, 11, 7, 5, 3, 2}, // Reverse sorted prime numbers
        {5, -1, 3, -2, 4, 0},             // Mixed small set
        {INT_MAX, INT_MIN, INT_MAX, INT_MIN}, // Alternating max/min values
        {999999, -999999, 0, 123456, -123456}, // Large and small mix
        {INT_MAX, INT_MAX, INT_MIN, INT_MIN, 0}, // Repeated max/min values
        {-5, -1, -3, -2, -4, 0},          // Mixed with zero
        {7, 8, 5, 3, 2, 1, 9, 6, 4, 0}    // Random order 0-9
    };

    int passed = 0;

    // Testing and printing results
    for (const auto& testCase : testCases) {
        std::cout << "Original array: ";
        printVector(testCase);

        std::vector<int> arr = testCase;
        quickSort(arr);

        std::cout << "Sorted array: ";
        printVector(arr);

        if (testCurrentSortAlgoo(testCase)) {
            std::cout << "Test Passed" << std::endl;
            passed++;
        } else {
            std::cout << "Test Failed" << std::endl;
        }

        std::cout << "---------------------------" << std::endl;
    }

    // Calculate and print the percentage of passed tests
    double passPercentage = (static_cast<double>(passed) / testCases.size()) * 100;
    std::cout << "Passed " << passed << " out of " << testCases.size() << " tests." << std::endl;
    std::cout << "Pass percentage: " << passPercentage << "%" << std::endl;

    return 0;
}
