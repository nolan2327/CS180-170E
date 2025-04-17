#include <iostream>
#include <vector>

using namespace std;

/*
 * Given a sorted array A of n distinct integers in increasing order, design an algorithm to determine
 * if there exists an index i such that A[i] = i. The algorithm should run in O(log n) time.
 * I used an approach like binary search to accomplish this.
    Example:

    std::vector<int> vec_induction = { 1, 2, 3, 4, 5 };
    // This is for induction. If it works here, it should work for every case.

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    if(findContainedValue(14, vec)) {
        cout << "Contained" << endl;
    }
    else {
        cout << "Not contained" << endl;
    }

 */

// HOMEWORK #2
bool findContainedValue(int value, std::vector<int>& vec) {

    if(vec.size() == 2) {
        return vec[0] == value || vec[1] == value;
    }

    int middle = vec.size() / 2;

    cout << "Middle at " << middle << " with size of array " << vec.size()
         << ", with value " << vec[middle] << endl;

    if(vec[middle] == value) {
        return true;
    }
    else if (vec[middle] < value) {
        std::vector<int> subVec(vec.begin() + middle, vec.end());
        return findContainedValue(value, subVec);
    }
    else { // vec[middle] < value
        std::vector<int> subVec(vec.begin(), vec.begin() + middle);
        return findContainedValue(value, subVec);
    }
}