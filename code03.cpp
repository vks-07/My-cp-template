#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#define Sort(v) sort(v.begin(), v.end())
#define Sortr(v) sort(v.rbegin(), v.rend())
#define vec vector<int>
#define vecpair vector<pair<int, int>>
#define mm map<int, int>
#define loop1(n) for (int i = 0; i < n; i++)
#define looprev(r) for (int i = r; i >= 0; i--)
#define loop2(s, e) for (int i = s; i < e; i++)
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define line cout << '\n';
#define st set<int>
#define vvec vector<vector<int>>
#define mxpq priority_queue<int>
#define mnpq priority_queue<int, vector<int>, greater<int>>
#define pp pair<int, int>
#define se(v) v.begin(), v.end()
#define pb push_back
#define ppb pop_back
#define minus_one cout << -1 << endl;

using namespace std;

#define int long long
const int mod = 1e9 + 7;
const int inf = LLONG_MAX;

// RATING IS SHIT, YOU ARE HERE JUST FOR FUN!
// SEE EDGE CASES SPECIALLY (0 & 1)

bool isPowerOfTwo(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

int gcd(int a, int b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

vector<bool> is_prime;
void sieve(int n)
{
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

void print(const vec &v)
{
    for (int x : v)
        cout << x << ' ';
    cout << '\n';
}

void input(vec &v)
{
    for (auto &x : v)
        cin >> x;
}

int mod_pow(int base, int exp, int m)
{
    int res = 1;
    while (exp)
    {
        if (exp & 1)
            res = (res * base) % m;
        base = (base * base) % m;
        exp >>= 1;
    }
    return res;
}

int mod_inverse(int a, int m)
{
    return mod_pow(a, m - 2, m);
}

vec prefix_sum(const vec &v)
{
    vec ps(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        ps[i] = v[i];
        if (i)
            ps[i] += ps[i - 1];
    }
    return ps;
}

vec suffix_sum(const vec &v)
{
    vec ss(v.size());
    for (int i = (int)v.size() - 1; i >= 0; i--)
    {
        ss[i] = v[i];
        if (i + 1 < v.size())
            ss[i] += ss[i + 1];
    }
    return ss;
}

class dsu
{
public:
    vec parent, Rank;

    dsu(int n)
    {
        parent.resize(n + 1);
        Rank.assign(n + 1, 0);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    int find_Parent(int x)
    {
        if (parent[x] != x)
            parent[x] = find_Parent(parent[x]);
        return parent[x];
    }

    void unite(int a, int b)
    {
        a = find_Parent(a);
        b = find_Parent(b);
        if (a != b)
        {
            if (Rank[a] < Rank[b])
                swap(a, b);
            parent[b] = a;
            if (Rank[a] == Rank[b])
                Rank[a]++;
        }
    }
};

// Well i am the Rustin
int f(int r, int g, int b, int x, int y, int z)
{
    int ans = 0;
    if (x != 0 && r>0)
    {
        int yy = y;
        int zz = z;
        if (y >= 0)
            yy--;
        if (z >= 0)
            zz--;
        ans = max(ans, 1 + f(r - 1, g, b, 2, yy, zz));
    }
    if(y!=0 && g>0){
        int yy = x;
        int zz = z;
        if (yy >= 0)
            yy--;
        if (z >= 0)
            zz--;
        ans = max(ans, 1 + f(r , g-1, b, yy, 2, zz));
    }
    if(z!=0){
        int yy = y;
        int zz = x;
        if (y >= 0)
            yy--;
        if (x >= 0)
            zz--;
        ans = max(ans, 1 + f(r - 1, g, b, zz, yy, 2));
    }
    return ans;
}
void Rustin()
{
    int r, g, b;
    cin >> r >> g >> b;
    cout << f(r, g, b, -1, -1, -1) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--)
        Rustin();

    return 0;
}