//credit for logic goes to the one and only chandra prakash khudia

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long simulate(vector<long long> arr, int k) {
    long long total = 0;
    int n = arr.size();

    vector<long long> sorted_arr = arr;
    for (int step = 0; step < k; step++) {
        sort(sorted_arr.rbegin(), sorted_arr.rend());

        vector<long long> temp(n);
        for (int i = 0; i < n; ++i) {
            temp[i] = sorted_arr[i] * (i + 1);
        }

        long long min_val = temp[0];
        int min_index = 0;
        for (int i = 1; i < n; ++i) {
            if (temp[i] < min_val && temp[i] != 0) {
                min_val = temp[i];
                min_index = i;
            }
        }

        for (int i = 0; i <= min_index; ++i) {
            sorted_arr[i] -= sorted_arr[min_index];
        }

        total += min_val;
    }

    return total;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    long long ans = simulate(arr, k);
    cout << ans << endl;

    
}