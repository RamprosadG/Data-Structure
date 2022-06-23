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

vector<ll> B1, B2;

void update(vector<ll>& bit, int n, int x, ll val) {
    for (int i = x; i <= n; i += (i & -i)) {
        bit[i] += val;
    }
}

void update(int n, int x, ll val) {
    update(B1, n, x, val);
    update(B2, n, x, val * (x - 1));
}

void update(int n, int l, int r, ll val) {
    update(n, l, val);
    update(n, r + 1, -val);
}

ll query(vector<ll>& bit, int x) {
    ll ans = 0;
    for (int i = x; i > 0; i -= (i & -i)) {
        ans += bit[i];
    }
    return ans;
}

ll query(int x) {
    return query(B1, x) * x - query(B2, x);
}

ll query(int l, int r) {
    return query(r) - query(l - 1);
}

int solve() {
    int n; Int(n);
    B1.resize(n + 1, 0);
    B2.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll val; Int(val);
        update(n, i, i, val);
    }
    int q; Int(q);
    while (q--) {
        int ck; Int(ck);
        if (ck == 2) {
            int l, r; Int(l, r);
            printf("%lld\n", query(l, r));
        }
        else {
            int l, r; ll val; Int(l, r, val);
            update(n, l, r, val);
        }
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
