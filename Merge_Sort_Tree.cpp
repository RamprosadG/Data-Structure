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

vector<int> node[4 * N];
int a[N];

void build(int pos, int left, int right) {
	if (left == right) {
		node[pos].push_back(a[left]);
		return;
	}
	int mid = (left + right) >> 1;
	build(pos * 2, left, mid);
	build(pos * 2 + 1, mid + 1, right);
	merge(all(node[pos * 2]), all(node[pos * 2 + 1]), back_inserter(node[pos]));
}

int query(int pos, int left, int right, int x, int y, int p, int q) {
	if (left > y or right < x) return 0;
	if (left >= x and right <= y) return upper_bound(all(node[pos]), q) - lower_bound(all(node[pos]), p);
	int mid = (left + right) >> 1;
	int m = query(pos * 2, left, mid, x, y, p, q);
	int n = query(pos * 2 + 1, mid + 1, right, x, y, p, q);
	return m + n;
}

int query_mn(int pos, int left, int right, int x, int y, int p, int q) {
	if (left > y or right < x) return inf;
	if (left >= x and right <= y) {
		int cnt = upper_bound(all(node[pos]), q) - lower_bound(all(node[pos]), p);
		if (!cnt) return inf;
		return *lower_bound(all(node[pos]), p);
	}
	int mid = (left + right) >> 1;
	int m = query_mn(pos * 2, left, mid, x, y, p, q);
	int n = query_mn(pos * 2 + 1, mid + 1, right, x, y, p, q);
	return min(m, n);
}

int query_mx(int pos, int left, int right, int x, int y, int p, int q) {
	if (left > y or right < x) return -inf;
	if (left >= x and right <= y) {
		int cnt = upper_bound(all(node[pos]), q) - lower_bound(all(node[pos]), p);
		if (!cnt) return -inf;
		auto it = upper_bound(all(node[pos]), q);
		--it;
		return *it;
	}
	int mid = (left + right) >> 1;
	int m = query_mx(pos * 2, left, mid, x, y, p, q);
	int n = query_mx(pos * 2 + 1, mid + 1, right, x, y, p, q);
	return max(m, n);
}

int solve() {
	int n, q; Int(n, q);
	for (int i = 1; i <= n; i++) {
		Int(a[i]);
	}
	build(1, 1, n);
	while (q--) {
		int l, r, p, q; Int(l, r); Int(p, q);
		int cnt = query(1, 1, n, l, r, p, q);
		int x = -1, y = -1;
		if (cnt) {
			x = query_mn(1, 1, n, l, r, p, q);
			y = query_mx(1, 1, n, l, r, p, q);
		}
		printf("%d %d %d\n", cnt, x, y);
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
