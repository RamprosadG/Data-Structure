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

int node[N][2];
int cnt[N];
int state = 0;

void Insert(int root, int num) {
	int n = 30;
	for (int i = n; i >= 0; i--) {
		int to = ((num >> i) & 1);
		if (node[root][to] == -1) node[root][to] = ++state;
		root = node[root][to];
		cnt[root]++;
	}
}

void Remove(int root, int num) {
	int n = 30;
	for (int i = n; i >= 0; i--) {
		int to = ((num >> i) & 1);
		int tem = node[root][to];
		cnt[tem]--;
		if (cnt[tem] == 0) root[node][to] = -1;
		root = tem;
	}
}

int max_query(int root, int num) {
	int n = 30, ans = 0;
	for (int i = n; i >= 0; i--) {
		int to = ((num >> i) & 1);
		if (node[root][to ^ 1] != -1) {
			ans += (1 << i);
			root = node[root][to ^ 1];
		}
		else {
			root = node[root][to];
		}
	}
	return ans;
}

int min_query(int root, int num) {
	int n = 30, ans = 0;
	for (int i = n; i >= 0; i--) {
		int to = ((num >> i) & 1);
		if (node[root][to] != -1) {
			root = node[root][to];
		}
		else {
			ans += (1 << i);
			root = node[root][to ^ 1];
		}
	}
	return ans;
}

int less_query(int root, int num, int k) {
	int n = 30, ans = 0;
	for (int i = n; i >= 0; i--) {
		int need = ((k >> i) & 1);
		int has = ((num >> i) & 1);
		if (need == 1) {
			if (has == 0) {
				if (node[root][0] != -1) ans += cnt[node[root][0]];
				if (node[root][1] != -1) root = node[root][1];
				else break;
			}
			else {
				if (node[root][1] != -1) ans += cnt[node[root][1]];
				if (node[root][0] != -1) root = node[root][0];
				else break;
			}
		}
		else {
			if (has == 0) {
				if (node[root][0] != -1) root = node[root][0];
				else break;
			}
			else {
				if (node[root][1] != -1) root = node[root][1];
				else break;
			}
		}
	}
	return ans;
}

int solve() {
	memset(node, -1, sizeof(node));
	int root = 0;
	int q; Int(q);
	while (q--) {
		int ck, num; Int(ck, num);
		if (ck == 1) Insert(root, num);
		else if (ck == 2) Remove(root, num);
		else if (ck == 3) printf("%d\n", min_query(root, num));
		else if (ck == 4) printf("%d\n", max_query(root, num));
		else {
			int k; Int(k);
			printf("%d\n", less_query(root, num, k));
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
