#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m;
const ll MAXINT = 1e+9 + 7;
struct Point
{
    ll x, y, z;
    Point(ll x, ll y, ll z) : x(x), y(y), z(z){};
    Point operator+(const Point &p)
    {
        return Point((x + p.x) % MAXINT, (y + p.y) % MAXINT, (z + p.z) % MAXINT);
    }
};

// 线段树节点
struct Node
{
    ll l, r;
    // int lazy;
    ll x, y, z;
    Node *lc, *rc;
    Node(ll l, ll r) : l(l), r(r), x(0), y(0), z(0), lc(nullptr), rc(nullptr) {}
};

Point OP(Node *&p, ll l, ll r, int op, ll a, ll b, ll c, ll k)
{
    Point ans = Point(0, 0, 0);
    if (p->r < l || p->l > r)
        return ans;
    ll mid = (p->r - p->l >> 1) + p->l;
    cout << p->l << " " << p->r << endl;
    cout << mid << endl;
    if (!p->lc && !p->rc && p->l != p->r)
    {
        Node *lc = new Node(p->l, mid);
        Node *rc = new Node(mid + 1, p->r);
    }

    if (p->l == l && p->r == r)
    {
        switch (op)
        {
        case 1:
            p->x = (p->x + a) % MAXINT;
            p->y = (p->y + b) % MAXINT;
            p->z = (p->z + c) % MAXINT;
            return ans;
        case 2:
            p->x = (p->x * k) % MAXINT;
            p->y = (p->y * k) % MAXINT;
            p->z = (p->z * k) % MAXINT;
            return ans;
        case 3:
        {
            ll temp = p->x;
            p->x = p->z;
            p->z = p->y;
            p->y = temp;
        }
            return ans;
        case 4:
            return Point(p->x, p->y, p->z);
        default:
            break;
        }
    }
    
    if (l > mid)
        return OP(p->rc, l, r, op, a, b, c, k);
    if (r <= mid)
        return OP(p->lc, l, r, op, a, b, c, k);
    return OP(p->lc, l, mid, op, a, b, c, k) + OP(p->rc, mid + 1, r, op, a, b, c, k);
}
int main(int argc, char const *argv[])
{
    int op;
    ll l, r, a = 0, b = 0, c = 0, k = 0;
    cin >> n >> m;
    Node *root = new Node(1, n);
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> l >> r >> a >> b >> c;
            cout<<l<<" "<<r<<" "<<a<<" "<<b<<" "<<c<<endl;
            OP(root, l, r, op, a, b, c, 0);
            cout << "ok" << endl;
            break;
        case 2:
            cin >> l >> r >> k;
            cout<<l<<" "<<r<<" "<<k<<endl;
            OP(root, l, r, op, 0, 0, 0, k);
            break;
        case 3:
            cin >> l >> r;
            cout<<l<<" "<<r<<endl;
            OP(root, l, r, op, 0, 0, 0, 0);
            break;
        case 4:
            cin >> l >> r;
            cout<<l<<" "<<r<<endl;
            {
                Point ans = OP(root, l, r, op, 0, 0, 0, 0);
                ll distance = sqrt((ans.x * ans.x % MAXINT + ans.y * ans.y % MAXINT + ans.z * ans.z % MAXINT) % MAXINT);
                cout << ans.x << " " << ans.y << " " << ans.z << endl;
                cout << distance << endl;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
