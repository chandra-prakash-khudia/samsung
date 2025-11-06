#include <iostream>
#include <iomanip>
#include<vector>
using namespace std;

// int main()
// {

//     cout.setf(std::ios::fixed);
//     cout << setprecision(6);

//     int T;
//     if (!(cin >> T))
//         return 0;

//     const int MAXN = 200;
//     while (T--)
//     {
//         int n, m;
//         long long timeMin;
//         cin >> n >> m >> timeMin;
//         if (n <= 0)
//         {
//             cout << "1 1.000000\n";
//             continue;
//         }

//         double P[MAXN][MAXN];
//         double rowSum[MAXN];
//         for (int i = 0; i < n; ++i)
//         {
//             rowSum[i] = 0.0;
//             for (int j = 0; j < n; ++j)
//                 P[i][j] = 0.0;
//         }

//         for (int i = 0; i < m; ++i)
//         {
//             int u, v;
//             double p;
//             cin >> u >> v >> p;
//             int ui = u - 1, vi = v - 1;
//             P[ui][vi] += p;
//             rowSum[ui] += p;
//         }

//         long long steps = timeMin / 10LL;

//         // distribution vector v (0-based)
//         static double v[MAXN], vnext[MAXN];
//         for (int i = 0; i < n; ++i)
//             v[i] = 0.0;
//         v[0] = 1.0; // start at node 1

//         // if steps small and n large, repeated multiplication is fine
//         for (long long s = 0; s < steps; ++s)
//         {
//             // zero next vector
//             for (int j = 0; j < n; ++j)
//                 vnext[j] = 0.0;

//             // vnext[j] = sum_i v[i] * P[i][j]
//             for (int i = 0; i < n; ++i)
//             {
//                 double vi = v[i];
//                 if (vi == 0.0)
//                     continue;
//                 // distribute vi along row i
//                 for (int j = 0; j < n; ++j)
//                 {
//                     if (P[i][j] != 0.0)
//                         vnext[j] += vi * P[i][j];
//                 }
//                 // if rowSum[i] < 1 and you treat leftover as leaving,
//                 // that leftover mass is implicitly lost (no addition to vnext).
//             }
//             // copy vnext -> v
//             for (int j = 0; j < n; ++j)
//                 v[j] = vnext[j];
//         }

//         // find best division
//         int bestIndex = 0;
//         double bestProb = v[0];
//         for (int i = 1; i < n; ++i)
//         {
//             if (v[i] > bestProb + 1e-15)
//             {
//                 bestProb = v[i];
//                 bestIndex = i;
//             }
//         }

//         // print 1-based index and probability
//         cout << (bestIndex + 1) << " " << bestProb << "\n";
//     }
//     return 0;
// }

// int main()
// {
//      cout.setf(ios::fixed);
//     cout << setprecision(6);

//     int t;
//     cin >> t;
//     const int MAX = 100;
//     while (t--)
//     {
//         int n;
//         cin >> n;
//         int m;
//         cin >> m;
//         int time;
//         cin>>time;  
//         double pos[MAX][MAX];
//         for (int i = 1; i <= n; i++)
//         {
//             for (int j = 1; j <= n; j++)
//             {
//                 pos[i][j] = 0.0;
//             }
//         }


//         for (int i = 0; i < m; i++)
//         {
//             int u, v;
//             double x;
//             cin >> u >> v >> x;
//             pos[u][v] += x;
//         }

//         double v[n + 1];
//         for (int i = 1; i <= n; i++)
//             v[i] = 0.00;
//         v[1] = 1.00;
//         int steps = time / 10;
//         double temp[n + 1];
//         for (int k = 0; k < steps; k++)
//         {

//             for (int i = 1; i <= n; i++)
//                 temp[i] = 0.00;


//             for (int i = 1; i <= n; i++)
//             {
//                 double vi = v[i];
//                 if (vi == 0.0)
//                     continue;
//                 for (int j = 1; j <= n; j++)
//                 {
//                     if(pos[i][j] != 0.0)
//                     temp[j] += v[i] * pos[i][j];
//                 }
//             }
//             for (int j = 1; j <= n; j++)
//                 v[j] = temp[j];
//         }

//         int bestIndex = 1;
//         double bestProb = v[1];
//         for (int i = 2; i <= n; ++i)
//         {
//             if (v[i] > bestProb + 1e-15)
//             {
//                 bestProb = v[i];
//                 bestIndex = i;
//             }
//         }


//         cout << (bestIndex ) << " " << bestProb << "\n";
//     }
// }


using Matrix = vector<vector<double>>;
const double EPS = 1e-12;

// Matrix multiplication: res = A * B
Matrix multiply(const Matrix &A, const Matrix &B, int n) {
    Matrix res(n + 1, vector<double>(n + 1, 0.0));
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k <= n; ++k)
            // if (A[i][k] > EPS)
                for (int j = 1; j <= n; ++j)
                    res[i][j] += A[i][k] * B[k][j];
    return res;
}

// Matrix exponentiation: P^exp
Matrix matrixExpo(Matrix P, int exp, int n) {
    Matrix result(n + 1, vector<double>(n + 1, 0.0));
    // Identity matrix
    for (int i = 1; i <= n; ++i)
        result[i][i] = 1.0;

    while (exp > 0) {
        if (exp % 2)
            result = multiply(result, P, n);
        P = multiply(P, P, n);
        exp /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);

    int t;
    cin >> t;
    while (t--) {
        int n, m, time;
        cin >> n >> m >> time;
        int steps = time / 10;

        // Initialize probability matrix
        Matrix P(n + 1, vector<double>(n + 1, 0.0));
        for (int i = 0; i < m; ++i) {
            int u, v;
            double p;
            cin >> u >> v >> p;
            P[u][v] += p;
        }

        // Matrix exponentiation: P^steps
        Matrix P_power = matrixExpo(P, steps, n);

        // Initial vector v: starting at division 1
        vector<double> v(n + 1, 0.0);
        v[1] = 1.0;

        // Final probabilities after steps: v * P^steps
        vector<double> final(n + 1, 0.0);
        for (int j = 1; j <= n; ++j)
            for (int i = 1; i <= n; ++i)
                final[j] += v[i] * P_power[i][j];

        // Find best division
        int bestIndex = 1;
        double bestProb = final[1];
        for (int i = 2; i <= n; ++i) {
            if (final[i] > bestProb + EPS) {
                bestProb = final[i];
                bestIndex = i;
            }
        }

        cout << bestIndex << " " << bestProb << "\n";
    }

    return 0;
}
