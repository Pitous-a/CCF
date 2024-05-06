#include <bits/stdc++.h>
using namespace std;
int p[1001][11];
int r[1001];
int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> p[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            int *p1 = p[i];
            int *p2 = p[j];
            int k = 1;
            for (; k <= m; k++)
            {
                if (p1[k] >= p2[k])
                    break;
            }
            if (k == m + 1)
            {
                r[i] = j;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << r[i] << endl;
    }
    return 0;
}
