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
const int N   = (int) 2e3 + 5;

ll bit[N][N];

void update(int n, int m, int x, int y, ll val) {
	for (int i = x; i <= n; i += (i & -i)) {
		for (int j = y; j <= m; j += (j & -j)) {
			bit[i][j] += val;
		}
	}
}

ll query(int x, int y) {
	ll ans = 0;
	for (int i = x; i > 0; i -= (i & -i)) {
		for (int j = y; j > 0; j -= (j & -j)) {
			ans += bit[i][j];
		}
	}
	return ans;
}

ll query(int x1, int y1, int x2, int y2) {
	return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

int solve() {
	int n, m; Int(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ll val; Int(val);
			update(n, m, i, j, val);
		}
	}
	int q; Int(q);
	while (q--) {
		int ck; Int(ck);
		if (ck == 1) {
			int x, y; ll val; Int(x, y, val);
			update(n, m, x, y, val);
		}
		else {
			int x1, y1, x2, y2; Int(x1, y1); Int(x2, y2);
			printf("%lld\n", query(x1, y1, x2, y2));
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
