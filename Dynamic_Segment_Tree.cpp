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

struct Dynamic_Seg_tree {

	vector<ll> node;
	vector<int> l, r;

	Dynamic_Seg_tree() {
		node.push_back(0);
		l.push_back(-1);
		r.push_back(-1);
	}

	void get_id(int& x) {
		x = sz(node);
		node.push_back(0);
		l.push_back(-1);
		r.push_back(-1);
	}

	void update(int pos, int left, int right, int x, ll val) {
		if (left == right) {
			node[pos] += val;
			return;
		}
		int mid = (left + right) >> 1;
		if (x <= mid) {
			if (l[pos] == -1) get_id(l[pos]);
			update(l[pos], left, mid, x, val);
		}
		else {
			if (r[pos] == -1) get_id(r[pos]);
			update(r[pos], mid + 1, right, x, val);
		}
		node[pos] = 0;
		if (l[pos] != -1) node[pos] += node[l[pos]];
		if (r[pos] != -1) node[pos] += node[r[pos]];
	}

	ll query(int pos, int left, int right, int x, int y) {
		if (left > y or right < x) return 0;
		if (left >= x and right <= y)  return node[pos];
		int mid = (left + right) >> 1;
		ll ans = 0;
		if (l[pos] != -1) ans += query(l[pos], left, mid, x, y);
		if (r[pos] != -1) ans += query(r[pos], mid + 1, right, x, y);
		return ans;
	}
};


int solve() {
	int n = 1e8;
	int q; Int(q);
	Dynamic_Seg_tree dp;
	while (q--) {
		int ck; Int(ck);
		if (ck == 2) {
			int x, y; Int(x, y);
			printf("%lld\n", dp.query(0, 1, n, x, y));
		}
		else {
			int x; ll val; Int(x, val);
			dp.update(0, 1, n, x, val);
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
