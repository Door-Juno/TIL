#include <iostream>
#include <vector>

using namespace std;

void selection_sort(vector<int>& v){
    int n = v.size();
    for (int i = 0 ; i < n - 1 ; ++i){
        int min_idx = i ;

        for ( int j = i + 1; j < n ; ++j){
            if (v[j] < v[min_idx]){
                min_idx = j;
            }
        }
        int temp = v[i] ;
        v[i] = v[min_idx];
        v[min_idx] = temp;
    }
}