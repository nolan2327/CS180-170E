#include <iostream>
#include <map>
#include <vector>

using namespace std;

// HOMEWORK #1
int findMinimumFrequency(int N, std::vector<int> A) {
    /*
     * Given an array, finds the smallest element with the least frequency.
     *
     *
        Example:
            std::vector<int> arr = { 1, 1, 5, 6, 50, 2, 2, 2, 2};
            cout << findMinimumFrequency(arr.size(), arr);
     */
    std::map<int, int> value_to_frequency;

    // Step 1: Count frequencies
    for (int i = 0; i < N; i++) {
        value_to_frequency[A[i]]++;
    }

    // Step 2: Find the minimum frequency
    int min_freq = INT_MAX; // Every number will be less than this
    for (auto& [val, freq] : value_to_frequency) { // Use auto so compiler decides type :P
        if (freq < min_freq) {
            min_freq = freq;
        }
    }

    // Step 3: Find the smallest element with that frequency
    int min_val = INT_MAX;
    for (auto& [val, freq] : value_to_frequency) {
        if (freq == min_freq && val < min_val) {
            min_val = val;
        }
    }

    return min_val;
}
