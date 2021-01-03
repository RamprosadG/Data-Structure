#include<bits/stdc++.h>
using namespace std;

#define ll       long long
#define ull      unsigned ll
#define pii      pair<int, int>
#define pll      pair<ll, ll>
#define mp       make_pair
#define ff       first
#define ss       second
#define sz(x)    (int) x.size()
#define all(v)   v.begin(), v.end()

template <typename T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <typename T> inline void smax(T &a, T b) {a = a > b ? a : b;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ", ";
    err(++it, args...);
}

template <typename T> inline void Int(T &n) {
    n = 0; int f = 1; register int ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
    n = n * f;
}

template <typename T, typename TT> inline void Int(T &n, TT &m) { Int(n); Int(m); }
template <typename T, typename TT, typename TTT> inline void Int(T &n, TT &m, TTT &l) { Int(n, m); Int(l); }

const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b) {return (ll) a * b % mod;}

const int inf = (int) 2e9 + 5;
const ll  Inf = (ll) 2e18 + 5;
const int N   = (int) 2e5 + 5;
const int M   = (int) 18;

int idx = 2;
int a[N], b[N], c[N];
int node[50 * N], l[50 * N], r[50 * N], root[N];

std::vector<int> g[N];
int dep[N], par[M][N];
bool vis[N];

int compress(int n) {
    std::vector<pii>  tem;
    for (int i = 1; i <= n ; i++) {
        tem.push_back({a[i], i});
    }
    sort(all(tem));
    int cur = 1;
    for (int i = 0; i < n; i++) {
        if (i > 0 and tem[i].ff != tem[i - 1].ff) cur++;
        b[tem[i].ss] = cur;
        c[b[tem[i].ss]] = a[tem[i].ss];
    }
    return cur;
}

void build(int pos, int left, int right) {
    if (left == right) return;
    int mid = (left + right) >> 1;
    l[pos] = idx++;
    r[pos] = idx++;
    build(l[pos], left, mid);
    build(r[pos], mid + 1, right);
}

int update(int pos, int left, int right, int x) {
    if (left > x or right < x) return pos;
    int id = idx++;
    if (left == right) {
        node[id] = node[pos] + 1;
        return id;
    }
    int mid = (left + right) >> 1;
    l[id] = update(l[pos], left, mid, x);
    r[id] = update(r[pos], mid + 1, right, x);
    node[id] = node[l[id]] + node[r[id]];
    return id;
}

int query(int pos1, int pos2, int pos3, int pos4, int left, int right, int k) {
    if (left == right) return c[left];
    int mid = (left + right) >> 1;
    int cnt = node[l[pos1]] + node[l[pos2]] - node[l[pos3]] - node[l[pos4]];
    if (cnt >= k) return query(l[pos1], l[pos2], l[pos3], l[pos4], left, mid, k);
    else return query(r[pos1], r[pos2], r[pos3], r[pos4], mid + 1, right, k - cnt);
}

void dfs(int n, int u, int p, int d = 1) {
    vis[u] = true, dep[u] = d;
    root[u] = update(root[p], 1, n, b[u]);
    for (int i = 1; i < M; i++) {
        par[i][u] = par[i - 1][par[i - 1][u]];
    }
    for (auto v : g[u]) {
        if (vis[v]) continue;
        par[0][v] = u;
        dfs(n, v, u, d + 1);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = M - 1; i >= 0 and u != v; i--) {
        if (dep[par[i][u]] >= dep[v]) u = par[i][u];
    }
    if (u == v) return u;
    for (int i = M - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
    }
    return par[0][u];
}

int solve() {
    int n, q; Int(n, q);
    for (int i = 1; i <= n; i++) {
        Int(a[i]);
    }
    int mx = compress(n);
    for (int i = 1; i < n ; i++) {
        int u, v; Int(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    par[0][1] = 1;
    root[0] = 1;
    build(1, 1, mx);
    dfs(mx, 1, 0);
    while (q--) {
        int u, v, k; Int(u, v, k);
        int x = lca(u, v);
        int y = par[0][x];
        if (x == 1) y = 0;
        int ans = query(root[u], root[v], root[x], root[y], 1, mx, k);
        printf("%d\n", ans);
    }
    return 0;
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int test = 1, tc = 0;
    //Int(test);
    //cin >> test;
    while (test--) {
        //printf("Case %d: ", ++tc);
        solve();
    }
    return 0;
}
