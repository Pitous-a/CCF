#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll t[10000000000];
// 判断是否为质数
bool isP(ll n)
{
    if (n <= 1)
        return false;
    for (ll j = 2; j <= sqrt(n); j++)
    {
        // 不是质数
        if (n % j == 0)
            return false;
    }
    return true;
}
ll query(ll n, int k)
{
    if (isP(n))
        return 1;
    for (ll i = 2; i <= 100001; i++)
    {
        if (isP(i))
        {
            ll temp = n;
            int temp_count = 0;
            while (temp % i == 0)
            {
                temp /= i;
                temp_count++;
            }
            // 舍弃小于k的部分
            if (temp_count < k)
                n = temp;
            if (n == 1)
                return 1;
        }
    }
    return n;
}

int main(int argc, char const *argv[])
{
    ll n;
    int k, q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> n >> k;
        cout << query(n, k) << endl;
    }
    return 0;
}
