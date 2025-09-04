//credit for logic goes to the one and only chandra prakash khudia
#include <iostream>
using namespace std;

long long temp[1000];
long long sorted_arr[1000];

void sort_desc(long long arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[max_idx]) max_idx = j;
        }
        if (max_idx != i) {
            long long tmp = arr[i];
            arr[i] = arr[max_idx];
            arr[max_idx] = tmp;
        }
    }
}

long long simulate(long long arr[], int n, int k) {
    long long total = 0;
    for (int i = 0; i < n; ++i) sorted_arr[i] = arr[i];

    for (int step = 0; step < k; ++step) {
        sort_desc(sorted_arr, n);
        for (int i = 0; i < n; ++i) temp[i] = sorted_arr[i] * (i + 1);

        long long min_val = temp[0];
        int min_index = 0;
        for (int i = 1; i < n; ++i) {
            if (temp[i] < min_val && temp[i] != 0) {
                min_val = temp[i];
                min_index = i;
            }
        }

        for (int i = 0; i <= min_index; ++i) sorted_arr[i] -= sorted_arr[min_index];
        total += min_val;
    }

    return total;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        long long arr[1000];
        for (int i = 0; i < n; ++i) cin >> arr[i];
        long long ans = simulate(arr, n, k);
        cout << ans << endl;
    }
    return 0;
}

