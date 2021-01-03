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
const int N   = (int) 500 + 5;
const int M   = (int) 9;

ll a[N][N];
ll table[N][M][N][M];

void build(int n, int m) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			table[i][0][j][0] = a[i][j];
		for (int k = 1; (1 << k) <= m; k++) {
			for (int j = 1; j + (1 << (k - 1)) - 1 <= m; j++) {
				table[i][0][j][k] = min(table[i][0][j][k - 1], table[i][0][j + (1 << (k - 1))][k - 1]);
			}
		}
	}
	for (int k = 1; (1 << k) <= n; k++) {
		for (int i = 1; i + (1 << k) - 1 <= n; i++) {
			for (int l = 0; (1 << l) <= m; l++) {
				for (int j = 1; j + (1 << l) - 1 <= m; j++) {
					table[i][k][j][l] = min(table[i][k - 1][j][l], table[i + (1 << (k - 1))][k - 1][j][l]);
				}
			}
		}
	}
}

ll query(int x1, int y1, int x2, int y2) {
	int k = log2(x2 - x1 + 1), l = log2(y2 - y1 + 1);
	ll r1 = min(table[x1][k][y1][l], table[x1][k][y2 + 1 - (1 << l)][l]);
	ll r2 = min(table[x2 + 1 - (1 << k)][k][y1][l], table[x2 + 1 - (1 << k)][k][y2 + 1 - (1 << l)][l]);
	return min(r1, r2);
}


int solve() {
	int n, m; Int(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			Int(a[i][j]);
		}
	}
	build(n, m);
	int q; Int(q);
	while (q--) {
		int x1, y1, x2, y2; Int(x1, y1); Int(x2, y2);
		printf("%lld\n", query(x1, y1, x2, y2));
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
