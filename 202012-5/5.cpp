#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m;
const ll MAXINT = 1e+7;
const ll MOD = 1e+9 + 7;
// 左右子节点
ll lc[MAXINT], rc[MAXINT];
// 总和
ll sumx[MAXINT], sumy[MAXINT], sumz[MAXINT];
// 懒标记
ll x[MAXINT], y[MAXINT], z[MAXINT], mul[MAXINT];
int ro[MAXINT];
// 节点编号
ll no = 0;
void pushdown(ll p, ll start, ll end)
{
    if (!x[p] && !y[p] && !z[p] && !mul[p] && !ro[p])
        return;
    // 如果p为叶子节点，则将懒标记清空并退出
    if (start == end)
    {
        x[p] = y[p] = z[p] = mul[p] = ro[p] = 0;
        return;
    }
    // 获取左右子节点，若为空则创建
    ll &lchild = lc[p];
    ll &rchild = rc[p];
    if (!lchild) lchild = ++no;
    if (!rchild) rchild = ++no;
    ll mid = (start + end) >> 1;
    // 若mul[p]标签为0，则置为1
    if (!mul[p]) mul[p] = 1;
    // 下放总和(先*后+)
    sumx[lchild] = ((sumx[lchild] % MOD * (mul[p] % MOD)) % MOD + (x[p] % MOD * (mid - start + 1) % MOD) % MOD) % MOD;
    sumy[lchild] = ((sumy[lchild] % MOD * (mul[p] % MOD)) % MOD + (y[p] % MOD * (mid - start + 1) % MOD) % MOD) % MOD;
    sumz[lchild] = ((sumz[lchild] % MOD * (mul[p] % MOD)) % MOD + (z[p] % MOD * (mid - start + 1) % MOD) % MOD) % MOD;

    sumx[rchild] = ((sumx[rchild] % MOD * (mul[p] % MOD)) % MOD + (x[p] % MOD * (end - mid) % MOD) % MOD) % MOD;
    sumy[rchild] = ((sumy[rchild] % MOD * (mul[p] % MOD)) % MOD + (y[p] % MOD * (end - mid) % MOD) % MOD) % MOD;
    sumz[rchild] = ((sumz[rchild] % MOD * (mul[p] % MOD)) % MOD + (z[p] % MOD * (end - mid) % MOD) % MOD) % MOD;

    // 总和旋转
    ll templ, tempr;
    for (int i = 0; i < ro[p]; i++)
    {
        templ = sumx[lchild];
        sumx[lchild] = sumy[lchild];
        sumy[lchild] = sumz[lchild];
        sumz[lchild] = templ;
        tempr = sumx[rchild];
        sumx[rchild] = sumy[rchild];
        sumy[rchild] = sumz[rchild];
        sumz[rchild] = tempr;
    }

    // 下放懒标记
    // 1、加法标记
    ll xl = x[p], yl = y[p], zl = z[p], tl;
    // 先逆时针转ro[p]圈
    for (int i = 0; i < ro[lchild]; i++)
    {
        tl = xl;
        xl = zl;
        zl = yl;
        yl = tl;
    }

    x[lchild] = ((mul[p] % MOD * x[lchild]) % MOD + xl % MOD) % MOD;
    y[lchild] = ((mul[p] % MOD * y[lchild]) % MOD + yl % MOD) % MOD;
    z[lchild] = ((mul[p] % MOD * z[lchild]) % MOD + zl % MOD) % MOD;

    ll xr = x[p], yr = y[p], zr = z[p], tr;
    // 先逆时针转ro[p]圈
    for (int i = 0; i < ro[rchild]; i++)
    {
        tr = xr;
        xr = zr;
        zr = yr;
        yr = tr;
    }
    x[rchild] = ((mul[p] % MOD * x[rchild]) % MOD + xr % MOD) % MOD;
    y[rchild] = ((mul[p] % MOD * y[rchild]) % MOD + yr % MOD) % MOD;
    z[rchild] = ((mul[p] % MOD * z[rchild]) % MOD + zr % MOD) % MOD;

    // 2、乘法标记
    if (mul[p] != 1)
    {
        if (!mul[lchild]) mul[lchild] = 1;
        mul[lchild] = (mul[lchild] % MOD * (mul[p] % MOD)) % MOD;
        if (!mul[rchild]) mul[rchild] = 1;
        mul[rchild] = (mul[rchild] % MOD * (mul[p] % MOD)) % MOD;
    }

    // 3、旋转标记
    ro[lchild] = (ro[lchild] + ro[p]) % 3;
    ro[rchild] = (ro[rchild] + ro[p]) % 3;

    // 下放完毕,清空标记
    x[p] = y[p] = z[p] = mul[p] = ro[p] = 0;
    return;
}
void add(ll &p, ll start, ll end, ll &l, ll &r, ll a, ll b, ll c)
{
    // 判断节点是否存在，不存在就创建
    if (!p)
        p = ++no;
    // 判断区间范围
    // 树区间在查询区间外
    if (start > r || end < l)
        return;
    // 树区间在查询区间内
    if (start >= l && end <= r)
    {
        // 给该节点修改sum值
        sumx[p] = (sumx[p] + ((end - start + 1) % MOD * (a % MOD)) % MOD) % MOD;
        sumy[p] = (sumy[p] + ((end - start + 1) % MOD * (b % MOD)) % MOD) % MOD;
        sumz[p] = (sumz[p] + ((end - start + 1) % MOD * (c % MOD)) % MOD) % MOD;
        // 修改懒标记
        for (int i = 0; i < ro[p]; i++)
        {
            swap(b, c);
            swap(a, b);
        }
        x[p] = (x[p] + a % MOD) % MOD;
        y[p] = (y[p] + b % MOD) % MOD;
        z[p] = (z[p] + c % MOD) % MOD;
        return;
    }
    ll mid = (start + end) >> 1;
    // 递归前需下放一级懒标记
    pushdown(p, start, end);
    // 左递归
    if (mid >= l)
        add(lc[p], start, mid, l, r, a, b, c);
    // 右递归
    if (mid < r)
        add(rc[p], mid + 1, end, l, r, a, b, c);
    // 给该父节点修改sum值,但不修改懒标记
    sumx[p] = (sumx[lc[p]] % MOD + sumx[rc[p]] % MOD) % MOD;
    sumy[p] = (sumy[lc[p]] % MOD + sumy[rc[p]] % MOD) % MOD;
    sumz[p] = (sumz[lc[p]] % MOD + sumz[rc[p]] % MOD) % MOD;
    return;
}
void multi(ll &p, ll start, ll end, ll &l, ll &r, ll &k)
{
    // 判断节点是否存在，不存在就创建
    if (!p)
        p = ++no;
    // 判断区间范围
    // 树区间在查询区间外
    if (start > r || end < l)
        return;
    // 树区间在查询区间内
    if (start >= l && end <= r)
    {
        // 给该节点修改sum值
        sumx[p] = (sumx[p] * (k % MOD)) % MOD;
        sumy[p] = (sumy[p] * (k % MOD)) % MOD;
        sumz[p] = (sumz[p] * (k % MOD)) % MOD;
        // 修改懒标记
        if (!mul[p]) mul[p] = 1;
        mul[p] = mul[p] * (k % MOD) % MOD;
        x[p] = x[p] * (k % MOD) % MOD;
        y[p] = y[p] * (k % MOD) % MOD;
        z[p] = z[p] * (k % MOD) % MOD;
        return;
    }
    // 递归前需下放一级懒标记
    pushdown(p, start, end);
    ll mid = (start + end) >> 1;
    // 左递归
    if (mid >= l)
        multi(lc[p], start, mid, l, r, k);
    // 右递归
    if (mid < r)
        multi(rc[p], mid + 1, end, l, r, k);
    // 给该父节点修改sum值,但不修改懒标记
    sumx[p] = (sumx[lc[p]] % MOD + sumx[rc[p]] % MOD) % MOD;
    sumy[p] = (sumy[lc[p]] % MOD + sumy[rc[p]] % MOD) % MOD;
    sumz[p] = (sumz[lc[p]] % MOD + sumz[rc[p]] % MOD) % MOD;
    return;
}
void rol(ll &p, ll start, ll end, ll &l, ll &r)
{
    // 判断节点是否存在，不存在就创建
    if (!p) p = ++no;
    // 判断区间范围
    // 树区间在查询区间外
    if (start > r || end < l) return;
    // 树区间在查询区间内
    ll t;
    if (start >= l && end <= r)
    {
        // 给该节点修改sum值
        t = sumx[p];
        sumx[p] = sumy[p];
        sumy[p] = sumz[p];
        sumz[p] = t;
        // 修改懒标记
        ro[p] = (ro[p] + 1) % 3;
        return;
    }
    ll mid = (start + end) >> 1;
    // 递归前需下放一级懒标记
    pushdown(p, start, end);
    // 左递归
    if (mid >= l)
        rol(lc[p], start, mid, l, r);
    // 右递归
    if (mid < r)
        rol(rc[p], mid + 1, end, l, r);
    // 给该父节点修改sum值,但不修改懒标记
    sumx[p] = (sumx[lc[p]] % MOD + sumx[rc[p]] % MOD) % MOD;
    sumy[p] = (sumy[lc[p]] % MOD + sumy[rc[p]] % MOD) % MOD;
    sumz[p] = (sumz[lc[p]] % MOD + sumz[rc[p]] % MOD) % MOD;
    return;
}
void query(ll &p, ll start, ll end, ll &l, ll &r, ll &rx, ll &ry, ll &rz)
{
    // 判断节点是否存在，不存在就创建
    if (!p) p = ++no;
    // 判断区间范围
    // 树区间在查询区间外
    if (start > r || end < l) return;
    // 树区间在查询区间内
    if (start >= l && end <= r)
    {
        rx = (rx + sumx[p] % MOD) % MOD;
        ry = (ry + sumy[p] % MOD) % MOD;
        rz = (rz + sumz[p] % MOD) % MOD;
        return;
    }
    ll mid = (start + end) >> 1;
    // 递归前需下放一级懒标记
    pushdown(p, start, end);
    // 左递归
    if (mid >= l)
        query(lc[p], start, mid, l, r, rx, ry, rz);
    // 右递归
    if (mid < r)
        query(rc[p], mid + 1, end, l, r, rx, ry, rz);
    return;
}
int main(int argc, char const *argv[])
{
    cin >> n >> m;
    // 操作
    int op;
    // 操作区间范围
    ll l, r;
    // 创建根节点
    ll root = ++no;
    // 根节点区间
    ll start = 1, end = n;
    ll a, b, c, k;
    // 查询结果
    ll rx, ry, rz, distance;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        cin >> l >> r;
        switch (op)
        {
        case 1:
            cin >> a >> b >> c;
            add(root, start, end, l, r, a, b, c);
            break;
        case 2:
            cin >> k;
            multi(root, start, end, l, r, k);
            break;
        case 3:
            rol(root, start, end, l, r);
            break;
        case 4:
            rx = ry = rz = 0;
            query(root, start, end, l, r, rx, ry, rz);
            distance = ((rx % MOD) * (rx % MOD) % MOD + (ry % MOD) * (ry % MOD) % MOD + (rz % MOD) * (rz % MOD) % MOD) % MOD;
            cout << distance << endl;
            break;
        default:
            break;
        }
    }

    return 0;
}
