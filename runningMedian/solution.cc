#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void rebalance (priority_queue<int>* max_heap, priority_queue< int, vector<int>, greater<int> >* min_heap) {
    int displaced_integer;
    if (max_heap->size() - min_heap->size() == 2) {
        displaced_integer = max_heap->top();
        max_heap->pop();
        min_heap->push(displaced_integer);
    } else if (min_heap->size() - max_heap->size() == 2) {
        displaced_integer = min_heap->top();
        min_heap->pop();
        max_heap->push( displaced_integer );
    }
}

double recalculate_median( priority_queue<int>* max_heap, priority_queue< int, vector<int>, greater<int> >* min_heap ) {
    double median;
    if (max_heap->size() > min_heap->size()) {
        median = (double) max_heap->top();
    } else if (min_heap->size() > max_heap->size()) {
        median = (double) min_heap->top();
    } else { // if ==
        median = (float)max_heap->top() + (float)min_heap->top();
        median = median / 2;
    }
    return median;
}

int main() {
    int number_of_inputs;
    cin >> number_of_inputs;
    
    priority_queue<int> max_heap_of_lower_half;
    priority_queue< int, vector<int>, greater<int> > min_heap_of_upper_half;
    
    int current_input;
    double median = -1;
    for (int i = 0; i < number_of_inputs; i++) {
        cin >> current_input;
        if (median == -1) {
            max_heap_of_lower_half.push( current_input );
            median = current_input;
            printf("%.1f\n", median);
            continue;
        } else if (current_input <= median) {
            max_heap_of_lower_half.push(current_input);
        } else if (current_input > median) {
            min_heap_of_upper_half.push(current_input);
        }
        rebalance( &max_heap_of_lower_half, &min_heap_of_upper_half );
        median = recalculate_median( &max_heap_of_lower_half, &min_heap_of_upper_half );
        printf("%.1f\n", median);
    }

    return 0;
}
