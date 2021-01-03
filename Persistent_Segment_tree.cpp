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

ll a[N];
ll node[50 * N];
int l[50 * N], r[50 * N], root[N];
int idx = 1;

void build(int pos, int left, int right) {
	if (left == right) {
		node[pos] = a[left];
		return;
	}
	int mid = (left + right) >> 1;
	l[pos] = ++idx;
	r[pos] = ++idx;
	build(l[pos], left, mid);
	build(r[pos], mid + 1, right);
	node[pos] = node[l[pos]] + node[r[pos]];
}

int update(int pos, int left, int right, int x, ll val) {
	if (left > x || right < x) return pos;
	int id = ++idx;
	if (left == right) {
		node[id] = node[pos] + val;
		return id;
	}
	int mid = (left + right) >> 1;
	l[id] = update(l[pos], left, mid, x, val);
	r[id] = update(r[pos], mid + 1, right, x, val);
	node[id] = node[l[id]] + node[r[id]];
	return id;
}

int query(int pos, int left, int right, int x, int y) {
	if (left > y or right < x) return 0;
	if (left >= x and right <= y) return node[pos];
	int mid = (left + right) >> 1;
	return query(l[pos], left, mid, x, y) + query(r[pos], mid + 1, right, x, y);
}

int solve() {
	int n; Int(n);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	root[0] = 1;
	build(root[0], 1, n);
	int k; Int(k);
	for (int i = 1; i <= k; i++) {
		int x; ll val; Int(x, val);
		root[i] = update(root[i - 1], 1, n, x, val);
	}
	int q; Int(q);
	while (q--) {
		int u, l, r; Int(u, l, r);
		printf("%lld\n", query(root[u], 1, n, l, r));
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
