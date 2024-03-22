#include <bits/stdc++.h>
using namespace std;
#define MAXS 1 << 17
int f[MAXS];
double dp[100][MAXS];
int main()
{
    // 计算f[S]，表示S的二进制表示中1的个数
    for (int i = 0; i < MAXS; i++)
    {
        f[i] = f[i >> 1] + (i & 1);
    }
    int n, k;
    double ans = 0;
    cin >> n >> k;
    double p[n];
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    dp[0][0] = 1;
    for (int S = 0; S < (1 << n); S++)
    {
        for (int i = 0; i < 100; i++)
        {
            // 满足状态
            if (f[S] + (i - f[S]) / k == n)
            {
                ans += i * dp[i][S];
                // 输出i，S的二进制表示，dp[i][S]
                cout << i << " " << bitset<17>(S) << " " << dp[i][S] << endl;
                continue;
            }

            for (int j = 0; j < n; j++)
            {
                if (S & (1 << j))
                    dp[i + 1][S] += dp[i][S] * p[j];
                else
                    dp[i + 1][S + (1 << j)] += dp[i][S] * p[j];
            }
        }
    }
    // 保留小数点后10位
    printf("%.10lf", ans);
    return 0;
}
