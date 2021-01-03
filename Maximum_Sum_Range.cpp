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

struct item {
	ll sum, pre, suff, best;
	item() {
		sum = 0, pre = 0, suff = 0, best = -Inf;
	}
};

item node[4 * N];

item combine(item x, item y) {
	if (x.best == -Inf) return y;
	if (y.best == -Inf) return x;
	item res;
	res.sum = x.sum + y.sum;
	res.pre = max(x.pre, x.sum + y.pre);
	res.suff = max(y.suff, y.sum + x.suff);
	res.best = max(max(x.best, y.best), x.suff + y.pre);
	return res;
}

void build(int pos, int left, int right) {
	if (left == right) {
		node[pos].sum = node[pos].pre = node[pos].suff = node[pos].best = a[left];
		return;
	}
	int mid = (left + right) >> 1;
	build(pos * 2, left, mid);
	build(pos * 2 + 1, mid + 1, right);
	node[pos] = combine(node[pos * 2], node[pos * 2 + 1]);
}

void update(int pos, int left, int right, int x, ll val) {
	if (left > x or right < x) return;
	if (left == right) {
		node[pos].sum += val;
		node[pos].pre += val;
		node[pos].suff += val;
		node[pos].best += val;
		return;
	}
	int mid = (left + right) >> 1;
	update(pos * 2, left, mid, x, val);
	update(pos * 2 + 1, mid + 1, right, x, val);
	node[pos] = combine(node[pos * 2], node[pos * 2 + 1]);
}

item query(int pos, int left, int right, int x, int y) {
	if (left > y or right < x) {
		item x;
		return x;
	}
	if (left >= x and right <= y) return node[pos];
	int mid = (left + right) >> 1;
	item m = query(pos * 2, left, mid, x, y);
	item n = query(pos * 2 + 1, mid + 1, right, x, y);
	return combine(m, n);
}

int solve() {
	int n, q; Int(n, q);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	build(1, 1, n);
	while (q--) {
		int ck; Int(ck);
		if (ck == 2) {
			int l, r; Int(l, r);
			printf("%lld\n", query(1, 1, n, l, r).best);
		}
		else {
			int x; ll val; Int(x, val);
			update(1, 1, n, x, val);
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
