#include <bits/stdc++.h>
#include <vector>

using namespace std;

long merge(vector<int>* workArray, vector<int>* destinationArray, int begin, int end) {
    int lIndex = begin;
    int lEnd = begin + (end-begin)/2;
    
    int rIndex = lEnd + 1;
    int rEnd = end;
    
    int arrayPos = begin;
    long inversions = 0;
    
    while (arrayPos <= end){
        if (lIndex > lEnd) {
            (*workArray)[arrayPos] = (*destinationArray)[rIndex];
            rIndex++;
        } else if(rIndex > rEnd) {
            (*workArray)[arrayPos] = (*destinationArray)[lIndex];
            lIndex++;
        } else {
            if ((*destinationArray)[rIndex] < (*destinationArray)[lIndex]) {
                // number of inversions is equal to the number of unprocessed
                // records in the left subarray
                inversions += lEnd - lIndex + 1;
                (*workArray)[arrayPos] = (*destinationArray)[rIndex];
                rIndex++;
            } else {
                (*workArray)[arrayPos] = (*destinationArray)[lIndex];
                lIndex++;
            }
        }
        
        arrayPos++;
    }
    
    // copy the workArray range into the destinationArray
    for (int i = begin; i <= end; i++) {
        (*destinationArray)[i] = (*workArray)[i];
    }
    
    return inversions;
}


long mergeSort(vector<int>* workArray, vector<int>* destinationArray, int low, int high) {
    if (low < high) {
        int mid = low + (high - low)/2;
        long leftMerge = mergeSort(workArray, destinationArray, low, mid);
        long rightMerge = mergeSort(workArray, destinationArray, mid+1, high);
        
        long mergeInversions = merge(workArray, destinationArray, low, high);
        return mergeInversions + leftMerge + rightMerge;
        //return 1;
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        vector<int> destinationArray(n);
        vector<int> workArray(n);

        for(int arr_i = 0; arr_i < n; arr_i++){
           int val;
           cin >> val;
           destinationArray[arr_i] = val;
           workArray[arr_i] = val;
        }
        long result = mergeSort(&workArray, &destinationArray, 0, n-1);
        cout << result << endl;
    }
    return 0;
}
